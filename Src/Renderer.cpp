#include "Renderer.h"
#include <iostream>

Renderer::Renderer(const int width, const int height) : m_screenWidth{width}, m_screenHeight{height}
{

	std::cout << "Loading renderer" << std::endl;

	SDL_CreateWindowAndRenderer(width, height,/* SDL_WINDOW_FULLSCREEN*/0, &m_window, &m_renderer);
	
	std::cout << "Window created" << std::endl;
	
	TTF_Init();

	std::cout << "Font System loaded" << std::endl;

	m_pixelbufferTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, width, height);
	m_pixelBuffer = new Uint32[width * height];

	std::cout << "Pixel buffer created" << std::endl;

#ifdef __EMSCRIPTEN__
	m_font = TTF_OpenFont("arial.ttf", 12);

#else
	m_font = TTF_OpenFont(R"(c:\windows\fonts\Arial.ttf)", 12);
#endif



	std::cout << "Font Loaded" << std::endl;

	cleanPixelBuffer();
	flip();

	std::cout << "Presented blank pixel buffer" << std::endl;
}

Renderer::~Renderer()
{
	TTF_CloseFont(m_font);
	TTF_Quit();
	SDL_DestroyWindow(m_window);
	SDL_Quit(); 
}


void Renderer::cleanPixelBuffer() const
{
	memset(m_pixelBuffer, 0xFF000000, m_screenWidth * m_screenHeight * sizeof(Uint32));
}

void Renderer::flipPixels() const
{
	SDL_UpdateTexture(m_pixelbufferTexture, nullptr, m_pixelBuffer, m_screenWidth * sizeof(Uint32));
	SDL_RenderCopy(m_renderer, m_pixelbufferTexture, nullptr, nullptr);
}

void Renderer::flip() const
{
	SDL_RenderPresent(m_renderer);
}

void Renderer::setWindowTitle(const std::string& title) const
{
	SDL_SetWindowTitle(m_window, title.c_str());
}

void Renderer::setPixel(const int x, const int y, const Uint32 colour) const
{
	m_pixelBuffer[y * m_screenWidth + x] = colour;
}

void Renderer::drawTexture(SDL_Texture* texture) const
{
	if (texture == nullptr)
		return;

	SDL_RenderCopy(m_renderer, texture, nullptr, nullptr);
}

void Renderer::drawTexture(SDL_Texture* texture, int x, int y, int width, int height) const
{
	if (texture == nullptr)
		return;

	SDL_Rect dstRect = { x, y, width, height };
	SDL_RenderCopy(m_renderer, texture, nullptr, &dstRect);
}


SDL_Texture* Renderer::getTextFromSurface(SDL_Surface* surface) const
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	return texture;
}

SDL_Texture* Renderer::getTextFromText(const std::string& message, const SDL_Color& colour) const
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, message.c_str(), colour);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);

	return texture;	
}
