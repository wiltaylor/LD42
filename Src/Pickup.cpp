#include "PickUp.h"

void PickUp::OnPlayerTouch(Player* m_player)
{
	visible = false;
	cleanUp = true;

	m_player->pickupKey(Key);

}


