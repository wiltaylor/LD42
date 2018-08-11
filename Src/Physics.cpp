#include "Physics.h"

bool Physics::canMove(float x, float y)
{
	auto block = m_level->getBlock(static_cast<int>(x), static_cast<int>(y));
	return block->passable;
}