#pragma once
#include "Renderer.h"
#include "SDL.h"
struct Texture
{
	Uint32* data = nullptr;
	int width = 0;
	int height = 0 ;

	Uint32 sampleColour(const float x, const float y) const
	{
		const auto sx = static_cast<int>(x * width);
		const auto sy = static_cast<int>(y * height);

		if (sx < 0 || sx >= width || sy < 0 || sy >= height)
			return 0x00000000;

		return data[sy * height + sx];
	}
};

class AssetLoader
{
public:
	AssetLoader() = default;
	~AssetLoader() = default;

	Texture* loadTexture(std::string& filename);

};