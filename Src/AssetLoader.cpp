#include "AssetLoader.h"
#include <SDL_image.h>
#include <SDL.h>

Uint32 Texture::sampleColour(const float x, const float y) const
{
	const auto sx = static_cast<int>(x * width);
	const auto sy = static_cast<int>(y * height);

	if (sx < 0 || sx >= width || sy < 0 || sy >= height)
		return 0x00000000;

	return data[sy * height + sx];
}

void AssetLoader::loadTexture(const std::string& filename, const std::string name)
{
	const auto result = new Texture;
	result->name = name;

	SDL_Surface* surface = IMG_Load(filename.c_str());
	result->width = surface->w;
	result->height = surface->h;

	SDL_LockSurface(surface);

	result->data = new Uint32[surface->w * surface->h];
	SDL_ConvertPixels(surface->w, surface->h, surface->format->format, surface->pixels, surface->pitch, SDL_PIXELFORMAT_ARGB8888, result->data, surface->w * 4);

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
	return m_textures[id];
}