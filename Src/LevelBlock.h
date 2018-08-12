#pragma once
struct LevelBlock
{
	bool passable;
	int textureIndex;
	bool open = false;
	bool door = false;
};