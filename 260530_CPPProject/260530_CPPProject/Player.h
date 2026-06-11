#pragma once
#include "Color.h"
#include"Actor.h"
#include "Clone.h"

class Player:public Actor
{
public:
	Player() = default;
private:
	bool isActive = true;
	Color bodyClr = Color::WHITE;
	Clone clone;
public:
	void TestGenerateClone()
	{
		clone.isActive = true;
	}
	void Render() const	 override;
	void Move(Dir dir)  override;
	void Tick(ULONGLONG curTick) override;
};