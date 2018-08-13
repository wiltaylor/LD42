#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
	SDL_Init(SDL_INIT_AUDIO);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

AudioSystem::~AudioSystem()
{
	if(m_music != nullptr)
		Mix_FreeMusic(m_music);

	Mix_CloseAudio();
}



void AudioSystem::PlayMusic(const std::string& filename)
{
	m_music = Mix_LoadMUS(filename.c_str());
	Mix_PlayMusic(m_music, -1);
}

void AudioSystem::SetMusicVolumn(int ammount)
{
	Mix_VolumeMusic(ammount);
}

int AudioSystem::getMusicVolumn()
{
    //-1 causes it to return volumn instead of setting it.
	return 	Mix_VolumeMusic(-1);
}



