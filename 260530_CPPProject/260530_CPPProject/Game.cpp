#include "Game.h"

void Init(GameState& state)
{
	SetConsoleSize(WIDTH, HEIGHT);
	SetConsoleWindowStyle(true);
	SetConsoleMouseInputDisabled();
	SetCursorVisible(false);

	SoundManager::GetInst()->Init();
	SoundManager::GetInst()->Load("Laser", "Resources/Sounds/Laser.mp3");
	SoundManager::GetInst()->Load("PlayerMovement", "Resources/Sounds/PlayerMovement.mp3");
	SoundManager::GetInst()->Load("ButtonClick", "Resources/Sounds/ButtonClick.mp3");
	SoundManager::GetInst()->Load("SwitchableBrick_OFF", "Resources/Sounds/SwitchableBrick_OFF.mp3");
	SoundManager::GetInst()->Load("SwitchableBrick_ON", "Resources/Sounds/SwitchableBrick_ON.mp3");
	SoundManager::GetInst()->Load("Teleport", "Resources/Sounds/Teleport.mp3");
	SoundManager::GetInst()->Load("CloneMovement", "Resources/Sounds/CloneMovement.mp3");
	SoundManager::GetInst()->Load("PlayerDeath", "Resources/Sounds/PlayerDeath.mp3");
	SoundManager::GetInst()->Load("CloneDeath", "Resources/Sounds/CloneDeath.mp3");
	SoundManager::GetInst()->Load("StageClear", "Resources/Sounds/StageClear.mp3");
	state = GameState{};
}

void Update(GameState& state)
{
	Dir dir;
	UpdateInput();
	if (GetKeyDown('W'))
	{
		dir = Dir::UP;
		if (TryPlayerMove(state, dir))
			state.player.Move(dir);
	}
	if (GetKeyDown('S'))
	{
		dir = Dir::DOWN;
		if (TryPlayerMove(state, dir))
			state.player.Move(dir);
	}
	if (GetKeyDown('A'))
	{
		dir = Dir::LEFT;
		if (TryPlayerMove(state, dir))
			state.player.Move(dir);
	}
	if (GetKeyDown('D'))
	{
		dir = Dir::RIGHT;
		if (TryPlayerMove(state, dir))
			state.player.Move(dir);
	}

	state.clone.Tick(state, state.delta);
}

void Render(GameState& state)
{
	GotoXY(0, 0);
    DrawMap(state);
	DrawUI(state);
}