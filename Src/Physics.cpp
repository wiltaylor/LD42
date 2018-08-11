#include "Physics.h"

bool Physics::canMove(float x, float y)
{
	auto block = m_level->getBlock(static_cast<int>(x), static_cast<int>(y));
	return block->passable;
}

HITTYPE Physics::testPosition(float x, float y)
{
	return testPosition(x, y, false);
}

HITTYPE Physics::testPosition(float x, float y, bool skipPlayer)
{
	m_lastHitObject = nullptr;

	auto block = m_level->getBlock(static_cast<int>(x), static_cast<int>(y));
	
	if (!block->passable)
		return HIT_WALL;

	if (!skipPlayer)
	{
		float playerDiffX = x - m_playerX;
		float playerDiffY = y - m_playerY;

		if (playerDiffX < 1.0f && playerDiffX > -1.0f && playerDiffY < 1.0f && playerDiffY > -1.0f)
			return HIT_PLAYER;
	}

	for (auto &obj : m_level->getGameObjects())
	{


		float objDiffX = x - obj->x;
		float objDiffY = y - obj->y;

		if (objDiffX < 1.0f && objDiffX > -1.0f && objDiffY < 1.0f && objDiffY > -1.0f)
		{
			m_lastHitObject = obj;

			if (!obj->solid)
				continue;
			
			return HIT_OBJECT;
		}
	}

	return HIT_NOTHING;
	
}

void Physics::update(float deltaTime)
{
	for (auto &obj : m_level->getGameObjects())
	{
		if (obj->cleanUp)
			continue;

		if(!obj->physicsObject)
			continue;

		float newX = obj->x + obj->vx * deltaTime;
		float newY = obj->y + obj->vy * deltaTime;

		auto hit = testPosition(newX, newY);

		if (hit == HIT_WALL || hit == HIT_OBJECT)
		{
			if (obj->projectile)
				obj->cleanUp = true;

			obj->vx = 0;
			obj->vy = 0;
		}
		else if(hit == HIT_PLAYER)
		{
			//do player damage if npc
		}
		else
		{
			obj->x = newX;
			obj->y = newY;
		}		
	}

	m_lastHitObject = nullptr;
}