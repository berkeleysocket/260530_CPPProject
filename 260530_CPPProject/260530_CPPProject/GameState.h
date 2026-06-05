#pragma once
#include<Windows.h>

constexpr int MAP_W = 21;
constexpr int MAP_H = 20;
constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

enum class Scene { NONE, TITLE, INGAME };
enum class Block {EMPTY, START, BRICK, LASER};

struct GameState
{
	Scene	prevScene = Scene::NONE;
	Scene	curScene = Scene::INGAME;
	bool	isRunning = true;
	Block	map[MAP_H][MAP_W] = {};
	ULONGLONG curTime;
};