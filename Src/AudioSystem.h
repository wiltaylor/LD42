#pragma once
#ifndef __linux__
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
#ifdef __EMSCRIPTEN__
	#include <SDL/SDL_mixer.h>
#elif __linux__ 
	#include <SDL2/SDL_mixer.h>
#else
	#include <SDL_mixer.h>
#endif
#include <string>

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	void PlayMusic(const std::string& filename);
	void SetMusicVolumn(int ammount);
	int getMusicVolumn();

private:
	Mix_Music* m_music = nullptr;
};