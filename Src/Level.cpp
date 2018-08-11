
#include "Level.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

Level::Level(const std::string& filename)
{
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
                case 'p':
                    m_playerStartX = x;
                    m_playerStartY = y;
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