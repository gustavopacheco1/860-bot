#include <iostream>
#include "Hook.h"
#include "Memory.h"
#include "Address.h"

DWORD HookCall(DWORD hookAt, DWORD newFunction)
{
	DWORD newOffset = newFunction - hookAt - 5;

	auto oldProtection = protectMemory<DWORD>(hookAt + 1, PAGE_EXECUTE_READWRITE);
	DWORD originalOffset = readMemory<DWORD>(hookAt + 1);
	writeMemory<DWORD>(hookAt + 1, newOffset);
	protectMemory<DWORD>(hookAt + 1, oldProtection);

	return originalOffset + hookAt + 5;
}

DWORD HookIAT(const char* functionName, DWORD newFunction)
{
	auto dosHeader = pointMemory<IMAGE_DOS_HEADER>(ADDR::BASE);
	if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		return 0;
	}

	auto optHeader = pointMemory<IMAGE_OPTIONAL_HEADER>(ADDR::BASE + dosHeader->e_lfanew + 24);
	if (optHeader->Magic != IMAGE_NT_OPTIONAL_HDR_MAGIC) {
		return 0;
	}

	auto IAT = optHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	if (IAT.Size == 0|| IAT.VirtualAddress == 0) {
		return 0;
	}

	auto importDescriptor = pointMemory<IMAGE_IMPORT_DESCRIPTOR>(ADDR::BASE + IAT.VirtualAddress);
	while (importDescriptor != nullptr && importDescriptor->FirstThunk)
	{
		int index = 0;
		auto thunkData = pointMemory<IMAGE_THUNK_DATA>(ADDR::BASE + importDescriptor->OriginalFirstThunk);
		
		while (thunkData != nullptr && thunkData->u1.Function)
		{
			auto importFunctionName = pointMemory<char>(ADDR::BASE + (DWORD)(thunkData->u1.AddressOfData + 2));
			if (importFunctionName != nullptr && (strcmp(importFunctionName, functionName) == 0)) {
				auto VFTable = pointMemory<DWORD>(ADDR::BASE + importDescriptor->FirstThunk);
				DWORD original = VFTable[index];
			 
			
				auto oldProtection = protectMemory<DWORD>((DWORD)&VFTable[index], PAGE_READWRITE);
				VFTable[index] = newFunction;
				protectMemory<DWORD>((DWORD)&VFTable[index], oldProtection);
			
				return original;
			}

			index++;
			thunkData++;
		}
		importDescriptor++;
	}
	return 0;
}