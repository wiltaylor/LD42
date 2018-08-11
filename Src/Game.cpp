#include "Game.h"
#include <chrono>
#include "AssetLoader.h"
#include "Level.h"

Game::Game()
{
	//Load game textures
	m_assetLoader.loadTexture("wall.png", "wall");
	m_assetLoader.loadTexture("pillar.png", "pillar");
	m_assetLoader.loadTexture("chest.png", "chest");
	m_assetLoader.loadTexture("MagicBolt.png", "magicbolt");
	m_assetLoader.loadTexture("hellblob.png", "hellblob");

	m_renderer = new Renderer(800, 600);
	m_rayCastRenderer = new RayCastRenderer(m_renderer, &m_assetLoader);
}

Game::~Game()
{
	delete m_renderer;
}

void Game::start()
{
	m_level = new Level("level1.txt", &m_assetLoader, &m_player);
	m_physics = new Physics(m_level);

	m_rayCastRenderer->setMapData(m_level, m_level->getWidth(), m_level->getHeight());
	
	m_player.setX(static_cast<float>(m_level->getPlayerStartX()));
	m_player.setY(static_cast<float>(m_level->getPlayerStartY()));

	long timeStep = 1000000;
	long currentStep = 0;

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();	

	while(m_running)
	{
		// Handle Timing
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float ElapsedTime = elapsedTime.count();
		
		m_renderer->setWindowTitle("FPS: " + std::to_string(1.0f / ElapsedTime) + "Angle: " + std::to_string(m_player.getA()));
		update(ElapsedTime);
	}
}

void Game::update(float deltaTime)
{
	if (m_coolDown > 0)
		m_coolDown -= deltaTime;

	m_renderer->cleanPixelBuffer();

	m_input.update();
	m_physics->setPlayerPosition(m_player.getX(), m_player.getY(), m_player.getA());

	if (m_input.keyDown(SDL_SCANCODE_ESCAPE) || m_input.hasQuit())
		m_running = false;

	if(m_input.keyDown(SDL_SCANCODE_A))
		m_player.setA(m_player.getA() - 0.8f * deltaTime);

	if (m_input.keyDown(SDL_SCANCODE_D))
		m_player.setA(m_player.getA() + 0.8f * deltaTime);

	if(m_input.keyDown(SDL_SCANCODE_W))
	{

		float newX = m_player.getX() + sinf(m_player.getA()) * 5.0f * deltaTime;
		float newY = m_player.getY() + cosf(m_player.getA()) * 5.0f * deltaTime;

		if (m_physics->testPosition(newX, newY, true) == HIT_NOTHING)
		{
			m_player.setX(newX);
			m_player.setY(newY);

			if (m_physics->getLastHitObject() != nullptr)
				m_physics->getLastHitObject()->OnPlayerTouch();
		}
	}

	if (m_input.keyDown(SDL_SCANCODE_S))
	{
		float newX = m_player.getX() - sinf(m_player.getA()) * 5.0f * deltaTime;
		float newY = m_player.getY() - cosf(m_player.getA()) * 5.0f * deltaTime;

		if (m_physics->testPosition(newX, newY, true) == HIT_NOTHING)
		{
			m_player.setX(newX);
			m_player.setY(newY);

			if (m_physics->getLastHitObject() != nullptr)
				m_physics->getLastHitObject()->OnPlayerTouch();
		}
	}

	if(m_input.keyDown(SDL_SCANCODE_Q))
	{
		float newX = m_player.getX() - cosf(m_player.getA()) * 5.0f * deltaTime;
		float newY = m_player.getY() + sinf(m_player.getA()) * 5.0f * deltaTime;

		if (m_physics->testPosition(newX, newY, true) == HIT_NOTHING)
		{
			m_player.setX(newX);
			m_player.setY(newY);

			if (m_physics->getLastHitObject() != nullptr)
				m_physics->getLastHitObject()->OnPlayerTouch();
		}
	}

	if (m_input.keyDown(SDL_SCANCODE_E))
	{
		float newX = m_player.getX() + cosf(m_player.getA()) * 5.0f * deltaTime;
		float newY = m_player.getY() - sinf(m_player.getA()) * 5.0f * deltaTime;

		if (m_physics->testPosition(newX, newY, true) == HIT_NOTHING)
		{
			m_player.setX(newX);
			m_player.setY(newY);

			if (m_physics->getLastHitObject() != nullptr)
				m_physics->getLastHitObject()->OnPlayerTouch();
		}
	}

	if(m_input.keyDown(SDL_SCANCODE_SPACE) && m_coolDown <= 0)
	{		
		auto fireball = new GameObject();

		fireball->visible = true;
		fireball->physicsObject = true;
		fireball->vx = sinf(m_player.getA()) * 4.0f;
		fireball->vy = cosf(m_player.getA()) * 4.0f;
		fireball->x = m_player.getX();
		fireball->y = m_player.getY();
		fireball->texture = m_assetLoader.getTextureId("magicbolt");
		fireball->projectile = true;

		m_level->AddObject(fireball);

		m_coolDown = m_ShootcoolDown;
	}

	m_physics->update(deltaTime);
	m_level->update(deltaTime);
	m_rayCastRenderer->setPlayerPosition(m_player.getX(), m_player.getY(), m_player.getA());
	m_rayCastRenderer->Draw();
	m_rayCastRenderer->drawObjects();
	m_renderer->flip();
}


