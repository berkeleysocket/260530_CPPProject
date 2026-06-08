#include "Clone.h"

void Clone::PushMoveData(Dir dir)
{
	moveQ.push(dir);
}

void Clone::Move(Dir dir)
{
	prevPos = pos;

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
