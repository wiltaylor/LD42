#include "RayCastRender.h"

void RayCastRenderer::Draw()
{
	//Clear depth buffer
	std::fill(m_depthBuffer, m_depthBuffer + m_depthBufferSize, m_maxDistance);

	for (int x = 0; x < m_renderer->getScreenWidth(); x++)
	{
		float rayAngle = (m_playerA - m_fov / 2.0f) + (static_cast<float>(x) / static_cast<float>(m_renderer->getScreenWidth())) * m_fov;
		float distanceToWall = 0;
		bool hitWall = false;

		float eyeX = sinf(rayAngle);
		float eyeY = cosf(rayAngle);
		float sampleX = 0.0f;
		bool testData = false;

		while (!hitWall && distanceToWall < m_maxDistance)
		{
			distanceToWall += m_stepSize;

			const auto testX = static_cast<int>(m_playerX + eyeX * distanceToWall);
			const auto testY = static_cast<int>(m_playerY + eyeY * distanceToWall);

			if (testX < 0 || testX >= m_mapWidth || testY < 0 || testY >= m_mapHeight)
			{
				hitWall = true;
				distanceToWall = m_maxDistance;
			}
			else
			{
				if (!m_level->getBlock(testX, testY)->passable)
				{
					hitWall = true;

					float blockMidX = static_cast<float>(testX) + 0.5f;
					float blockMidY = static_cast<float>(testY) + 0.5f;

					float testPointX = m_playerX + eyeX * distanceToWall;
					float testPointY = m_playerY + eyeY * distanceToWall;

					float testAngle = atan2f((testPointY - blockMidY), (testPointX - blockMidX));



					if (testAngle > -3.14159f * 0.25f && testAngle < 3.14159f * 0.25f)
						sampleX = testPointY - static_cast<float>(testY);				
					if(testAngle >= 3.14159f * 0.25f && testAngle < 3.14159f * 0.75f)
						sampleX = testPointX - static_cast<float>(testX);
					if (testAngle < -3.14159f * 0.25f && testAngle >= -3.14159f * 0.75f)
						sampleX = testPointX - static_cast<float>(testX);
					if (testAngle >= 3.14159f * 0.75f || testAngle < -3.14159f * 0.75f)
						sampleX = testPointY - static_cast<float>(testY);
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
					float sampleY = (static_cast<float>(y) - static_cast<float>(ceiling)) / (static_cast<float>(floor) - static_cast<float>(ceiling));
					m_renderer->setPixel(x, y, m_wallTexture->sampleColour(sampleX, sampleY));
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

void RayCastRenderer::addObject(GameObject* gameObject)
{
	m_gameObjects.push_back(gameObject);
}

void RayCastRenderer::drawObjects()
{
	for(auto &obj : m_gameObjects)
	{
		float vecX = obj->x - m_playerX;
		float vecY = obj->y - m_playerY;
		float distance = sqrtf(vecX * vecX + vecY * vecY);

		float eyeX = sinf(m_playerA);
		float eyeY = cos(m_playerA);

		float objectAngle = atan2f(eyeY, eyeX) - atan2f(vecY, vecX);

		bool inPlayerFov = fabs(objectAngle) < m_fov / 2.0f;

		if(inPlayerFov && distance >= 0.5f && distance < m_maxDistance)
		{
			float ceiling = static_cast<float>(m_renderer->getScreenHeight() / 2.0f) - m_renderer->getScreenHeight() / static_cast<float>(distance);
			float floor = m_renderer->getScreenHeight() - ceiling;
			float objHeight = floor - ceiling;
			float objAspectRatio = static_cast<float>(obj->texture->height) / static_cast<float>(obj->texture->width);
			float objWidth = objHeight / objAspectRatio;
			float objMiddle = (0.5f * (objectAngle / (m_fov / 2.0f)) + 0.5f) * static_cast<float>(m_renderer->getScreenWidth());

			for(int x = 0; x < objWidth; x++)
				for(int y = 0; y < objHeight; y++)
				{
					float sampleX = x / objWidth;
					float sampleY = y / objHeight;
					int objColumn = static_cast<int>(objMiddle + x - (objWidth / 2.0f));

					Uint32 colour = obj->texture->sampleColour(sampleX, sampleY);

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

RayCastRenderer::RayCastRenderer(Renderer* renderer): m_renderer{ renderer }
{
	AssetLoader assetloader;

	std::string filename = "wall.png";
	m_wallTexture = assetloader.loadTexture(filename);

	m_depthBufferSize = m_renderer->getScreenWidth();
	m_depthBuffer = new float[m_depthBufferSize];
} 

RayCastRenderer::~RayCastRenderer()
{
	delete m_wallTexture;
	delete[] m_depthBuffer;	
}
