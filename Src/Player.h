#pragma once
#include <glm/vec2.hpp>

class Player
{
public:
	Player() = default;
	~Player() = default;

	float getAngle() { return m_angle; }

	void setAngle(float value) { m_angle = value; }

	void setPosition(glm::vec2 position) { m_position = position; }
	glm::vec2& getPosition() { return m_position; }

private:
	float m_angle = 0;
	glm::vec2 m_position = {0,0};
};