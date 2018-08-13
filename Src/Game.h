#pragma once
#include "Renderer.h"
#include "RayCastRender.h"
#include "Player.h"
#include "Input.h"
#include "Physics.h"
#include "AssetLoader.h"
#include "AudioSystem.h"
#include "HudRenderer.h"
#include <chrono>

class Game
{
public:
	Game();
	~Game();

	void runLoop();
	bool isRunning() { return m_running; }

private:
	bool m_running = true;
	Renderer* m_renderer;
	HUDRenderer* m_hudRenderer;
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
	const float m_ShootcoolDown = 1.0f;

	SoundClip* m_pickupSound;
	float m_timeStep = 0.1f;
	float m_currentStep = 0;
	std::chrono::time_point<std::chrono::system_clock> m_tp1 = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> m_tp2 = std::chrono::system_clock::now();
};
