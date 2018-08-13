#pragma once
#include "AssetLoader.h"
#include <glm/vec2.hpp>
#include "Player.h"

typedef enum
{
	OBJECT_NPC,
	OBJECT_PICKUP,
	OBJECT_PROJECTILE
}GAMEOBJECT_TYPE;

class GameObject
{
public:
	GameObject(): type{OBJECT_NPC} {}
	virtual ~GameObject() = default;

	bool visible = true;
	int texture = 0;
	bool physicsObject = false;
	bool solid = false;
	bool cleanUp = false;
	bool projectile = false;
	bool playerOwned = false;
	float dmg = 0.0f;
	GAMEOBJECT_TYPE type;

	virtual void onPlayerTouch(Player* player){}
	virtual void onUpdate(const float deltaTime){}
	virtual void onHitWithProjectile(float dmg) {}

	void setPosition(const glm::vec2& position) { m_position = position; }
	void setVelocity (const glm::vec2& velocity) { m_velocity = velocity; }

	glm::vec2& getPosition() { return m_position; }
	glm::vec2& getVelocity() { return m_velocity; }


protected:
	glm::vec2 m_position = {0,0};
	glm::vec2 m_velocity = {0,0};
};
