#include "Physics.h"

HITTYPE Physics::testPosition(glm::vec2 position)
{
	return testPosition(position, false);
}

HITTYPE Physics::testPosition(glm::vec2 position, bool skipPlayer)
{
	m_lastHitObject = nullptr;

	auto block = m_level->getBlock(static_cast<int>(position.x), static_cast<int>(position.y));
	
	if (!block->passable)
		return HIT_WALL;

	if (!skipPlayer)
	{
		auto diff = position - m_player->getPosition();
		float mag = glm::length(diff);
		
		if (mag < 0.1f && mag > -0.1f)
			return HIT_PLAYER;
	}

	for (auto &obj : m_level->getGameObjects())
	{
		auto diff = position - obj->getPosition();
		float mag = glm::length(diff);

		if (mag < 0.1f && mag > -0.1f)
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

		const glm::vec2 newPosition = obj->getPosition() + obj->getVelocity() * deltaTime;

		auto hit = testPosition(newPosition);

		if (hit == HIT_WALL || hit == HIT_OBJECT)
		{
			if (obj->projectile)
				obj->cleanUp = true;

			obj->setVelocity({ 0,0 });
		}
		else if(hit == HIT_PLAYER)
		{
			//do player damage if npc
		}
		else
		{
			obj->setPosition(newPosition);
		}		
	}

	m_lastHitObject = nullptr;
}
void Physics::useInFront()
{
	const glm::vec2 usePosition(
		{
			m_player->getPosition().x + sinf(m_player->getAngle()),
			m_player->getPosition().y + cosf(m_player->getAngle())
		});

 	const auto block = m_level->getBlock(usePosition.x, usePosition.y);

	if (block->door)
	{
		block->open = true;
		block->passable = true;
	}
}
