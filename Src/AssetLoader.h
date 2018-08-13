#pragma once
#include <SDL.h>
#include <vector>
#include "SoundClip.h"

struct Texture
{
	std::string name;
	Uint32* data = nullptr;
	int width = 0;
	int height = 0 ;

	Uint32 sampleColour(const float x, const float y) const;
};

class AssetLoader
{
public:
	AssetLoader() = default;

	~AssetLoader()
	{
		for (auto t : m_textures)
		{
			delete[] t->data;
			delete t;
		}
	}

	void loadTexture(const std::string& filename, const std::string& name);
	void loadSoundClip(const std::string& filename, const std::string& name);
	int getTextureId(const std::string& name);
	SoundClip* getSoundClip(const std::string& name);
	Texture* getTexture(const int id);

private:
	std::vector<Texture*> m_textures;
	std::vector<SoundClip*> m_sounds;
};