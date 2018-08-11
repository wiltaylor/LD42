
#include "Level.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "PickUp.h"
#include <algorithm>

Level::Level(const std::string& filename, AssetLoader* assetLoader)
{
	const auto pillarTexture = assetLoader->getTextureId("pillar");
	const auto chestTexture = assetLoader->getTextureId("chest");

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
            int index = y * m_width + x;
			std::string line = levelData[y];

            switch(line[x])
            {
                case '#':
                    m_levelBlocks[index].passable = false;
                    m_levelBlocks[index].textureIndex = 1;
                    break;
				case '@':
				{
					auto piller = new GameObject();

					piller->visible = true;
					piller->vx = 0.0f;
					piller->vy = 0.0f;
					piller->x = static_cast<float>(x);
					piller->y = static_cast<float>(y);
					piller->solid = true;
					piller->texture = pillarTexture;

					m_gameObjects.push_back(piller);

					m_levelBlocks[index].passable = true;
					m_levelBlocks[index].textureIndex = 0;
				}
					break;
				case 't':
				{
					auto chest = new PickUp();

					chest->visible = true;
					chest->vx = 0.0f;
					chest->vy = 0.0f;
					chest->x = static_cast<float>(x);
					chest->y = static_cast<float>(y);
					chest->solid = false;
					chest->texture = chestTexture;

					m_gameObjects.push_back(chest);

					m_levelBlocks[index].passable = true;
					m_levelBlocks[index].textureIndex = 0;
				}
				break;
                case 'p':
                    m_playerStartX = x;
                    m_playerStartY = y;
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

void Level::update()
{
	std::remove_if(m_gameObjects.begin(), m_gameObjects.end(), [&](GameObject* o)
	{
		if(o->cleanUp)
		{
			delete o;
			return true;
		}
		return false;
	});
}
