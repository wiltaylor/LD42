#pragma once
#include <SDL.h>
#ifdef __EMSCRIPTEN__
	#include <SDL/SDL_mixer.h>
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