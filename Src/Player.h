#pragma once
#include <glm/vec2.hpp>
#include "LevelBlock.h"

class Player
{
public:
	Player() = default;
	~Player() = default;

	float getAngle() { return m_angle; }

	void setAngle(float value) { m_angle = value; }

	void setPosition(glm::vec2 position) { m_position = position; }
	glm::vec2& getPosition() { return m_position; }

	void pickupKey(LockLevel key);
	bool hasKey(LockLevel key);
	void doDamage(float ammount) { m_hp -= ammount; }
	float getHp() const {return m_hp;}

private:
	float m_angle = 0;
	glm::vec2 m_position = {0,0};
	bool m_redKey;
	bool m_greenKey;
	bool m_blueKey;
	bool m_goldKey;
	float m_hp = 100.0f;
};