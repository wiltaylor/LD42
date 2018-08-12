#pragma once
#include "GameObject.h"
#include "Level.h"

class Portal : public GameObject
{
public:
	Portal(const Level* level) : m_level{const_cast<Level*>(level)} {}


	void onPlayerTouch(Player* player) override;
private:
	Level* m_level;
};
