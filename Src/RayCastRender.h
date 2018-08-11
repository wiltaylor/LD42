#include "Renderer.h"
#include "AssetLoader.h"
#include "GameObject.h"
#include <vector>
#include "Level.h"

class RayCastRenderer
{
public:
	RayCastRenderer(Renderer* renderer, AssetLoader* assetLoader);
	~RayCastRenderer();

	void setPlayerPosition(float x, float y, float angle)
	{
		m_playerX = x;
		m_playerY = y;
		m_playerA = angle;
	}

	void setMapData(Level* level, int width, int height)
	{
		m_level = level;
		m_mapWidth = width;
		m_mapHeight = height;
	}

	void Draw();

	void drawObjects();

	void setCelingColour(const Uint32 colour) { m_celingColour = colour; }
	void setFloorColour(const Uint32 colour) { m_floorColour = colour; }
	Uint32 getCelingColour() const { return m_celingColour; }
	Uint32 getFloorColour() const { return m_floorColour; }

private:
	Renderer* m_renderer;
	float m_playerX = 0;
	float m_playerY = 0;
	float m_playerA = 0;
	Level* m_level = nullptr;
	int m_mapWidth = 0;
	int m_mapHeight = 0;
	float* m_depthBuffer = nullptr;
	int m_depthBufferSize = 0;
	Uint32 m_celingColour = 0xFFCAC5CA;
	Uint32 m_floorColour = 0xFF666066;

	const float m_fov = 3.14159f / 4.0f;
	const float m_maxDistance = 16.0f;
	const float m_stepSize = 0.01f;

	int m_wallTexture = -1;
	std::vector<GameObject*> m_gameObjects;
	AssetLoader* m_assetLoader;

};
