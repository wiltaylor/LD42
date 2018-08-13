#include "SoundClip.h"
#include <iostream>

SoundClip::SoundClip(const std::string& filename, const std::string& name)
{
	SDL_RWops *rw = SDL_RWFromFile(filename.c_str(), "rb");

	if (rw == nullptr)
		std::cout << "Failed to load " << filename << std::endl;

	m_wave = Mix_LoadWAV_RW(rw, 1);
		 
	m_name = name;
}

void SoundClip::play() const
{

	Mix_PlayChannel(-1, m_wave, 0);
}
