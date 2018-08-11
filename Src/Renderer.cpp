#include "Renderer.h"

Renderer::Renderer(const int width, const int height) : m_screenWidth{width}, m_screenHeight{height}
{

	SDL_CreateWindowAndRenderer(width, height, 0, &m_window, &m_renderer);

	m_pixelbufferTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, width, height);
	m_pixelBuffer = new Uint32[width * height];
	cleanPixelBuffer();
	flip();
}

Renderer::~Renderer()
{
	SDL_DestroyWindow(m_window);
	SDL_Quit(); 
}


void Renderer::cleanPixelBuffer() const
{
	memset(m_pixelBuffer, 0xFF000000, m_screenWidth * m_screenHeight * sizeof(Uint32));
}

void Renderer::flip() const
{
	SDL_UpdateTexture(m_pixelbufferTexture, nullptr, m_pixelBuffer, m_screenWidth * sizeof(Uint32));
	SDL_RenderCopy(m_renderer, m_pixelbufferTexture, nullptr, nullptr);
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

