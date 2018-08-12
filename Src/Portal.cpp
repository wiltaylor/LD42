#include "Portal.h"

void Portal::onPlayerTouch(Player* player)
{
	m_level->loadLevel(m_level->getCurrentLevel() + 1);
}
