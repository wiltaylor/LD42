#include "Physics.h"

HITTYPE Physics::testPosition(glm::vec2 position)
{
	return testPosition(position, false, nullptr, false);
}

HITTYPE Physics::testPosition(glm::vec2 position, bool skipPlayer, GameObject* self)
{
	return testPosition(position, skipPlayer, self, false);
}

HITTYPE Physics::testPosition(glm::vec2 position, bool skipPlayer, GameObject* self, bool projectile)
{
	m_lastHitObject = nullptr;

	auto block = m_level->getBlock(static_cast<int>(position.x), static_cast<int>(position.y));
	
	if (!block->passable)
		return HIT_WALL;

	if (!skipPlayer)
	{
		auto diff = position - m_player->getPosition();
		float mag = glm::length(diff);
		
		if (mag < m_tolerance && mag > -m_tolerance)
			return HIT_PLAYER;
	}

	for (auto &obj : m_level->getGameObjects())
	{

		if (obj == self)
			continue;

		auto diff = position - obj->getPosition();
		float mag = glm::length(diff);

		if (mag < 0.1f && mag > -0.1f)
		{
			m_lastHitObject = obj;

			if (!obj->solid && !projectile)
				continue;
			
			return HIT_OBJECT;
		}
	}

	return HIT_NOTHING;
}

HITTYPE Physics::testProjectile(glm::vec2 position, bool skipPlayer, GameObject* self)
{
	m_lastHitObject = nullptr;

	auto block = m_level->getBlock(static_cast<int>(position.x), static_cast<int>(position.y));

	if (!block->passable)
		return HIT_WALL;

	if (!skipPlayer)
	{
		auto diff = position - m_player->getPosition();
		float mag = glm::length(diff);

		if (mag < m_tolerance && mag > -m_tolerance)
			return HIT_PLAYER;
	}

	for (auto &obj : m_level->getGameObjects())
	{

		if (obj == self)
			continue;

		if (!obj->physicsObject)
			continue;
				
		auto diff = position - obj->getPosition();
		float mag = glm::length(diff);

		if (mag < 0.5f && mag > -0.5f)
		{
			m_lastHitObject = obj;

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

		const auto newPosition = obj->getPosition() + obj->getVelocity() * deltaTime;

		const auto hit = obj->projectile ? testProjectile(newPosition, false, obj) : 
			testPosition(newPosition, false, obj);

		if(hit == HIT_WALL)
		{
			if (obj->projectile)
			{
				obj->cleanUp = true;
			}

			obj->setVelocity({ 0,0 });

		}

		if (hit == HIT_OBJECT)
		{
			if (obj->projectile)
			{
				obj->cleanUp = true;

				if(m_lastHitObject != nullptr)
					m_lastHitObject->onHitWithProjectile(obj->dmg);
			}

			obj->setVelocity({ 0,0 });
		}
		else if(hit == HIT_PLAYER)
		{
			m_player->doDamage(obj->dmg);
		}
		else
		{
			obj->setPosition(newPosition);
		}		
	}

	m_lastHitObject = nullptr;
}
void Physics::useInFront() const
{
	const glm::vec2 usePosition(
		{
			m_player->getPosition().x + sinf(m_player->getAngle()),
			m_player->getPosition().y + cosf(m_player->getAngle())
		});

 	const auto block = m_level->getBlock(static_cast<int>(usePosition.x), static_cast<int>(usePosition.y));

	if (block->door)
	{
		if (m_player->hasKey(block->lock))
		{
			block->open = true;
			block->passable = true;
		}
	}
}
