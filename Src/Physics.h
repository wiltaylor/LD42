#pragma once
#include "GameObject.h"
#include "AssetLoader.h"
#include "Level.h"

typedef enum {
	HIT_NOTHING,
	HIT_PLAYER,
	HIT_OBJECT,
	HIT_WALL
} HITTYPE;

class Physics
{
public:
	Physics(Player* player, AssetLoader* assetLoader) : m_player{ player }, m_assetLoader{ assetLoader } {}
	~Physics() = default;

	void setLevel(Level* level) { m_level = level; }

	HITTYPE testPosition(glm::vec2 position);
	HITTYPE testPosition(glm::vec2 position, bool skipPlayer, GameObject* self);
	HITTYPE testPosition(glm::vec2 position, bool skipPlayer, GameObject* self, bool projectile);
	HITTYPE testProjectile(glm::vec2 position, bool skipPlayer, GameObject* self);
	bool checkLineOfSite(glm::vec2 origin, glm::vec2 dest);

	void update(float deltaTime);
	void useInFront() const;

	GameObject* getLastHitObject() { return m_lastHitObject; }

private:
	Level* m_level;
	Player* m_player;
	GameObject* m_lastHitObject;
	const float m_tolerance = 0.3f;
	AssetLoader* m_assetLoader;
	float m_stepAmmount = 0.5f;

};
