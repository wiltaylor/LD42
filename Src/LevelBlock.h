#pragma once

typedef enum 
{
	DOORLOCK_NONE,
	DOORLOCK_RED,
	DOORLOCK_GREEN,
	DOORLOCK_BLUE,
	DOORLOCK_GOLD
}LockLevel;


struct LevelBlock
{
	char icon;
	bool passable;
	int textureIndex;
	bool open = false;
	bool door = false;
	LockLevel lock = DOORLOCK_NONE;
};