#include "RayCastRender.h"
#include <glm/detail/func_geometric.inl>

void RayCastRenderer::Draw()
{
	//Clear depth buffer
	std::fill(m_depthBuffer, m_depthBuffer + m_depthBufferSize, m_maxDistance);

	for (int x = 0; x < m_renderer->getScreenWidth(); x++)
	{
		const auto rayAngle = (m_player->getAngle() - m_fov / 2.0f) + (static_cast<float>(x) / static_cast<float>(m_renderer->getScreenWidth())) * m_fov;
		float distanceToWall = 0;
		auto hitWall = false;

		const glm::vec2 eye = { sinf(rayAngle), cosf(rayAngle) };


		glm::vec2 sample({ 0.0f,0.0f });

		Texture* wallTex = nullptr;


		while (!hitWall && distanceToWall < m_maxDistance)
		{
			distanceToWall += m_stepSize;

			const glm::ivec2 test = m_player->getPosition() + eye * distanceToWall;

			if (test.x < 0 || test.x >= m_mapWidth || test.y < 0 || test.y >= m_mapHeight)
			{
				hitWall = true;
				distanceToWall = m_maxDistance;
			}
			else
			{
				const auto block = m_level->getBlock(test.x, test.y);


				if (!block->passable)
				{
					hitWall = true;

					wallTex = m_assetLoader->getTexture(block->textureIndex);

					const glm::vec2 blockMid{ test.x + 0.5f, test.y + 0.5f };

					auto testPoint = m_player->getPosition() + eye * distanceToWall;

					const auto testAngle = atan2f((testPoint.y - blockMid.y), (testPoint.x - blockMid.x));

					if (testAngle > -3.14159f * 0.25f && testAngle < 3.14159f * 0.25f)
						sample.x = testPoint.y - static_cast<float>(test.y);				
					if(testAngle >= 3.14159f * 0.25f && testAngle < 3.14159f * 0.75f)
						sample.x = testPoint.x - static_cast<float>(test.x);
					if (testAngle < -3.14159f * 0.25f && testAngle >= -3.14159f * 0.75f)
						sample.x = testPoint.x - static_cast<float>(test.x);
					if (testAngle >= 3.14159f * 0.75f || testAngle < -3.14159f * 0.75f)
						sample.x = testPoint.y- static_cast<float>(test.y);
				}
			}
		}


		int ceiling = static_cast<int>(static_cast<float>(m_renderer->getScreenHeight() / 2.0) - m_renderer->getScreenHeight() / static_cast<float>(distanceToWall));
		int floor = m_renderer->getScreenHeight() - ceiling;


		for (int y = 0; y < m_renderer->getScreenHeight(); y++)
		{
			if (y < ceiling)
			{
				m_renderer->setPixel(x, y, m_celingColour);
			}
			else if (y >= ceiling && y <= floor)
			{
				if(distanceToWall < m_maxDistance)
				{
					sample.y = (static_cast<float>(y) - static_cast<float>(ceiling)) / (static_cast<float>(floor) - static_cast<float>(ceiling));
					m_renderer->setPixel(x, y, wallTex->sampleColour(sample.x, sample.y));
					m_depthBuffer[x] = distanceToWall;
				
				}else
				{
					m_renderer->setPixel(x, y, 0xFFFF0000);
				}				
			}
			else
			{
				m_renderer->setPixel(x, y, m_floorColour);
			}
		}
	}
}

void RayCastRenderer::drawObjects()
{
	for(auto &obj : m_level->getGameObjects())
	{
		if(!obj->visible || obj->cleanUp)
			continue;

		const auto vec = obj->getPosition() - m_player->getPosition();
		const auto distance = glm::length(vec);
		const glm::vec2 eye = { sinf(m_player->getAngle()), cos(m_player->getAngle()) };
		const auto objectAngle = atan2f(eye.y, eye.x) - atan2f(vec.y, vec.x);

		const auto inPlayerFov = fabs(objectAngle) < m_fov / 2.0f;

		if(inPlayerFov && distance >= 0.5f && distance < m_maxDistance)
		{
			const auto tex = m_assetLoader->getTexture(obj->texture);

			const auto ceiling = static_cast<float>(m_renderer->getScreenHeight() / 2.0f) - m_renderer->getScreenHeight() / static_cast<float>(distance);
			const auto floor = m_renderer->getScreenHeight() - ceiling;
			const auto objHeight = floor - ceiling;
			const auto objAspectRatio = static_cast<float>(tex->height) / static_cast<float>(tex->width);
			const auto objWidth = objHeight / objAspectRatio;
			const auto objMiddle = (0.5f * (objectAngle / (m_fov / 2.0f)) + 0.5f) * static_cast<float>(m_renderer->getScreenWidth());

			for(auto x = 0; x < objWidth; x++)
				for(auto y = 0; y < objHeight; y++)
				{
					const glm::vec2 sample = { x / objWidth, y / objHeight };
					const auto objColumn = static_cast<int>(objMiddle + x - (objWidth / 2.0f));

					const auto colour = tex->sampleColour(sample.x, sample.y);

					if (objColumn >= 0 && objColumn < m_renderer->getScreenWidth() && ceiling + y >= 0 && ceiling + y < m_renderer->getScreenHeight())
					{
						if (colour == 0xFFFF00FF)
							continue;

						if(m_depthBuffer[objColumn] < distance)
							continue;

						m_depthBuffer[objColumn] = distance;
						m_renderer->setPixel(objColumn, static_cast<int>(ceiling + y), colour);
					}
				}
		}
	}

	m_gameObjects.clear();
}

RayCastRenderer::RayCastRenderer(Renderer* renderer, AssetLoader* loader, Player* player): m_renderer{ renderer }, m_player{player}, m_assetLoader {loader}
{
	m_wallTexture = m_assetLoader->getTextureId("wall");

	m_depthBufferSize = m_renderer->getScreenWidth();
	m_depthBuffer = new float[m_depthBufferSize];
} 

RayCastRenderer::~RayCastRenderer()
{
	delete[] m_depthBuffer;	
}
