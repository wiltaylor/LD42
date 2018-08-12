#pragma once
#include "GameObject.h"
#include "Player.h"
#include <vector>
#include "Physics.h"

typedef enum
{
	NPC_Idle,
	NPC_Attack
} NPCSTATE;

class NPC : public GameObject
{
public:
	NPC(Player* player, AssetLoader* assetLoader, Physics* physics) : m_player{ player }, m_assetLoader{assetLoader}, m_physics{physics}
	{
		type = OBJECT_NPC;
	}

	void onUpdate(const float deltaTime) override;
	void onHitWithProjectile(float dmg) override;
	void addFrame(int id) { m_frames.push_back(id); }
	void addDeathFrame(int id) { m_deathFrames.push_back(id); }
	void setSightSound(const std::string& sound) { m_sightSound = sound; }

private:
	bool m_isDead = false;
	bool m_hasSeen = false;
	std::string m_sightSound = "";

	NPCSTATE m_state = NPC_Idle;
	Player* m_player;

	const float m_maxDistance = 16.0f;
	const float m_maxSpeed = 0.5f;
	float m_hp = 1.0f;

	float m_frameTime = 1.0f;
	float m_currentFrameTime = 0.0f;
	int m_currentFrame = 0;
	std::vector<int> m_frames;
	std::vector<int> m_deathFrames;

	AssetLoader* m_assetLoader;
	Physics* m_physics;
	float m_deathTimeOut = 10.0f;

};
