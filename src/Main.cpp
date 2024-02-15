#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <math.h>
#include "Enums.h"
#include "Address.h"
#include "Hook.h"
#include "LocalPlayer.h"
#include "Memory.h"
#include "Game.h"

#pragma comment(lib, "ws2_32")

DWORD WINAPI init(LPVOID lpParam)
{
	AllocConsole();
	FILE *f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	printf("Injected.\n");
	Game g;
	LocalPlayer *localPlayer = (LocalPlayer*)ADDR::LOCAL_FIST_LEVEL;

	while (true)
	{
		if (localPlayer->health == 0) {
			// Poor way to check if player is online.
			Sleep(1000);
			continue;
		}

		// Auto attacker
		if (GetAsyncKeyState(VK_F1) & 0x01) {
			Creature* lpCreature = localPlayer->getCreature();

			if (lpCreature == nullptr || localPlayer->targetId > 0) {
				continue;
			}

			g.updateCreatureList();
			for (const auto &creature : g.getCreatureList())
			{
				if (
					creature->id < 0x40000000 || creature->id >= 0x80000000
					|| creature->posZ != lpCreature->posZ
					|| creature->health <= 0
					|| creature->isVisible == 0
				) {
					continue;
				}

				const int dx = abs(static_cast<int>(creature->posX - lpCreature->posX));
				const int dy = abs(static_cast<int>(creature->posY - lpCreature->posY));

				// Default is 7 and 5, but this way we can
				// attack creatures off-screen
				if (dx > 8 || dy > 6) {
					continue;
				}

				localPlayer->attack(creature->id);
				break;
			}
		}

		// Auto healer
		if (localPlayer->getHealthPercent() < 90) {
			say(TALK_SAY, "regeneration");
			Sleep(90);
		}
		Sleep(10);
	}

	FreeConsole();
	fclose(f);
	FreeLibraryAndExitThread((HMODULE)lpParam, 0);
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule,
					  DWORD ul_reason_for_call,
					  LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, &init, hModule, NULL, NULL);
		break;
	}
	return TRUE;
}
