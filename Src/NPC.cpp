#include "NPC.h"
#include <glm/detail/func_geometric.inl>

void NPC::OnUpdate(const float deltaTime)
{
	//Check distance
	const auto diff = m_position - m_player->getPosition();
	const auto distance = glm::length(diff);
	const auto direction = glm::normalize(diff);


	if(distance >= m_maxDistance)
	{
		m_velocity = { 0,0 };
		m_state = NPC_Idle;
		return;
	}

	m_velocity = -direction * m_maxSpeed;




}
