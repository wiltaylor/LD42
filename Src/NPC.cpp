#include "NPC.h"
#include <glm/detail/func_geometric.inl>

void NPC::onUpdate(const float deltaTime)
{

	if (m_isDead)
	{
		m_deathTimeOut -= deltaTime;
		texture = m_deathFrames[m_currentFrame];


		if (m_deathTimeOut <= 0)
			cleanUp = true;

		if (m_currentFrameTime <= 0.0f)
		{
			m_currentFrame++;
			if (m_currentFrame >= m_frames.size())
			{
				m_currentFrame = m_frames.size() - 1;
				m_currentFrameTime = m_deathTimeOut + 5;
			}

			m_currentFrameTime = m_frameTime;
		}
		else
		{
			m_currentFrameTime -= deltaTime;
		}

		return;
	}


	//Check distance
	const auto diff = m_position - m_player->getPosition();
	const auto distance = glm::length(diff);
	const auto direction = glm::normalize(diff);

	if(m_currentFrameTime <= 0.0f)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_frames.size())
			m_currentFrame = 0;

		texture = m_frames[m_currentFrame];

		m_currentFrameTime = m_frameTime;
	}else
	{
		m_currentFrameTime -= deltaTime;
	}


	if(distance >= m_maxDistance)
	{
		m_velocity = { 0,0 };
		m_state = NPC_Idle;
		return;
	}

	if (!m_physics->checkLineOfSite(m_position, m_player->getPosition()))
		return;

	if(!m_hasSeen)
	{
		m_hasSeen = true;
		m_assetLoader->getSoundClip(m_sightSound)->play();
		
	}
	m_velocity = -direction * m_maxSpeed;
}

void NPC::onHitWithProjectile(float dmg)
{
	m_hp -= dmg;

	if (m_hp < 0)
	{
		m_isDead = true;
		physicsObject = false;
	}
}

