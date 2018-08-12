#pragma once
#include "GameObject.h"
#include "Player.h"

typedef enum
{
	NPC_Idle,
	NPC_Attack
} NPCSTATE;

class NPC : public GameObject
{
public:
	NPC(Player* player) : m_player{ player }
	{
		type = OBJECT_NPC;
	}

	void onUpdate(const float deltaTime) override;
	void onHitWithProjectile(float dmg) override;

private:

	bool m_hostile = true;
	NPCSTATE m_state = NPC_Idle;
	Player* m_player;

	const float m_maxDistance = 16.0f;
	const float m_maxSpeed = 0.5f;
	float m_hp = 1.0f;
};
