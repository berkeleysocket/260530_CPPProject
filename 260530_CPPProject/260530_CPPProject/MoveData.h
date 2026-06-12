#pragma once
#include "Dir.h"
#include "Position.h"
struct MoveData
{
	//나중에 더 추가될지 몰라서 일단 따로 만들어놨음
	Dir dir;
	float nextMoveTime;
}; 