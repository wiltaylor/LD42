#pragma once
class Player
{
public:
	Player() = default;
	~Player() = default;

	float getX() { return m_x; }
	float getY() { return m_y; }
	float getA() { return m_a; }

	void setX(float value) { m_x = value; }
	void setY(float value) { m_y = value; }
	void setA(float value) { m_a = value; }
private:
	float m_x = 0, m_y = 0, m_a = 0;
};