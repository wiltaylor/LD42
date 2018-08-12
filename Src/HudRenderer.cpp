#include "HudRenderer.h"

HUDRenderer::HUDRenderer(Renderer* render, Player* player) : m_renderer{render}, m_player{player}
{
	m_texture = loadTexture("hud.png");
	m_wizard1 = loadTexture("wiz1.png");
	m_wizard2 = loadTexture("wiz2.png");
	m_wizard3 = loadTexture("wiz3.png");
	m_wizard4 = loadTexture("wiz4.png");

	update();
}

void HUDRenderer::draw() const
{
	m_renderer->drawTexture(m_texture);
	m_renderer->drawTexture(m_currentWizard, m_renderer->getScreenWidth() / 2 - 32, m_renderer->getScreenHeight() - 75, 64, 64);
	m_renderer->drawTexture(m_hpTexture, m_renderer->getScreenWidth() / 2 - 16 , m_renderer->getScreenHeight() - 110, 32, 32);
}

SDL_Texture* HUDRenderer::loadTexture(const std::string& filename)
{

	SDL_Surface* surface = IMG_Load(filename.c_str());
	SDL_Texture* texture = m_renderer->getTextFromSurface(surface);
	SDL_FreeSurface(surface);

	return texture;
}

void HUDRenderer::generateHPTexture(int hp)
{
	m_hpTexture = m_renderer->getTextFromText(std::to_string(hp), { 255,0,0 });
}

void HUDRenderer::update() 
{
	int currentHP = static_cast<int>(m_player->getHp());

	if(currentHP != m_lastHP)
		generateHPTexture(currentHP);

	m_lastHP = currentHP;

	if (currentHP > m_wizLevel2)
		m_currentWizard = m_wizard1;
	else if (currentHP > m_wizLevel3)
		m_currentWizard = m_wizard2;
	else if (currentHP > m_wizLevel4)
		m_currentWizard = m_wizard3;
	else
		m_currentWizard = m_wizard4;
	
}

