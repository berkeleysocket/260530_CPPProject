#include "Player.h"
#include "Console.h"

void Player::Render()
{
	SetDefaultMode();
	SetColor();
	GotoXY(prevPos.x, prevPos.y);
	cout << " ";

	SetUniCodeMode();
	SetColor(bodyClr);
	GotoXY(pos.x, pos.y);
	wcout << L"⁜";
}

void Player::Move(Dir dir)
{
	switch (dir)
	{
	case Dir::UP:
		pos.y--;
		break;
	case Dir::DOWN: 
		pos.y++;
		break;
	case Dir::LEFT:
		pos.x--;
		break;
	case Dir::RIGHT:
		pos.x++;
		break;
	}
}
