#pragma once
#include <sdl.h>
#ifdef __EMSCRIPTEN__
	#include <SDL/SDL_mixer.h>
#else
	#include <SDL_mixer.h>
#endif
#include <string>

class SoundClip
{
public:
	SoundClip(const std::string& filename, const std::string& name);

	void play() const;
	const std::string& getName() const { return m_name; }

private:
	Mix_Chunk * m_wave;
	std::string m_name;
};