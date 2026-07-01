#include "InGameScene.h"

void InitInStage(GameState& state)
{
	SetConsoleSize(MAP_W * 3.5, MAP_H * 1.5);

	SoundManager::GetInst()->PlayBGM("Resources/Sounds/InGameBGM.wav");
	GenerateMap(state, StageManager::GetInst()->GetCurMapData().m_map);
	state.clone.Init();
	state.moveDataRecord.ReSet();

	state.descriptionUITitleColor = Color::LIGHT_YELLOW;
	state.descriptionUIMessageColor = Color::SKYBLUE;

	if (state.curStage == Stage::TUTORIAL_1)
	{
		SetConsoleSize(MAP_W * 6.5, MAP_H * 1.5);
		state.descriptionUITitle = "<튜토리얼 1>                                                     ";
		state.descriptionUIMessage1 = "W,A,S,D로 플레이어를 움직일 수 있다.                           ";
		state.descriptionUIMessage2 = "목적지(◈)에 도달해서 스테이지를 클리어할 수 있다.               ";
		state.descriptionUIMessage3 = "                                                             ";
		state.descriptionUIMessage4 = "                                                             ";
	}
	else if (state.curStage == Stage::TUTORIAL_2)
	{
		SetConsoleSize(MAP_W * 6.5, MAP_H * 1.5);
		state.descriptionUITitle = "<튜토리얼 2>                                                     ";
		state.descriptionUIMessage1 = "충돌해서 기믹들과 상호작용할 수 있다.                           ";
		state.descriptionUIMessage2 = "색깔 버튼(⊙)은 똑같은 색의 모든 오브젝트들에 신호를 줍니다.      ";
		state.descriptionUIMessage3 = "스위치 블럭(■,□)은 꺼진 상태에서만 지나갈 수 있다.               ";
		state.descriptionUIMessage4 = "                                                             ";
	}
	else if (state.curStage == Stage::TUTORIAL_3)
	{
		SetConsoleSize(MAP_W * 6.5, MAP_H * 1.5);
		state.descriptionUITitle = "<튜토리얼 3>                                                     ";
		state.descriptionUIMessage1 = "레이저 코어는 레이저를 발사한다.                                ";
		state.descriptionUIMessage2 = "레이저 코어는 돌아갈 수 있고 켜졌다가 꺼질 수 있다.              ";
		state.descriptionUIMessage3 = "                                                             ";
		state.descriptionUIMessage4 = "                                                             ";
	}
	else if (state.curStage == Stage::TUTORIAL_4)
	{
		SetConsoleSize(MAP_W * 6.5, MAP_H * 1.5);
		state.descriptionUITitle = "<튜토리얼 4>                                                   ";
		state.descriptionUIMessage1 = "레이저(↑)와 킬 블록(▣)은 플레이어가 충돌하면 죽게된다.         ";
		state.descriptionUIMessage2 = "플레이어가 죽으면 클론이 생성되어 플레이어를 따라한다.          ";
		state.descriptionUIMessage4 = "클론 블럭(■)은 꺼져있는 상태에서 클론만 지나갈 수 있다.         ";
	}
	else if (state.curStage == Stage::TUTORIAL_5)
	{
		SetConsoleSize(MAP_W * 6.5, MAP_H * 1.5);
		state.descriptionUITitle = "<튜토리얼 5>                                                    ";
		state.descriptionUIMessage1 = "포탈은 맵에 존재하는 같은 색깔의 다른 포탈로 이동시킨다.         ";
		state.descriptionUIMessage2 = "패널은(◎) 버튼 기능을 하지만, 지나갈 수 있다.                  ";
		state.descriptionUIMessage3 = "                                                             ";
		state.descriptionUIMessage4 = "                                                             ";
	}
	else if (state.curStage == Stage::TUTORIAL_6)
	{
		SetConsoleSize(MAP_W * 6.5, MAP_H * 1.5);
		state.descriptionUITitle = "<튜토리얼 6>                                                    ";
		state.descriptionUIMessage1 = "가끔은.. 플레이어가 아니라 클론이 종착점에 도달해야 할 때도 있다.";
		state.descriptionUIMessage2 = "                                                             ";
		state.descriptionUIMessage3 = "                                                             ";
		state.descriptionUIMessage4 = "                                                             ";
	}
}

void UpdateInGame(GameState& state)
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

	if (GetKeyDown(VK_ESCAPE))
	{
		SoundManager::GetInst()->Play("Exit");
		state.curScene = Scene::STAGE;
		state.prevStage = Stage::NONE;
	}

	if (GetKeyDown('R'))
	{
		SoundManager::GetInst()->Play("Restart");
		state.curScene = Scene::RESTART;
	}

	state.clone.Tick(state, state.delta);
}

void RenderInGame(GameState& state)
{
	GotoXY(0, 0);
	DrawMap(state);
	DrawUI(state);
}

void ClearStage(GameState& state)
{
	//Stage 클리어 처리
	SoundManager::GetInst()->Play("StageClear");

	Sleep(500);
	StageManager::GetInst()->Clear(state.curStage);
	state.curScene = Scene::STAGE;
	state.prevStage = Stage::NONE;
}

void GenerateMap(GameState& state, const string gameMap[MAP_H])
{
	for (int y = 0; y < MAP_H; ++y)
	{ 
		for (int x = 0; x < MAP_W; ++x)
		{
			int data = gameMap[y][x];
			GenerateBlockType generateBlockType = (GenerateBlockType)data;
			BlockType blockType = (BlockType)data;
			Block* block = GenerateBlock((GenerateBlockType)data);

			block->SetPosition({x,y});
			
			state.map[y][x] = block;

			if (blockType == BlockType::START)
			{
				Position cursorPos = { x * 2, y };
				Position mapPos = { x, y };
				state.player.SetSpawnPos(cursorPos, mapPos);
				state.player.SetPos(cursorPos, mapPos);
			}
		}
	}
}

void DrawMap(GameState& state)
{
	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			GotoXY(x * 2, y);

			if (TryDrawPlayer(state, x, y))
				continue;
			if (TryDrawClone(state, x, y))
				continue;

			PreDrawBlock(state, x, y);
			DrawBlock(state, x, y);
		}
		SetDefaultMode();
		cout << endl;
	}

	PostDrawBlock(state);
}

void PreDrawBlock(GameState& state, int x, int y)
{
	Block* blockPtr = state.map[y][x];
	if (blockPtr == nullptr) return;
	BlockType blockType = blockPtr->GetType();

	switch (blockType)
	{
	case BlockType::LASERCORE:
	{
		((LaserCore*)blockPtr)->TryDrawCast(state);
		break;
	}
	}
}

void PostDrawBlock(GameState& state)
{
	for (int y = 0; y < MAP_H; ++y)
	{
		for (int x = 0; x < MAP_W; ++x)
		{
			if (Position{ x,y } == state.player.GetMapPos())
			{
				switch (state.map[y][x] -> GetType())
				{
				case BlockType::LASERCORE:
				{
					HandlePlayerDead(state);
					break;
				}
				}
			}
		}
	}
}

void DrawBlock(GameState& state, int x, int y)
{
	Block* block = state.map[y][x];
	if (block == nullptr) return;

	SetColor(block->GetColor());
	cout << (block->GetImage());
}

void DrawUI(GameState& state)
{
	GotoXY(0, 15);
	if (state.actionUIMessage.empty())
		SetColor();
	else
	{
		SetColor(state.actionUIColor);
		SetDefaultMode();
		cout << state.actionUIMessage;
		SetColor();
		cout << "         ";
	}

	SetDefaultMode();
	SetColor(state.descriptionUITitleColor);
	GotoXY(32, 5);
	cout << state.descriptionUITitle;
	SetColor(state.descriptionUIMessageColor);
	GotoXY(32, 6);
	cout << state.descriptionUIMessage1;
	GotoXY(32, 7);
	cout << state.descriptionUIMessage2;
	GotoXY(32, 8);
	cout << state.descriptionUIMessage3;
	GotoXY(32, 9);
	cout << state.descriptionUIMessage4;
	GotoXY(32, 10);
	cout << state.descriptionUIMessage5;
	SetColor();
	

	//GotoXY(0, 16);
	//SetColor(Color::RED);
	//cout << "@";
	//SetColor(Color::WHITE);
	//cout << " : 빨간 포탈";
	//SetColor(Color::BLUE);
	//cout << " @";
	//SetColor(Color::WHITE);
	//cout << " : 파란 포탈";

	//GotoXY(0, 17);
	//SetColor(Color::RED);
	//cout << "⊙";
	//SetColor(Color::WHITE);
	//cout << " : 빨간 버튼";
	//SetColor(Color::BLUE);
	//cout << " ⊙";
	//SetColor(Color::WHITE);
	//cout << " : 파란 버튼";

	//GotoXY(0, 18);
	//SetColor(Color::RED);
	//cout << "※";
	//SetColor(Color::WHITE);
	//cout << " : 레이저 코어";
	//SetColor(Color::RED);
	//cout << " ↑";
	//SetColor(Color::WHITE);
	//cout << " : 레이저";

	//GotoXY(0, 19);
	//SetColor(Color::LIGHT_GREEN);
	//cout << "⊙";
	//SetColor(Color::WHITE);
	//cout << " : 클론 버튼";
	//SetColor(Color::LIGHT_GREEN);
	//cout << " ■";
	//SetColor(Color::WHITE);
	//cout << " : 클론 스위치 벽";

	//GotoXY(0, 20);
	//SetColor(Color::LIGHT_RED);
	//cout << "■";
	//SetColor(Color::WHITE);
	//cout << " : 빨간 스위치 벽";
	//SetColor(Color::BLUE);
	//cout << " ■";
	//SetColor(Color::WHITE);
	//cout << " : 파란 스위치 벽";

	GotoXY(32, 0);
	cout << "[ESC] Select Stage";
	GotoXY(32, 1);
	cout << "[R] Restart";



}

bool TryDrawPlayer(GameState& state, int x, int y)
{
	if (state.player.GetMapPos() == Position{ x, y } )
	{
		state.player.Render();
		return true;
	}

	return false;
}

bool TryDrawClone(GameState& state, int x, int y)
{
	if (state.clone.GetMapPos() == Position{ x, y }
		&& state.clone.IsActive())
	{
		state.clone.Render();
		return true;
	}

	return false;
}

bool TryPlayerMove(GameState& state, Dir dir)
{
	MoveData moveData;
	moveData.dir = dir;
	state.moveDataRecord.Record(moveData);

	Position dirToPos = DirToScreenPosition(dir);
	Position playerPos = state.player.GetMapPos();
	Position nextPos = playerPos + dirToPos;

	if (IsEdge(nextPos.x, nextPos.y))
		return false;

	Block* nextBlock = state.map[nextPos.y][nextPos.x];
	nextBlock->Interaction(state, state.player);
	return (nextBlock->IsPassable(state.player));
}

bool TryCloneMove(GameState& state, Dir dir)
{
	Position dirToPos = DirToScreenPosition(dir);
	Position clonePos = state.clone.GetMapPos();
	Position nextPos = clonePos + dirToPos;

	if (IsEdge(nextPos.x, nextPos.y))
		return false;

	Block* nextBlock = state.map[nextPos.y][nextPos.x];
	nextBlock->Interaction(state, state.clone);
	return (nextBlock->IsPassable(state.clone));
}

void HandlePlayerDead(GameState& state)
{
	Position startPos = state.player.GetStartPos();
	Position cursorPos = { startPos.x * 2, startPos.y };
	state.player.Dead();
	ShakeConsoleWindow(20, 30, 30);
	Sleep(500);

	state.clone.SetPos(cursorPos, startPos);
	state.player.SetPos(cursorPos, startPos);
	state.clone.Spawn(state.moveDataRecord.GetRecord());
	state.player.Spawn();
	state.moveDataRecord.ReSet();
}

void HandleCloneDead(GameState& state)
{
	state.clone.Dead();
	ShakeConsoleWindow(20, 30, 30);
	Sleep(500);
}