#pragma once
#include "GameObject.h"

struct PickUp : public GameObject
{

	int CoinsOnPickUp = 0;

	void OnPlayerTouch() override;


};