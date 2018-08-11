#pragma once
#include "AssetLoader.h"

struct GameObject
{
	bool visible;
	float x;
	float y;
	float vx;
	float vy;
	Texture* texture;
	bool projectile;
	bool solid;
	bool cleanUp;

	virtual void OnPlayerTouch(){}
};
