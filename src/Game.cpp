#include "Game.h"
#include "Memory.h"
#include "Address.h"

void Game::updateCreatureList()
{
	m_creatureList.clear();

	DWORD i = ADDR::CREATURE_LIST;
	
	while (readMemory<DWORD>(i) != 0) {
		m_creatureList.push_back((Creature*)i);
		i += 0xA8;
	}
}

const std::vector<Creature*> Game::getCreatureList() const
{
	return m_creatureList;
}
