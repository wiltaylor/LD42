#include "HudRenderer.h"

HUDRenderer::HUDRenderer(Renderer* render, Player* player) : m_renderer{render}, m_player{player}
{
	SDL_Texture* loading = m_renderer->getTextFromText("Loading...", { 255,255,255,0 });
	m_renderer->drawTexture(loading, m_renderer->getScreenWidth() / 2 - 64, m_renderer->getScreenHeight() / 2 - 32, 128, 64);
	m_renderer->flip();

	m_texture = loadTexture("hud.png");
	m_wizard1 = loadTexture("wiz1.png");
	m_wizard2 = loadTexture("wiz2.png");
	m_wizard3 = loadTexture("wiz3.png");
	m_wizard4 = loadTexture("wiz4.png");
	m_staffidle = loadTexture("staff_idle.png");
	m_staffattack = loadTexture("staff_attack.png");
	m_deathColour = loadTexture("deathcolour.png");
	m_logo = loadTexture("logo.png");
	

	m_gameOver = m_renderer->getTextFromText("Game Over!", { 255,255,255,0});
	m_gameOverSubText = m_renderer->getTextFromText("Press space to restart", { 255,255,255,0 });

	update(0);
}

void HUDRenderer::draw() const
{
	if (!m_showingLogo)
	{
		m_renderer->drawTexture(m_texture);
		m_renderer->drawTexture(m_currentWizard, m_renderer->getScreenWidth() / 2 - 32, m_renderer->getScreenHeight() - 75, 64, 64);
		m_renderer->drawTexture(m_hpTexture, m_renderer->getScreenWidth() / 2 - 16, m_renderer->getScreenHeight() - 110, 32, 32);
		m_renderer->drawTexture(m_activestaff, m_renderer->getScreenWidth() / 2 - 128, m_renderer->getScreenHeight() - 235, 256, 128);

		if (m_player->getHp() <= 0)
		{
			m_renderer->drawTexture(m_deathColour);
			m_renderer->drawTexture(m_gameOver, m_renderer->getScreenWidth() / 2 - 128, m_renderer->getScreenHeight() / 2 - 64, 256, 128);
			m_renderer->drawTexture(m_gameOverSubText, m_renderer->getScreenWidth() / 2 - 256, m_renderer->getScreenHeight() / 2 + 64, 512, 64);
		}
	}else
	{
		m_renderer->drawTexture(m_logo);	
	}
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
	m_hpTexture = m_renderer->getTextFromText(std::to_string(hp), { 255,0,0,0});
}

void HUDRenderer::update(float deltaTime) 
{
	int currentHP = static_cast<int>(m_player->getHp());

	if(currentHP != m_lastHP)
		generateHPTexture(currentHP);

	m_lastHP = currentHP;

	if(m_attackCooldown <= 0.0f)
	{
		m_activestaff = m_staffidle;

	}else
	{
		m_attackCooldown -= deltaTime;
	}

	if (currentHP > m_wizLevel2)
		m_currentWizard = m_wizard1;
	else if (currentHP > m_wizLevel3)
		m_currentWizard = m_wizard2;
	else if (currentHP > m_wizLevel4)
		m_currentWizard = m_wizard3;
	else
		m_currentWizard = m_wizard4;
	
}

void HUDRenderer::attack()
{
	m_activestaff = m_staffattack;
	m_attackCooldown = m_coolDownTimeout;
}
