#pragma once
#include<queue>
#include"Color.h"
#include"Actor.h"
#include<string>

struct GameState;

class Clone:public Actor
{
public:
	Clone() = default;

private:
	bool m_isActive = false;
	Color m_bodyClr = Color::YELLOW;
	std::string m_bodyImg = "¡×";
	std::queue<MoveData> m_moveRecord;

public:
	void Move(Dir dir) override;
	const bool GetIsActive() const
	{
		return m_isActive;
	}
	void Spawn(std::queue<MoveData> record);
	void Dead();
	void Render() const override;
	void Tick(GameState& state, float deltaTime);
	bool IsActive();
};

