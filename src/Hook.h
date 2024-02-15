#pragma once

#include <windows.h>
DWORD HookCall(DWORD hookAt, DWORD newFunction);
DWORD HookIAT(const char* functionName, DWORD newFunction);

