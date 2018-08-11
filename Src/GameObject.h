#pragma once
#include "AssetLoader.h"

struct GameObject
{

	virtual ~GameObject()
	{
		
	}

	bool visible;
	float x;
	float y;
	float vx;
	float vy;
	int texture;
	bool physicsObject;
	bool solid;
	bool cleanUp;
	bool projectile;

	virtual void OnPlayerTouch(){}
	virtual void OnUpdate(const float deltaTime){}
};
