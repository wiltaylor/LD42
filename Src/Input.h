#pragma once
#ifndef __linux__
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
class Input
{
public:
	Input() = default;
	~Input() = default;

	void update();
	bool keyDown(int code);
	bool hasQuit() const { return  m_hasQuit; }

private:
	const Uint8* m_keyStates;
	bool m_hasQuit = false;
};
