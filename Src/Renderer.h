#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	int getScreenWidth() const { return m_screenWidth; }
	int getScreenHeight() const { return m_screenHeight; }
	void cleanPixelBuffer() const;
	void flipPixels() const;
	void flip() const;
	void setWindowTitle(const std::string& title) const;
	void setPixel(int x, int y, Uint32 colour) const;
	void drawTexture(SDL_Texture* texture) const;
	void drawTexture(SDL_Texture* texture, int x, int y, int width, int height) const;
	SDL_Texture* getTextFromSurface(SDL_Surface* surface) const;
	SDL_Texture* getTextFromText(const std::string& message, const SDL_Color& colour) const;
	

private:
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	Uint32* m_pixelBuffer;
	SDL_Texture *m_pixelbufferTexture;
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	TTF_Font* m_font;
};
