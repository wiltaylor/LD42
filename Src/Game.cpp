#include "Game.h"
#include <chrono>
#include "AssetLoader.h"
#include "Level.h"

Game::Game()
{
	m_renderer = new Renderer(800, 600);
	m_rayCastRenderer = new RayCastRenderer(m_renderer);
}

Game::~Game()
{
	delete m_renderer;
}

void Game::start()
{
	AssetLoader assetloader;

	std::string filename = "pillar.png";


	m_testpillar = new GameObject;

	m_testpillar->vx = 0.0f;
	m_testpillar->vy = 0.0f;
	m_testpillar->x = 8.0f;
	m_testpillar->y = 8.0f;
	m_testpillar->texture = assetloader.loadTexture(filename);

	Level level("level1.txt");
	m_physics = new Physics(&level);

	m_rayCastRenderer->setMapData(&level, level.getWidth(),level.getHeight());
	
	m_player.setX(static_cast<float>(level.getPlayerStartX()));
	m_player.setY(static_cast<float>(level.getPlayerStartY()));

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
	m_renderer->cleanPixelBuffer();

	m_input.update();

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

		if (m_physics->canMove(newX, newY))
		{
			m_player.setX(newX);
			m_player.setY(newY);
		}
	}

	if (m_input.keyDown(SDL_SCANCODE_S))
	{
		float newX = m_player.getX() - sinf(m_player.getA()) * 5.0f * deltaTime;
		float newY = m_player.getY() - cosf(m_player.getA()) * 5.0f * deltaTime;

		if (m_physics->canMove(newX, newY))
		{
			m_player.setX(newX);
			m_player.setY(newY);
		}
	}

	if(m_input.keyDown(SDL_SCANCODE_Q))
	{
		float newX = m_player.getX() - cosf(m_player.getA()) * 5.0f * deltaTime;
		float newY = m_player.getY() + sinf(m_player.getA()) * 5.0f * deltaTime;

		if (m_physics->canMove(newX, newY))
		{
			m_player.setX(newX);
			m_player.setY(newY);
		}
	}

	if (m_input.keyDown(SDL_SCANCODE_E))
	{
		float newX = m_player.getX() + cosf(m_player.getA()) * 5.0f * deltaTime;
		float newY = m_player.getY() - sinf(m_player.getA()) * 5.0f * deltaTime;

		if (m_physics->canMove(newX, newY))
		{
			m_player.setX(newX);
			m_player.setY(newY);
		}
	}


	m_rayCastRenderer->addObject(m_testpillar);

	m_rayCastRenderer->setPlayerPosition(m_player.getX(), m_player.getY(), m_player.getA());
	m_rayCastRenderer->Draw();
	m_rayCastRenderer->drawObjects();

	m_renderer->flip();
}


