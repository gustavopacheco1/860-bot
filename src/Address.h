#pragma once
#include <windows.h>

namespace ADDR {
	// NOTE: we don't need module base
	// since Tibia 860 is not ASLR protected.
	static auto BASE = (DWORD)GetModuleHandle(NULL);

	static constexpr auto SAY_FUNC = 0x4073F0;
	static constexpr auto LOCAL_FIST_LEVEL = 0x63FE40;
	static constexpr auto CREATURE_LIST = 0x63FEF8;
}

typedef void(cdecl _say)(int talkMode, const char* msg);
static _say* say = (_say*)ADDR::SAY_FUNC;