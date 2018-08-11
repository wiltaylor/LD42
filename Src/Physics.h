#pragma once
#include "Level.h"

class Physics
{
public:
	Physics(Level* level) : m_level{ level } {}
	~Physics() = default;

	bool canMove(float x, float y);

private:
	Level * m_level;
};
