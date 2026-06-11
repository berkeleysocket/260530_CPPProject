#pragma once
#include<queue>
#include"Color.h"
#include"Actor.h"

class Clone:public Actor
{
public:
	Clone() = default;

private:

	Color bodyClr = Color::YELLOW;

	std::queue<Dir> moveQ;

private:
	void Move(Dir dir) override;
public:
public:
	bool isActive = false;

	void Render() const override;
	void Tick(ULONGLONG curTick) override;
	void PushMoveData(Dir dir);
};

