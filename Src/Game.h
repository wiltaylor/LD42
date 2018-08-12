#pragma once
#include "Renderer.h"
#include "RayCastRender.h"
#include "Player.h"
#include "Input.h"
#include "GameObject.h"
#include "Physics.h"
#include "AssetLoader.h"
#include "AudioSystem.h"

class Game
{
public:
	Game();
	~Game();

	void start();	

private:
	bool m_running = true;
	Renderer* m_renderer;
	RayCastRenderer* m_rayCastRenderer;
	Player m_player;
	Input m_input;
	Physics* m_physics;
	AssetLoader m_assetLoader;
	Level* m_level;
	AudioSystem m_audio;
		
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);
	float m_coolDown = 0.0f;
	const float m_ShootcoolDown = 3.0f;

	SoundClip* m_pickupSound;
};
