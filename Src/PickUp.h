#pragma once
#include "GameObject.h"
#include "LevelBlock.h"
#include "Player.h"

class PickUp : public GameObject
{
public:
	PickUp()
	{
		type = OBJECT_PICKUP;
	};

	int CoinsOnPickUp = 0;
	LockLevel Key = DOORLOCK_NONE;

	void onPlayerTouch(Player* m_player) override;
};