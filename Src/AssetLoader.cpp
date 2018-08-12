#include "AssetLoader.h"
#include <SDL_image.h>
#include <SDL.h>
#include "AudioSystem.h"
#include "SoundClip.h"
#include <assert.h>  

Uint32 Texture::sampleColour(const float x, const float y) const
{
	const auto sx = static_cast<int>(x * width);
	const auto sy = static_cast<int>(y * height);

	if (sx < 0 || sx >= width || sy < 0 || sy >= height)
		return 0x00000000;

	return data[sy * height + sx];
}

void AssetLoader::loadTexture(const std::string& filename, const std::string& name)
{
	const auto result = new Texture;
	result->name = name;

	SDL_Surface* surface = IMG_Load(filename.c_str());
	result->width = surface->w;
	result->height = surface->h;

	SDL_LockSurface(surface);

	const int dataSize = surface->w * surface->h;

	result->data = new Uint32[dataSize];

	auto out = SDL_GetPixelFormatName(surface->format->format);

	if (surface->format->format == SDL_PIXELFORMAT_ARGB8888)
		memcpy_s(result->data, dataSize * sizeof(Uint32), surface->pixels, dataSize * sizeof(Uint32));
	else
		SDL_ConvertPixels(surface->w, surface->h, surface->format->format, surface->pixels, surface->pitch, SDL_PIXELFORMAT_ABGR8888, result->data, surface->w * 4);

	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);

	m_textures.push_back(result);
}

int AssetLoader::getTextureId(const std::string& name)
{
	for(size_t i = 0; i < m_textures.size(); i++)
	{
		if (m_textures[i]->name == name)
			return i;
	}

	return -1;
}

Texture* AssetLoader::getTexture(const int id)
{
	assert(id >= 0, "Id of texture is to small!");
	assert(id  m_textures.size(), "Id of texture is over the bounds of the array!");

	return m_textures[id];
}

void AssetLoader::loadSoundClip(const std::string& filename, const std::string& name)
{
	m_sounds.push_back(new SoundClip(filename, name));
}

SoundClip* AssetLoader::getSoundClip(const std::string& name)
{
	for (auto &clip : m_sounds)
		if (clip->getName() == name)
			return clip;

	return nullptr;
}

