#pragma once
#include <string>
#include "LevelBlock.h"
#include "GameObject.h"
#include <vector>
#include "Player.h"

class Level
{
public:
    explicit Level(const std::string& filename, AssetLoader* assetLoader, Player* player);
    ~Level();

    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
	const std::vector<GameObject*> &getGameObjects() { return m_gameObjects; }
	GameObject* getFreeProjectile();

	void update(const float deltaTime);


    LevelBlock* getBlock(const int x, const int y)
    {
        return &m_levelBlocks[y * m_width + x];
    }

private:
    unsigned int m_ceilingColour = 0;
    unsigned int m_floorColour = 0;

    int m_width;
    int m_height;
	Player* m_player;

    LevelBlock* m_levelBlocks;
	std::vector<GameObject*> m_gameObjects;


	const int m_MaxProjectiles = 20;
};
