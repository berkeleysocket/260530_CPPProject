#include "Console.h"
#include "StageScene.h"
#include "StageManager.h"

void InitStage()
{
	SetConsoleSize(80, 25);
	SetCursorVisible(false);

}

void UpdateStage(GameState& state)
{
	UpdateInput();
	if (GetKeyDown(VK_LEFT))
	{
		state.curStage = (Stage)std::max(0, (int)state.curMenu - 1);
		StageManager::GetInst()->ChangeStage(state.curStage);
	}
	if (GetKeyDown(VK_RIGHT))
	{
		state.curStage = (Stage)std::min((int)Stage::ENDSTAGE, (int)state.curMenu + 1);
		StageManager::GetInst()->ChangeStage(state.curStage);
	}
	// 엔터					//스페이스
	if (GetKeyDown(VK_RETURN) || GetKeyDown(VK_SPACE))
	{
		if (StageManager::GetInst()->GetCurStageSaveData().m_isLock)
			return;
		state.curScene = Scene::INGAME;
		StageManager::GetInst()->ChangeStage(state.curStage);
	}
}

void RenderStage(GameState& state)
{

	StageSaveData& stageData = StageManager::GetInst()->GetCurStageSaveData();
	if (state.curStage == state.prevStage)
			return;

	state.prevStage = state.curStage;
	MapData mapData = StageManager::GetInst()->GetCurMapData();


	COORD res = GetConsoleResolution();

	//스테이지 틀 그리기
	SetColor(); 
	SetUniCodeMode();
	const wstring stage[] = {
L"╔════════════════════════════════╗",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"║                                ║",
L"╚════════════════════════════════╝"
	};


	int frameX = res.X / 2 - 19;
	int frameY = res.Y / 4;
	for (int i = 0; i < 14; ++i)
	{
		GotoXY(frameX,frameY+i );
		wcout << stage[i];

	}

	if (stageData.m_isLock)
	{
		GotoXY(frameX + 14, frameY + 6);
		wcout<<L" ████";
		GotoXY(frameX + 14, frameY + 7);
		wcout<<L"█ ▓▓ █";
		GotoXY(frameX + 14, frameY + 8);
		wcout<<L"█ ▓▓ █";
		GotoXY(frameX + 14, frameY + 9);
		wcout << L" ████";

		GotoXY((frameX + 16)-1, frameY + 3);
		wcout << L"????";
		GotoXY(frameX + 14, frameY + 11);
		wcout << L"[LOCK]";
	}
	else
	{
		GotoXY((frameX + 16) - ((mapData.m_name.size())/2-1), frameY + 3);
		wcout << wstring(mapData.m_name.begin(), mapData.m_name.end());

		GotoXY(frameX + 12, frameY + 8);

		if (stageData.m_isCleared)
			wcout << L"Clear : O";
		else
			wcout << L"Clear : X";

		GotoXY(frameX + 10, frameY + 10);
		wcout << L"[SPACE] to play";
	}

	if ((int)state.curStage > 9)
	{
		GotoXY(frameX+13, frameY+2);
		wcout << L"Stage " << (int)state.curStage;
	}
	else
	{
		GotoXY(frameX + 14, frameY + 2);
		wcout << L"Stage " << (int)state.curStage;
	}



	
	//옆에 있는 버튼들
	wstring leftBtn = L"<";
	wstring rightBtn = L">";
	if (state.curStage != Stage::STAGE1)
	{
		GotoXY(0, res.Y / 2);
		wcout << leftBtn;
	}
	else
	{
		GotoXY(0, res.Y / 2);
		wcout << L" ";
	}

	if (state.curStage != Stage::ENDSTAGE)
	{
		GotoXY(res.X-1, res.Y / 2);
		wcout << rightBtn;
	}
	else
	{
		GotoXY(res.X-1, res.Y / 2);
		wcout << L" ";
	}

}

void SelecteStageAni(const StageSaveData& stageData, const MapData& mapData)
{
}
