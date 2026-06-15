#include "Dir.h"

Position DirToMapPosition(Dir dir)
{
	switch (dir)
	{
	case Dir::UP:
		return { 0, -1 };
	case Dir::DOWN:
		return { 0, 1 };
	case Dir::LEFT:
		return { -1, 0 };
	case Dir::RIGHT:
		return { 1, 0 };
	}
}