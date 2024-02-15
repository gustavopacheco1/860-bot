#include "LocalPlayer.h"
#include "Memory.h"
#include "Address.h"
#include "Game.h"

void LocalPlayer::attack(DWORD cid)
{
	((void (cdecl*)(DWORD))0x4F8290)(0xA1);
	((void (cdecl*)(DWORD))0x4F88A0)(cid);
	((void (cdecl*)(DWORD))0x4F88A0)(10);
	((void (cdecl*)(DWORD))0x4F8E40)(1);
	targetId = cid;
}

const int LocalPlayer::getHealthPercent() const
{
    return (health / maxHealth) * 100;
}

Creature* LocalPlayer::getCreature() const
{
	Game g;
	g.updateCreatureList();
	for (const auto& creature : g.getCreatureList()) {
		if (creature->id == id) {
			return creature;
		}
	}

    return nullptr;
}
