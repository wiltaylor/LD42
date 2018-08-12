#pragma once
#include "Renderer.h"
#include <SDL_image.h>
#include <SDL.h>
#include "Player.h"

class HUDRenderer
{
public:
	HUDRenderer(Renderer* render, Player* player);
	void draw() const;
	void update();

private:
	Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Texture* m_wizard1;
	SDL_Texture* m_wizard2;
	SDL_Texture* m_wizard3;
	SDL_Texture* m_wizard4;
	SDL_Texture* m_hpTexture;
	SDL_Texture* m_currentWizard;

	Player* m_player;

	int m_lastHP = 0;


	SDL_Texture* loadTexture(const std::string& filename);

	void generateHPTexture(int hp);

	const int m_wizLevel4 = 0;
	const int m_wizLevel3 = 30;
	const int m_wizLevel2 = 70;
	
};
