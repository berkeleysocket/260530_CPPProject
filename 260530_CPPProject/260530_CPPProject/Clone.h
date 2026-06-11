#pragma once
#include<queue>
#include"Color.h"
#include"Actor.h"

class Clone:public Actor
{
public:
	Clone(const std::queue<MoveData>& record)
	{
		m_moveRecord = record;
	}

private:
	Color m_bodyClr = Color::YELLOW;
	bool m_isActive = false;
	std::queue<MoveData> m_moveRecord;

private:
	void Move(Dir dir) override;
public:
	void Render() const override;
	void Tick(float deltaTime) override;
};

