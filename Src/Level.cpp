
#include "Level.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "PickUp.h"
#include <algorithm>
#include "NPC.h"

Level::Level(const std::string& filename, AssetLoader* assetLoader, Player* player)
{
	const auto pillarTexture = assetLoader->getTextureId("pillar");
	const auto chestTexture = assetLoader->getTextureId("chest");
	const auto hellBlobTexture = assetLoader->getTextureId("hellblob");
	const auto doorTexture = assetLoader->getTextureId("door");
	const auto wallTexture = assetLoader->getTextureId("wall");
	const auto boltTexture = assetLoader->getTextureId("magicbolt");
	const auto redkeyTexture = assetLoader->getTextureId("redkey");
	const auto redDoorTexture = assetLoader->getTextureId("reddoor");
	const auto greenkeyTexture = assetLoader->getTextureId("greenkey");
	const auto greenDoorTexture = assetLoader->getTextureId("greendoor");
	const auto bluekeyTexture = assetLoader->getTextureId("bluekey");
	const auto blueDoorTexture = assetLoader->getTextureId("bluedoor");
	const auto goldkeyTexture = assetLoader->getTextureId("goldkey");
	const auto goldDoorTexture = assetLoader->getTextureId("golddoor");

	m_player = player;

	for(int i =0 ; i < m_MaxProjectiles; i++)
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

	while(std::getline(levelFile, line))
	{
        levelData.push_back(line);
	}

	levelFile.close();

	m_height = levelData.size();
	m_width = levelData.at(0).size();
	
    m_levelBlocks = new LevelBlock[m_height * m_width];

    for(int y = 0; y < m_height; y++)
    {
        for(int x = 0; x < m_width; x++)
        {
	        const int index = y * m_width + x;
	        auto line = levelData[y];

            switch(line[x])
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
					piller->setPosition({static_cast<float>(x), static_cast<float>(y)});
					piller->solid = true;
					piller->texture = pillarTexture;

					m_gameObjects.push_back(piller);

					m_levelBlocks[index].passable = true;
					m_levelBlocks[index].textureIndex = 0;
				}
					break;
				case 'h':
				{
					auto hellblob = new NPC(m_player);

					hellblob->visible = true;
					hellblob->setVelocity({ 0.0f, 0.0f });
					hellblob->setPosition({ static_cast<float>(x), static_cast<float>(y) });
					hellblob->solid = false;
					hellblob->texture = hellBlobTexture;
					hellblob->physicsObject = true;
					hellblob->projectile = false;
					hellblob->dmg = 1.0f;

					m_gameObjects.push_back(hellblob);

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


	for (int y = 0; y < m_height; y++)
	{

		for (int x = 0; x < m_width; x++)
		{
			if (getBlock(x, y)->passable)
			{
				std::cout << ".";
			}
			else 
			{
				std::cout << "#";
			}
		}

		std::cout << std::endl;
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
