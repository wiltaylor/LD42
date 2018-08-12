#pragma once
#include <string>
#include "LevelBlock.h"
#include "GameObject.h"
#include <vector>
#include "Player.h"

class Level
{
public:
	explicit Level(AssetLoader* assetLoader, Player* player) :m_assetLoader{ assetLoader }, m_player { player } {}
    ~Level();



    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
	const std::vector<GameObject*> &getGameObjects() { return m_gameObjects; }
	GameObject* getFreeProjectile();

	void loadLevel(int level);
	int getCurrentLevel() const { return m_currentLevel; }
	

	void update(const float deltaTime);


    LevelBlock* getBlock(const int x, const int y)
    {
        return &m_levelBlocks[y * m_width + x];
    }

private:
    unsigned int m_ceilingColour = 0;
    unsigned int m_floorColour = 0;
	int m_currentLevel;
    int m_width;
    int m_height;
	Player* m_player;
	AssetLoader* m_assetLoader;

    LevelBlock* m_levelBlocks = nullptr;
	std::vector<GameObject*> m_gameObjects;


	const int m_MaxProjectiles = 20;
};
