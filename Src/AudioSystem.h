#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
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