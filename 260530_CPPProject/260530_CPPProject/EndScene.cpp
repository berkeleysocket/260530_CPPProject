#include "EndScene.h"
#include"StageManager.h"
#include<Windows.h>
#include<algorithm>


void InitEnd(const GameState& state)
{
	BlinkAniEnd(3, 500);

    SetColor();
    SetUniCodeMode();

    FinalData finalData = StageManager::GetInst()->GetFinalData(state.curTime);

    COORD resolution = GetConsoleResolution();

    vector<wstring> lines =
    {
        L"==========================",
        L"        게임 결과",
        L"==========================",
        L"",
        L"총 플레이 시간 ·········· " + WFormatTime(finalData.totalPlayTime/1000),
        L"총 사망 횟수   ·········· " + std::to_wstring(finalData.totalDeadCount),
        L""
        L"가장 많이 죽은 스테이지  ····· " + std::to_wstring(finalData.maxDeadCount),
        L"해당 스테이지 사망 횟수  ····· " + std::to_wstring(finalData.maxDeadCount),
        L"",
        L"가장 빨리 클리어한 스테이지  ··· Stage " + std::to_wstring(finalData.minTimeStage),
        L"클리어 시간    ·········· " + WFormatTime(finalData.minPlayTime/1000),
        L"",
        L"플레이해주셔서 감사합니다."
    };

    int startY = (resolution.Y - lines.size()) / 2;

    for (int i = 0; i < lines.size(); i++)
    {
        int startX = (resolution.X - (int)lines[i].length()) / 2;

        GotoXY(startX, startY + i);
        RenderDialogue(lines[i] + L"\n", 30);
    }

}

void UpdateEnd(GameState& state)
{
    if (GetKeyDown(VK_RETURN) || GetKeyDown(VK_SPACE))
    {
		state.curScene = Scene::TITLE;
    }
}





void BlinkAniEnd(int count, float delayms)
{
	for (int i = 0; i < count; ++i)
	{
		std::system("cls");
		Sleep(delayms);

		SetColor(Color::WHITE, Color::WHITE);
		std::system("cls");
		Sleep(delayms);
	}
}
