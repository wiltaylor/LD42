#pragma once
#include "Level.h"
#include "GameObject.h"
#include <vector>

typedef enum {
	HIT_NOTHING,
	HIT_PLAYER,
	HIT_OBJECT,
	HIT_WALL
} HITTYPE;

class Physics
{
public:
	Physics(Level* level) : m_level{ level } {}
	~Physics() = default;

	HITTYPE testPosition(float x, float y);
	HITTYPE testPosition(float x, float y, bool skipPlayer);
	bool canMove(float x, float y);
	void setPlayerPosition(float x, float y, float a) {
		m_playerX = x;
		m_playerY = y;
		m_playerA = a;
	}

	void update(float deltaTime);

	GameObject* getLastHitObject() { return m_lastHitObject; }

private:
	Level* m_level;
	float m_playerX;
	float m_playerY;
	float m_playerA;
	GameObject* m_lastHitObject;
};
