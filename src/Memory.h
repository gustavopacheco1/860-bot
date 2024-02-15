#pragma once
#include <windows.h>

template<typename T>
T* pointMemory(DWORD address)
{
	return reinterpret_cast<T*>(address);
}

template<typename T>
T readMemory(DWORD address)
{
	return *reinterpret_cast<T*>(address);
}

template<typename T>
void writeMemory(DWORD address, T value)
{
	*reinterpret_cast<T*>(address) = value;
}

template <typename T>
DWORD protectMemory(DWORD address, DWORD protection)
{
	DWORD oldProtection;
	VirtualProtect(reinterpret_cast<LPVOID>(address), sizeof(T), protection, &oldProtection);
	return oldProtection;
}