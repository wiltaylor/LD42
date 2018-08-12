#include "SoundClip.h"

SoundClip::SoundClip(const std::string& filename, const std::string& name)
{
	m_wave = Mix_LoadWAV(filename.c_str());
	m_name = name;
}

void SoundClip::play() const
{
	Mix_PlayChannel(-1, m_wave, 0);
}
