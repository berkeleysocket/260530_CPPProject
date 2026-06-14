#pragma once
#include<queue>
#include"Color.h"
#include"Actor.h"

class Clone:public Actor
{
public:
	Clone() = default;

private:
	bool m_isActive = false;
	Color m_bodyClr = Color::YELLOW;
	std::queue<MoveData> m_moveRecord;

private:
	void Move(Dir dir) override;
public:
	void Spawn(std::queue<MoveData> record);
	void Dead();
	void Render() const override;
	void Tick(float deltaTime) override;
};

