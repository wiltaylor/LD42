#include "Game.h"
#include "AssetLoader.h"
#include "Level.h"
#include <iostream>

Game::Game()
{
	std::cout << "starting up game..." << std::endl;
	
	m_renderer = new Renderer(800, 600);
	m_hudRenderer = new HUDRenderer(m_renderer, &m_player);
	m_rayCastRenderer = new RayCastRenderer(m_renderer, &m_assetLoader, &m_player);

	std::cout << "Loading image assets..." << std::endl;

	//Load game textures
	m_assetLoader.loadTexture("wall.png", "wall");
	m_assetLoader.loadTexture("pillar.png", "pillar");
	m_assetLoader.loadTexture("chest.png", "chest");
	m_assetLoader.loadTexture("magicbolt.png", "magicbolt");
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
	m_assetLoader.loadTexture("portal.png", "portal");
	m_assetLoader.loadTexture("portal.png", "endportal");
	m_assetLoader.loadTexture("skellington1.png", "skellington1");
	m_assetLoader.loadTexture("skellington2.png", "skellington2");
	m_assetLoader.loadTexture("skellington3.png", "skellington3");
	m_assetLoader.loadTexture("skellingtondeath1.png", "skellingtondeath1");
	m_assetLoader.loadTexture("skellingtondeath2.png", "skellingtondeath2");
	m_assetLoader.loadTexture("plant.png", "plant");
	m_assetLoader.loadTexture("blood.png", "blood");
	m_assetLoader.loadTexture("barrel.png", "barrel");

	std::cout << "Loading sound assets..." << std::endl;
	
	m_assetLoader.loadSoundClip("pickup.wav", "pickup");
	m_assetLoader.loadSoundClip("fire.ogg", "fire");
	m_assetLoader.loadSoundClip("door.ogg", "door");
	m_assetLoader.loadSoundClip("door_rejected.wav", "doorreject");
	m_assetLoader.loadSoundClip("portal.ogg", "portal");
	m_assetLoader.loadSoundClip("enemysee.ogg", "enemysee");
	m_assetLoader.loadSoundClip("skeletondeath.ogg", "skellingtondeath");
	m_assetLoader.loadSoundClip("hit.ogg", "hit");
	m_assetLoader.loadSoundClip("playerhit.ogg", "playerhit");

	std::cout << "Loading game systems..." << std::endl;


	m_pickupSound = m_assetLoader.getSoundClip("pickup");
	m_physics = new Physics(&m_player, &m_assetLoader);
	m_level = new Level(&m_assetLoader, &m_player, m_hudRenderer, m_physics);

	m_physics->setLevel(m_level);

	m_level->loadLevel(1);

	m_rayCastRenderer->setMapData(m_level, m_level->getWidth(), m_level->getHeight());

	m_renderer->setWindowTitle("Temple of Hate");

	std::cout << "Finished loading game..." << std::endl;


}

Game::~Game()
{
	delete m_renderer;
}

void Game::runLoop()
{
	// Handle Timing
	m_tp2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
	m_tp1 = m_tp2;
	float ElapsedTime = elapsedTime.count();
	m_currentStep += ElapsedTime;

	if (m_currentStep > m_timeStep)
	{
		fixedUpdate(m_timeStep);
		m_currentStep -= m_timeStep;
	}
	update(ElapsedTime);
}


void Game::fixedUpdate(float deltaTime)
{
	//Player is dead;
	if (m_player.getHp() <= 0 || m_hudRenderer->showingLogo())
		return;

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

	if(m_input.keyDown(SDL_SCANCODE_A) && !m_hudRenderer->showingLogo())
		m_player.setAngle(m_player.getAngle() - 1.5f * deltaTime);

	if (m_input.keyDown(SDL_SCANCODE_D) && !m_hudRenderer->showingLogo())
		m_player.setAngle(m_player.getAngle() + 1.5f * deltaTime);

	if(m_input.keyDown(SDL_SCANCODE_W) && m_player.getHp() > 0 && !m_hudRenderer->showingLogo())
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

	if (m_input.keyDown(SDL_SCANCODE_S) && m_player.getHp() > 0 && !m_hudRenderer->showingLogo())
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

	if(m_input.keyDown(SDL_SCANCODE_Q) && m_player.getHp() > 0 && !m_hudRenderer->showingLogo())
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

	if (m_input.keyDown(SDL_SCANCODE_E) && m_player.getHp() > 0 && !m_hudRenderer->showingLogo())
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

	if(m_input.keyDown(SDL_SCANCODE_SPACE) && m_coolDown <= 0 && m_player.getHp() > 0 && !m_hudRenderer->showingLogo())
	{
		m_physics->useInFront();
		m_coolDown = m_ShootcoolDown;
	}

	if (m_input.keyDown(SDL_SCANCODE_SPACE) && m_hudRenderer->showingLogo())
		m_hudRenderer->hideLogo();

	if (m_input.keyDown(SDL_SCANCODE_SPACE) && m_player.getHp() <= 0)
	{
		m_player.reset();
		m_level->loadLevel(m_level->getCurrentLevel());

	}

	if((m_input.keyDown(SDL_SCANCODE_RCTRL) || m_input.keyDown(SDL_SCANCODE_LCTRL)) && m_coolDown <= 0 && m_player.getHp() > 0 && !m_hudRenderer->showingLogo())
	{		
		auto fireball = m_level->getFreeProjectile();

		if(fireball != nullptr)
		{
			fireball->visible = true;
			fireball->cleanUp = false;
			fireball->playerOwned = true;
			fireball->setVelocity({ sinf(m_player.getAngle()) * 10.0f, cosf(m_player.getAngle()) * 10.0f });
			fireball->setPosition(m_player.getPosition());
			
			m_coolDown = m_ShootcoolDown;
			m_hudRenderer->attack();

			m_assetLoader.getSoundClip("fire")->play();
		}
	}

	m_rayCastRenderer->Draw();
	m_rayCastRenderer->drawObjects();
	m_renderer->flipPixels();
	m_hudRenderer->update(deltaTime);
	m_hudRenderer->draw();
	m_renderer->flip();
}


