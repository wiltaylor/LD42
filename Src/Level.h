#pragma once
#include <string>
#include "LevelBlock.h"
class Level
{
public:
    explicit Level(const std::string& filename);
    ~Level();

    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    int getPlayerStartX() { return m_playerStartX; }
    int getPlayerStartY() { return m_playerStartY; }

    const LevelBlock* getBlock(int x, int y)
    {
        return &m_levelBlocks[y * m_width + x];
    }

private:
    unsigned int m_ceilingColour = 0;
    unsigned int m_floorColour = 0;

    int m_width;
    int m_height;
    int m_playerStartX;
    int m_playerStartY;

    LevelBlock* m_levelBlocks;

};
