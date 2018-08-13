
#include "Level.h"
#include <fstream>
#include <vector>
#include <string>
#include "PickUp.h"
#include <algorithm>
#include "NPC.h"
#include "Portal.h"

void Level::loadLevel(int level)
{
	m_currentLevel = level;
	const auto filename = "level" + std::to_string(level) + ".txt";

//	for (auto &obj : m_gameObjects)
//		delete obj;

	m_gameObjects.clear();

	delete m_levelBlocks;

	const auto pillarTexture = m_assetLoader->getTextureId("pillar");
	const auto chestTexture = m_assetLoader->getTextureId("chest");
	const auto hellBlobTexture = m_assetLoader->getTextureId("hellblob");
	const auto doorTexture = m_assetLoader->getTextureId("door");
	const auto wallTexture = m_assetLoader->getTextureId("wall");
	const auto boltTexture = m_assetLoader->getTextureId("magicbolt");
	const auto redkeyTexture = m_assetLoader->getTextureId("redkey");
	const auto redDoorTexture = m_assetLoader->getTextureId("reddoor");
	const auto greenkeyTexture = m_assetLoader->getTextureId("greenkey");
	const auto greenDoorTexture = m_assetLoader->getTextureId("greendoor");
	const auto bluekeyTexture = m_assetLoader->getTextureId("bluekey");
	const auto blueDoorTexture = m_assetLoader->getTextureId("bluedoor");
	const auto goldkeyTexture = m_assetLoader->getTextureId("goldkey");
	const auto goldDoorTexture = m_assetLoader->getTextureId("golddoor");
	const auto portalTexture = m_assetLoader->getTextureId("portal");
	const auto endPortalTexture = m_assetLoader->getTextureId("endportal");


	for (int i = 0; i < m_MaxProjectiles; i++)
	{
		auto projectile = new GameObject;

		projectile->setPosition({ 0,0 });
		projectile->setVelocity({ 0,0 });
		projectile->cleanUp = true;
		projectile->texture = boltTexture;
		projectile->visible = true;
		projectile->projectile = true;
		projectile->physicsObject = true;
		projectile->dmg = 1;

		m_gameObjects.push_back(projectile);
	}

	std::ifstream levelFile;
	levelFile.open(filename, std::ifstream::in);

	std::string line;
	std::vector<std::string> levelData;

	while (std::getline(levelFile, line))
	{
		levelData.push_back(line);
	}

	levelFile.close();

	m_height = levelData.size();
	m_width = levelData.at(0).size();

	m_levelBlocks = new LevelBlock[m_height * m_width];

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			const int index = y * m_width + x;
			auto line = levelData[y];

			m_levelBlocks[index].icon = line[x];

			switch (line[x])
			{
			case '#':
				m_levelBlocks[index].passable = false;
				m_levelBlocks[index].textureIndex = wallTexture;
				break;
			case '@':
			{
				auto piller = new GameObject();

				piller->visible = true;
				piller->setVelocity({ 0.0f, 0.0f });
				piller->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				piller->solid = true;
				piller->texture = pillarTexture;

				m_gameObjects.push_back(piller);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
			}
			case '%':
			{
				auto plant = new GameObject();

				plant->visible = true;
				plant->setVelocity({ 0.0f, 0.0f });
				plant->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				plant->solid = false;
				plant->texture = m_assetLoader->getTextureId("plant");

				m_gameObjects.push_back(plant);

				m_levelBlocks[index].passable = true;
 				m_levelBlocks[index].textureIndex = 0;
				break;
			}
			case '&':
			{
				auto blood = new GameObject();

				blood->visible = true;
				blood->setVelocity({ 0.0f, 0.0f });
				blood->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				blood->solid = false;
				blood->texture = m_assetLoader->getTextureId("blood");

				m_gameObjects.push_back(blood);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
			}
			break;
			case '^':
			{
				auto blood = new GameObject();

				blood->visible = true;
				blood->setVelocity({ 0.0f, 0.0f });
				blood->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				blood->solid = false;
				blood->texture = m_assetLoader->getTextureId("barrel");

				m_gameObjects.push_back(blood);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
			}
			break;
			case 'h':
			{
				auto hellblob = new NPC(m_player, m_assetLoader, m_physics);

				hellblob->visible = true;
				hellblob->setVelocity({ 0.0f, 0.0f });
				hellblob->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				hellblob->solid = false;
				hellblob->texture = hellBlobTexture;
				hellblob->physicsObject = true;
				hellblob->projectile = false;
				hellblob->dmg = 1.0f;
				hellblob->addFrame(hellBlobTexture);

				m_gameObjects.push_back(hellblob);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
			}
			break;

			case 's':
			{
				auto skellington = new NPC(m_player, m_assetLoader, m_physics);

				skellington->visible = true;
				skellington->setVelocity({ 0.0f, 0.0f });
				skellington->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				skellington->solid = false;
				skellington->texture = 0;
				skellington->physicsObject = true;
				skellington->projectile = false;
				skellington->dmg = 1.0f;
				skellington->addFrame(m_assetLoader->getTextureId("skellington2"));
				skellington->addFrame(m_assetLoader->getTextureId("skellington3"));
				skellington->addDeathFrame(m_assetLoader->getTextureId("skellingtondeath1"));
				skellington->addDeathFrame(m_assetLoader->getTextureId("skellingtondeath2"));
				skellington->setSightSound("enemysee");
				skellington->setDeathSound("skellingtondeath");
				skellington->setOnHitSound("hit");

				m_gameObjects.push_back(skellington);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
			}
			break;
			case 'r':
			{
				auto key = new PickUp();

				key->visible = true;
				key->setVelocity({ 0.0f, 0.0f });
				key->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				key->solid = false;
				key->texture = redkeyTexture;
				key->Key = DOORLOCK_RED;

				m_gameObjects.push_back(key);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
				break;
			}
			case 'g':
			{
				auto key = new PickUp();

				key->visible = true;
				key->setVelocity({ 0.0f, 0.0f });
				key->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				key->solid = false;
				key->texture = greenkeyTexture;
				key->Key = DOORLOCK_GREEN;

				m_gameObjects.push_back(key);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
				break;
			}
			case 'b':
			{
				auto key = new PickUp();

				key->visible = true;
				key->setVelocity({ 0.0f, 0.0f });
				key->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				key->solid = false;
				key->texture = bluekeyTexture;
				key->Key = DOORLOCK_BLUE;

				m_gameObjects.push_back(key);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
				break;
			}
			case 'o':
			{
				auto key = new PickUp();

				key->visible = true;
				key->setVelocity({ 0.0f, 0.0f });
				key->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				key->solid = false;
				key->texture = goldkeyTexture;
				key->Key = DOORLOCK_GOLD;

				m_gameObjects.push_back(key);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
				break;
			}
			case 't':
			{
				auto chest = new PickUp();

				chest->visible = true;
				chest->setVelocity({ 0.0f, 0.0f });
				chest->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				chest->solid = false;
				chest->texture = chestTexture;

				m_gameObjects.push_back(chest);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
			}
			break;
			case 'E':
			{
				auto portal = new Portal(this, m_hudRenderer, m_assetLoader);

				portal->visible = true;
				portal->setVelocity({ 0.0f, 0.0f });
				portal->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				portal->solid = false;
				portal->texture = portalTexture;

				m_gameObjects.push_back(portal);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
			}
				break;
			case '!':
			{
				auto portal = new Portal(this, m_hudRenderer, m_assetLoader);

				portal->visible = true;
				portal->setVelocity({ 0.0f, 0.0f });
				portal->setPosition({ static_cast<float>(x), static_cast<float>(y) });
				portal->solid = false;
				portal->texture = endPortalTexture;
				portal->setEndPortal();

				m_gameObjects.push_back(portal);

				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
			}
			break;
			case 'D':
				m_levelBlocks[index].passable = false;
				m_levelBlocks[index].textureIndex = doorTexture;
				m_levelBlocks[index].door = true;
				break;
			case 'R':
				m_levelBlocks[index].passable = false;
				m_levelBlocks[index].textureIndex = redDoorTexture;
				m_levelBlocks[index].door = true;
				m_levelBlocks[index].lock = DOORLOCK_RED;
				break;
			case 'G':
				m_levelBlocks[index].passable = false;
				m_levelBlocks[index].textureIndex = greenDoorTexture;
				m_levelBlocks[index].door = true;
				m_levelBlocks[index].lock = DOORLOCK_GREEN;
				break;
			case 'B':
				m_levelBlocks[index].passable = false;
				m_levelBlocks[index].textureIndex = blueDoorTexture;
				m_levelBlocks[index].door = true;
				m_levelBlocks[index].lock = DOORLOCK_BLUE;
				break;
			case 'O':
				m_levelBlocks[index].passable = false;
				m_levelBlocks[index].textureIndex = goldDoorTexture;
				m_levelBlocks[index].door = true;
				m_levelBlocks[index].lock = DOORLOCK_GOLD;
				break;
			case 'p':
				m_player->setPosition({ x, y });
				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
				break;
			default:
				m_levelBlocks[index].passable = true;
				m_levelBlocks[index].textureIndex = 0;
				break;
			}
		}
	}
}


Level::~Level() {
    delete[] m_levelBlocks;
}

GameObject* Level::getFreeProjectile()
{
	for(auto &p : m_gameObjects)
	{
		if (p->cleanUp && p->projectile)
			return p;
	}

	return nullptr;
}

void Level::update(const float deltaTime)
{
	std::remove_if(m_gameObjects.begin(), m_gameObjects.end(), [&](GameObject* o)
	{
		if(o->cleanUp && !o->projectile)
		{
			//delete o;
			return true;
		}
		return false;
	});

	for (auto &o : m_gameObjects)
		o->onUpdate(deltaTime);
}
