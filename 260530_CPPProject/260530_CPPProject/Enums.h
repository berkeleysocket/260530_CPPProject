#pragma once
enum class Menu { START, QUIT };

enum class Scene
{
	NONE,
	TITLE,
	STAGE,
	INGAME,
	RESTART
};

enum class Stage
{
	NONE = -1,
	TUTORIAL_1,
	TUTORIAL_2,
	TUTORIAL_3,
	TUTORIAL_4,
	TUTORIAL_5,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	TUTORIAL_6,
	ENDSTAGE
};