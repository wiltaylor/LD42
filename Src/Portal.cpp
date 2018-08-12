#include "Portal.h"

void Portal::onPlayerTouch(Player* player)
{
	m_assetLoader->getSoundClip("portal")->play();

	if (!m_endPortal)
		m_level->loadLevel(m_level->getCurrentLevel() + 1);
	else
		m_hudRenderer->showEnd();
}
