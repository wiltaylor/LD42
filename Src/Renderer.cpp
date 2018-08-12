#include "Renderer.h"

Renderer::Renderer(const int width, const int height) : m_screenWidth{width}, m_screenHeight{height}
{

	SDL_CreateWindowAndRenderer(width, height, 0, &m_window, &m_renderer);
	TTF_Init();

	m_pixelbufferTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, width, height);
	m_pixelBuffer = new Uint32[width * height];

	m_font = TTF_OpenFont("c:\\windows\\fonts\\Arial.ttf", 12);

	if(!m_font)
	{
		printf(TTF_GetError());
	}
	
	cleanPixelBuffer();
	flip();
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
	SDL_RenderCopy(m_renderer, texture, nullptr, nullptr);
}

void Renderer::drawTexture(SDL_Texture* texture, int x, int y, int width, int height) const
{
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
