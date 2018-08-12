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
	void update(float deltaTime);
	void attack();
	void hideLogo() {m_showingLogo = false;}
	bool showingLogo() const { return m_showingLogo || m_showEnding; }
	void showEnd() { m_showEnding = true; }

private:
	Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Texture* m_wizard1;
	SDL_Texture* m_wizard2;
	SDL_Texture* m_wizard3;
	SDL_Texture* m_wizard4;
	SDL_Texture* m_hpTexture;
	SDL_Texture* m_currentWizard;
	SDL_Texture* m_staffidle;
	SDL_Texture* m_staffattack;
	SDL_Texture* m_activestaff;
	SDL_Texture* m_gameOver;
	SDL_Texture* m_gameOverSubText;
	SDL_Texture* m_deathColour;
	SDL_Texture* m_logo;
	SDL_Texture* m_endScreen;
	SDL_Texture* m_redkey;
	SDL_Texture* m_bluekey;
	SDL_Texture* m_greenkey;
	SDL_Texture* m_goldkey;

	Player* m_player;

	int m_lastHP = 0;
	float m_attackCooldown = 0.0f;
	bool m_showingLogo = true;
	bool m_showEnding = false;

	SDL_Texture* loadTexture(const std::string& filename);

	void generateHPTexture(int hp);

	const int m_wizLevel4 = 0;
	const int m_wizLevel3 = 30;
	const int m_wizLevel2 = 70;
	const float m_coolDownTimeout = 1.0f;
	
};
