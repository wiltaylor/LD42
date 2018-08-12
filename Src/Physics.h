#pragma once
#include "Level.h"
#include "GameObject.h"
#include <glm/glm.hpp>

typedef enum {
	HIT_NOTHING,
	HIT_PLAYER,
	HIT_OBJECT,
	HIT_WALL
} HITTYPE;

class Physics
{
public:
	Physics(Level* level, Player* player) : m_level{ level }, m_player { player } {}
	~Physics() = default;

	HITTYPE testPosition(glm::vec2 position);
	HITTYPE testPosition(glm::vec2 position, bool skipPlayer);
	void update(float deltaTime);

	GameObject* getLastHitObject() { return m_lastHitObject; }

private:
	Level* m_level;
	Player* m_player;
	GameObject* m_lastHitObject;
};
