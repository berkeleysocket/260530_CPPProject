#include "EndScene.h"
#include"StageManager.h"
#include<Windows.h>
#include<algorithm>


void InitEnd(const GameState& state)
{
	BlinkAniEnd(3, 200);

    SetColor();

    FinalData finalData = StageManager::GetInst()->GetFinalData(state.curTime);

    COORD resolution = GetConsoleResolution();

    vector<string> lines =
    {
        "==========================",
        "        게임 결과         ",
        "==========================",
        "",
        "총 플레이 시간               => " + FormatTime(finalData.totalPlayTime/1000),
        "총 사망 횟수                 => " + std::to_string(finalData.totalDeadCount),
        "",
        "가장 많이 죽은 스테이지      => " + std::to_string(finalData.maxDeadCount),
        "해당 스테이지 사망 횟수      => " + std::to_string(finalData.maxDeadCount),
        "",
        "가장 빨리 클리어한 스테이지  => Stage " + std::to_string(finalData.minTimeStage),
        "클리어 시간                  => " + FormatTime(finalData.minPlayTime/1000),
        "",
        "==========================",
        "",
        "제작자 : 김희진, 강승영",
        "",
        "",
        "플레이해주셔서 감사합니다."
    };

    SetColor();
	system("cls");

    int startY = (resolution.Y - lines.size()) / 2;

    int contentX = resolution.X / 2 - 20;   // 원하는 만큼 왼쪽으로 이동

    for (int i = 0; i < lines.size(); i++)
    {
        int x;

        // 제목과 구분선은 가운데 정렬
        if (i <= 2 || i == 13)
        {
            x = (resolution.X - (int)lines[i].length()) / 2;
        }
        // 빈 줄도 가운데(아무 의미 없음)
        else if (lines[i].empty())
        {
            x = (resolution.X - (int)lines[i].length()) / 2;
        }
        // 내용은 왼쪽 정렬
        else
        {
            x = contentX;
        }

        GotoXY(x, startY + i);
        RenderDialogue(lines[i], 30);
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
		Sleep(delayms);
		SetColor(Color::WHITE, Color::WHITE);
		std::system("cls");

		Sleep(delayms);
        SetColor();
		std::system("cls");
	}
}
