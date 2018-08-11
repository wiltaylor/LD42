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
	NPC(Player* player) : m_player{player} {}

	void OnUpdate(const float deltaTime) override;

private:

	bool m_hostile = true;
	NPCSTATE m_state = NPC_Idle;
	Player* m_player;

	const float m_maxDistance = 16.0f;
	const float m_maxSpeed = 0.5f;
	const float m_tollerance = 0.1f;
};
