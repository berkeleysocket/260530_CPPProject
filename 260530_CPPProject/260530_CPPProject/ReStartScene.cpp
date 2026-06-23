#include "ReStartScene.h"

void ReStartInit(GameState& state)
{
	system("cls");
	state.curScene = state.prevScene;
	state.prevScene = Scene::RESTART;
}
