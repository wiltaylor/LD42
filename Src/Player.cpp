#include "Player.h"

bool Player::hasKey(LockLevel key)
{
	switch(key)
	{
	case DOORLOCK_RED:
		return m_redKey;
	case DOORLOCK_BLUE:
		return m_blueKey;
	case DOORLOCK_GOLD:
		return m_goldKey;
	case DOORLOCK_GREEN:
		return m_greenKey;
	default:
		return true;
	}
}

void Player::pickupKey(LockLevel key)
{
	switch (key)
	{
	case DOORLOCK_RED:
		m_redKey = true;
		break;
	case DOORLOCK_BLUE:
		m_blueKey = true;
		break;
	case DOORLOCK_GOLD:
		m_goldKey = true;
		break;
	case DOORLOCK_GREEN:
		m_greenKey = true;
		break;
	default: ;
	}
}


void Player::reset()
{
	m_redKey = false;
	m_blueKey = false;
	m_goldKey = false;
	m_greenKey = false;
	m_hp = 100.0f;
	m_angle = 0;
}
