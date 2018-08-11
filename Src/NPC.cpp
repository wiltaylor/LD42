#include "NPC.h"

void NPC::OnUpdate(const float deltaTime)
{

	//todo: proper vector maths here

	//Check distance
	float dX = x - m_player->getX();
	float dY = y - m_player->getY();

	if (dX < 0)
		dX *= -1;
	if (dY < 0)
		dY *= -1;

	float distance = sqrtf(dX * dX + dY * dY);

	//if (distance < 0)
	//	distance *= -1;


	if(distance >= m_maxDistance)
	{
		vx = 0;
		vy = 0;
		m_state = NPC_Idle;
		return;
	}

	////Move towards player
	if (m_player->getX() > x && dX > m_tollerance)
		vx = m_maxSpeed;
	if(m_player->getX() < x && dX > m_tollerance)
		vx = -m_maxSpeed;
	if (m_player->getY() > y && dY > m_tollerance)
		vy = m_maxSpeed;
	if (m_player->getY() < y && dY > m_tollerance)
		vy = -m_maxSpeed;



}
