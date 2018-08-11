#include "AssetLoader.h"
#include <SDL_image.h>
#include <SDL.h>

Texture* AssetLoader::loadTexture(std::string& filename)
{
	const auto result = new Texture;
	SDL_Surface* surface = IMG_Load(filename.c_str());
	result->width = surface->w;
	result->height = surface->h;

	SDL_LockSurface(surface);

	result->data = new Uint32[surface->w * surface->h];
	SDL_ConvertPixels(surface->w, surface->h, surface->format->format, surface->pixels, surface->pitch, SDL_PIXELFORMAT_ARGB8888, result->data, surface->w * 4);

	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
	
	return result;
}