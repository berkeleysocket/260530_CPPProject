#include "GameState.h"

bool IsEdge(int x, int y)
{
    return x < 0 || y < 0 ||
        x >= MAP_W || y >= MAP_H;
}