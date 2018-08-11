#include "Input.h"

void Input::update()
{
	m_keyStates = SDL_GetKeyboardState(nullptr);
	SDL_Event event;

	if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		m_hasQuit = true;
}

bool Input::keyDown(int code)
{
	return m_keyStates[code] != 0;
}
