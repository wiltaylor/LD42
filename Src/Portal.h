#pragma once
#include "GameObject.h"
#include "Level.h"
#include "HudRenderer.h"

class Portal : public GameObject
{
public:
	Portal(const Level* level, HUDRenderer* hud, AssetLoader* assetLoader) : m_level{ const_cast<Level*>(level) }, m_hudRenderer{ hud }, m_assetLoader{ assetLoader }  {}


	void onPlayerTouch(Player* player) override;
	void setEndPortal() { m_endPortal = true; }
private:
	Level* m_level;
	HUDRenderer* m_hudRenderer;
	AssetLoader* m_assetLoader;
	bool m_endPortal = false;
};
