#pragma once
#include <iostream>
#include <windows.h>

class Creature
{
public:
	DWORD id;            // 0x00
	char name[32];       // 0x04
	DWORD posX;          // 0x24
	DWORD posY;          // 0x28
	DWORD posZ;          // 0x2C
	BYTE __pad1[28];     // 0x30
	BOOL isWalking;      // 0x4C
	DWORD direction;     // 0x50
	BYTE __pad2[12];     // 0x54
	DWORD lookType;      // 0x60
	DWORD lookHead;      // 0x64
	DWORD lookBody;      // 0x68
	DWORD lookLegs;      // 0x6C
	DWORD lookFeet;      // 0x70
	DWORD addon;         // 0x74
	DWORD light;         // 0x78
	DWORD lightColor;    // 0x7C
	DWORD __unknown1;    // 0x80
	DWORD blackSquare;   // 0x84
	DWORD health;        // 0x88
	DWORD speed;         // 0x8C
	BOOL isVisible;      // 0x90
	DWORD skull;         // 0x94
	DWORD party;         // 0x98
	DWORD __unknown2;    // 0x9C
	DWORD guildEmblem;   // 0xA0
	BOOL blocking;       // 0xA4
};