#pragma once
#include "GameObject.h"
#include "LevelBlock.h"
#include "Player.h"

struct PickUp : public GameObject
{

	int CoinsOnPickUp = 0;
	LockLevel Key = DOORLOCK_NONE;

	void OnPlayerTouch(Player* m_player) override;


};