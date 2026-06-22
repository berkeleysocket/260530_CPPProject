#pragma once
enum class Menu { START, QUIT };

enum class Scene
{
	NONE,
	TITLE,
	STAGE,
	INGAME
};

enum class Stage
{
	NONE = -1,
	STAGE1,
	STAGE2,
	STAGE3,
	ENDSTAGE,
};