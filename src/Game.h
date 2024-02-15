#pragma once

#include <iostream>
#include <vector>
#include "Creature.h"

class Game
{
	std::vector<Creature*> m_creatureList;
public:
	Game() = default;

	void updateCreatureList();
	const std::vector<Creature*> getCreatureList() const;
};