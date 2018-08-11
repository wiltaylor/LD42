#pragma once
#include <SDL.h>
#include <string>

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	int getScreenWidth() const { return m_screenWidth; }
	int getScreenHeight() const { return m_screenHeight; }
	void cleanPixelBuffer() const;
	void flip() const;
	void setWindowTitle(const std::string& title) const;
	void setPixel(int x, int y, Uint32 colour) const;

private:
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	Uint32* m_pixelBuffer;
	SDL_Texture *m_pixelbufferTexture;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
};
