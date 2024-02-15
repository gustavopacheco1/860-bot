#pragma once

#include <windows.h>
#include "Creature.h"

class LocalPlayer
{
public:
	DWORD fist;				 // 0x00
	DWORD club;				 // 0x04
	DWORD sword;			 // 0x08
	DWORD axe;				 // 0x0C
	DWORD distance;			 // 0x10
	DWORD shielding;		 // 0x14
	DWORD fishing;			 // 0x18
	DWORD battleHoverId;	 // 0x1C
	DWORD followId;			 // 0x20
	DWORD targetId;			 // 0x24
	DWORD cap;				 // 0x28
	DWORD stamina;			 // 0x2C
	DWORD soulPoints;		 // 0x30
	DWORD maxMana;			 // 0x34
	DWORD mana;				 // 0x38
	DWORD magicLevelPercent; // 0x3C
	DWORD levelPercent;		 // 0x40
	DWORD magicLevel;		 // 0x44
	DWORD level;			 // 0x48
	DWORD experience;		 // 0x4C
	DWORD maxHealth;		 // 0x50
	DWORD health;			 // 0x54
	DWORD id;				 // 0x58

	void attack(DWORD cid);
	const int getHealthPercent() const;
	Creature* getCreature() const;
};