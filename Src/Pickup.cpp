#include "PickUp.h"

void PickUp::onPlayerTouch(Player* m_player)
{
	visible = false;
	cleanUp = true;

	m_player->pickupKey(Key);

}


