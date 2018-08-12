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
	m_assetLoader.loadTexture("door.png", "door");
	m_assetLoader.loadTexture("reddoor.png", "reddoor");
	m_assetLoader.loadTexture("greendoor.png", "greendoor");
	m_assetLoader.loadTexture("bluedoor.png", "bluedoor");
	m_assetLoader.loadTexture("golddoor.png", "golddoor");
	m_assetLoader.loadTexture("redkey.png", "redkey");
	m_assetLoader.loadTexture("greenkey.png", "greenkey");
	m_assetLoader.loadTexture("bluekey.png", "bluekey");
	m_assetLoader.loadTexture("goldkey.png", "goldkey");

	m_assetLoader.loadSoundClip("pickup.wav", "pickup");
	
	m_renderer = new Renderer(800, 600);
	m_rayCastRenderer = new RayCastRenderer(m_renderer, &m_assetLoader, &m_player);
	m_hudRenderer = new HUDRenderer(m_renderer, &m_player);
}

Game::~Game()
{
	delete m_renderer;
}

void Game::start()
{
	//turn back on before release
	//m_audio.PlayMusic("bgmuisc.mp3");
	//m_audio.SetMusicVolumn(1);

	m_pickupSound = m_assetLoader.getSoundClip("pickup");


	m_level = new Level("level1.txt", &m_assetLoader, &m_player);
	m_physics = new Physics(m_level, &m_player);

	m_rayCastRenderer->setMapData(m_level, m_level->getWidth(), m_level->getHeight());
	
	float timeStep = 0.1f;
	float currentStep = 0;

	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();	

	while(m_running)
	{
		// Handle Timing
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float ElapsedTime = elapsedTime.count();
		currentStep += ElapsedTime;

		if(currentStep > timeStep)
		{
			fixedUpdate(timeStep);
			currentStep -= timeStep;
		}

		m_renderer->setWindowTitle("FPS: " + std::to_string(1.0f / ElapsedTime) + "Angle: " + std::to_string(m_player.getAngle()) + "Pos: " + std::to_string(m_player.getPosition().x) + "/" + std::to_string(m_player.getPosition().y) + "cooldown: " + std::to_string(m_coolDown));
		update(ElapsedTime);
	}
}

void Game::fixedUpdate(float deltaTime)
{
	m_physics->update(deltaTime);
	m_level->update(deltaTime);
}

void Game::update(float deltaTime)
{
	if (m_coolDown > 0)
		m_coolDown -= deltaTime;

	m_renderer->cleanPixelBuffer();

	m_input.update();

	if (m_input.keyDown(SDL_SCANCODE_ESCAPE) || m_input.hasQuit())
		m_running = false;

	if(m_input.keyDown(SDL_SCANCODE_A))
		m_player.setAngle(m_player.getAngle() - 0.8f * deltaTime);

	if (m_input.keyDown(SDL_SCANCODE_D))
		m_player.setAngle(m_player.getAngle() + 0.8f * deltaTime);

	if(m_input.keyDown(SDL_SCANCODE_W))
	{
		const auto pos = m_player.getPosition();
		const glm::vec2 newPosition(
			{ 
				pos.x + sinf(m_player.getAngle()) * 5.0f * deltaTime, 
				pos.y + cosf(m_player.getAngle()) * 5.0f * deltaTime 
			});	
	
		if (m_physics->testPosition(newPosition, true, nullptr) == HIT_NOTHING)
		{
			m_player.setPosition(newPosition);

			if (m_physics->getLastHitObject() != nullptr)
			{
				m_physics->getLastHitObject()->onPlayerTouch(&m_player);

				if (m_physics->getLastHitObject()->type == OBJECT_PICKUP)
					m_pickupSound->play();
			}
		}
	}

	if (m_input.keyDown(SDL_SCANCODE_S))
	{
		const auto pos = m_player.getPosition();
		const glm::vec2 newPosition(
			{
				pos.x - sinf(m_player.getAngle()) * 5.0f * deltaTime,
				pos.y - cosf(m_player.getAngle()) * 5.0f * deltaTime
			});

		if (m_physics->testPosition(newPosition, true, nullptr) == HIT_NOTHING)
		{
			m_player.setPosition(newPosition);

			if (m_physics->getLastHitObject() != nullptr)
			{
				m_physics->getLastHitObject()->onPlayerTouch(&m_player);

				if (m_physics->getLastHitObject()->type == OBJECT_PICKUP)
					m_pickupSound->play();
			}
		}
	}

	if(m_input.keyDown(SDL_SCANCODE_Q))
	{
		const auto pos = m_player.getPosition();
		const glm::vec2 newPosition(
			{
				pos.x - cosf(m_player.getAngle()) * 5.0f * deltaTime,
				pos.y + sinf(m_player.getAngle()) * 5.0f * deltaTime
			});


		if (m_physics->testPosition(newPosition, true, nullptr) == HIT_NOTHING)
		{
			m_player.setPosition(newPosition);

			if (m_physics->getLastHitObject() != nullptr)
			{
				m_physics->getLastHitObject()->onPlayerTouch(&m_player);

				if (m_physics->getLastHitObject()->type == OBJECT_PICKUP)
					m_pickupSound->play();
			}
		}
	}

	if (m_input.keyDown(SDL_SCANCODE_E))
	{
		const auto pos = m_player.getPosition();
		const glm::vec2 newPosition(
			{
				pos.x + cosf(m_player.getAngle()) * 5.0f * deltaTime,
				pos.y - sinf(m_player.getAngle()) * 5.0f * deltaTime
			});

		if (m_physics->testPosition(newPosition, true, nullptr) == HIT_NOTHING)
		{
			m_player.setPosition(newPosition);

			if (m_physics->getLastHitObject() != nullptr)
			{
				m_physics->getLastHitObject()->onPlayerTouch(&m_player);

				if(m_physics->getLastHitObject()->type == OBJECT_PICKUP)
					m_pickupSound->play();
			}
		}
	}

	if(m_input.keyDown(SDL_SCANCODE_SPACE) && m_coolDown <= 0)
	{
		m_physics->useInFront();
		m_coolDown = m_ShootcoolDown;
	}

	if((m_input.keyDown(SDL_SCANCODE_RCTRL) || m_input.keyDown(SDL_SCANCODE_LCTRL)) && m_coolDown <= 0)
	{		
		auto fireball = m_level->getFreeProjectile();

		if(fireball != nullptr)
		{
			fireball->visible = true;
			fireball->cleanUp = false;
			fireball->playerOwned = true;
			fireball->setVelocity({ sinf(m_player.getAngle()) * 4.0f, cosf(m_player.getAngle()) * 4.0f });
			fireball->setPosition(m_player.getPosition());
			
			m_coolDown = m_ShootcoolDown;
		}
	}

	m_rayCastRenderer->Draw();
	m_rayCastRenderer->drawObjects();
	m_renderer->flipPixels();
	m_hudRenderer->update();
	m_hudRenderer->draw();
	m_renderer->flip();
}


