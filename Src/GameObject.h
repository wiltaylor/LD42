#pragma once
#include "AssetLoader.h"
#include <glm/vec2.hpp>

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	bool visible;
	int texture;
	bool physicsObject;
	bool solid;
	bool cleanUp;
	bool projectile;
	bool playerOwned;

	virtual void OnPlayerTouch(){}
	virtual void OnUpdate(const float deltaTime){}

	void setPosition(const glm::vec2& position) { m_position = position; }
	void setVelocity (const glm::vec2& velocity) { m_velocity = velocity; }

	glm::vec2& getPosition() { return m_position; }
	glm::vec2& getVelocity() { return m_velocity; }


protected:
	glm::vec2 m_position = {0,0};
	glm::vec2 m_velocity = {0,0};
};
