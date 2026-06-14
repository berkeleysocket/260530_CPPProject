#include "Console.h"
#include "TitleScene.h"

void InitTitle()
{
	SetConsoleSize(120, 50);
	SetCursorVisible(false);
	//SetConsoleWindowStyle(false);
}

void UpdateTitle(GameState& state)
{
	UpdateInput();
	if (GetKeyDown(VK_UP))
	{
		state.curMenu = (Menu)std::max(0, (int)state.curMenu - 1);
	}
	if (GetKeyDown(VK_DOWN))
	{
		state.curMenu = (Menu)std::min((int)Menu::QUIT, (int)state.curMenu + 1);
	}
	// 엔터					//스페이스
	if (GetKeyDown(VK_RETURN) || GetKeyDown(VK_SPACE))
	{
		switch (state.curMenu)
		{
		case Menu::START:
			PlayTransition();
			state.curScene = Scene::STAGE;
			break;
		case Menu::QUIT:
			state.isRunning = false;
			break;
		}
	}
}
void RenderTitle(const GameState& state)
{
	COORD res = GetConsoleResolution();
	int x = res.X / 2 -4;
	int y = res.Y / 3 *2;
	SetColor();

	const string labels[] = { "게임 시작", "게임 종료" };
	for (int i = 0; i < 2; i++)
	{
		GotoXY(x - 2, y + i);
		cout << (i == (int)state.curMenu ? "> " : "  ") << labels[i];
	}
	const wstring title[] =
	{
		L"████████▄     ▄████████    ▄████████ ████████▄     ▄███████▄ ███    █▄   ▄███████▄   ▄███████▄     ▄████████  ▄█",
		L"███   ▀███   ███    ███   ███    ███ ███   ▀███   ███    ███ ███    ███ ██▀     ▄██ ██▀     ▄██   ███    ███ ███",
		L"███    ███   ███    █▀    ███    ███ ███    ███   ███    ███ ███    ███       ▄███▀       ▄███▀   ███    █▀  ███",
		L"███    ███  ▄███▄▄▄       ███    ███ ███    ███   ███    ███ ███    ███  ▀█▀▄███▀▄▄  ▀█▀▄███▀▄▄  ▄███▄▄▄     ███",
		L"███    ███ ▀▀███▀▀▀     ▀███████████ ███    ███ ▀█████████▀  ███    ███   ▄███▀   ▀   ▄███▀   ▀ ▀▀███▀▀▀     ███",
		L"███    ███   ███    █▄    ███    ███ ███    ███   ███        ███    ███ ▄███▀       ▄███▀         ███    █▄  ███",
		L"███   ▄███   ███    ███   ███    ███ ███   ▄███   ███        ███    ███ ███▄     ▄█ ███▄     ▄█   ███    ███ ███▌    ▄",
		L"████████▀    ██████████   ███    █▀  ████████▀   ▄████▀      ████████▀   ▀████████▀  ▀████████▀   ██████████ █████▄▄██"
	};
	int titleX = (res.X - 118) / 2;
	int titleY = res.Y / 4;
	SetUniCodeMode();

	for (int i = 0; i < 8; ++i)
	{
		GotoXY(titleX, titleY + i);
		wcout << title[i];
	}
	SetDefaultMode();

}

void UpdateInfo(GameState& state)
{
	if (GetKeyDown(VK_ESCAPE))
		state.curScene = Scene::TITLE;
}

void RenderInfo(const GameState& state)
{
	COORD res = GetConsoleResolution();
	int x = res.X / 2;
	int y = res.Y / 3;
	const string infoLabel[] =
	{
		"[ 조작 방법 ]",
		"방향키 : 이동",
		"SPACE : 폭탄 설치",
		"Z     : 스킬",
		"ESC   : 돌아가기"
	};
	for (int i = 0; i < 5; ++i)
	{
		GotoXY(x, y + i);
		if (i == 0)
			SetColor(Color::LIGHT_YELLOW);
		else if (i == 4)
			SetColor(Color::LIGHT_GRAY);
		else
			SetColor();
		cout << infoLabel[i];

	}
}

void PlayTransition()
{
	COORD res = GetConsoleResolution();
	int delayMs = 30;
	int flashCount = 6;
	FlashAnim(res, flashCount, delayMs);
	CrossAnim(res, delayMs);
}

void FlashAnim(COORD res, int count, int delayMs)
{
	for (int i = 0; i < count; ++i)
	{
		SetColor(Color::BLACK, Color::WHITE);
		system("cls");

		SetColor();
		system("cls");
		Sleep(delayMs);
	}
}

void CrossAnim(COORD res, int delayMs)
{
	SetColor(Color::BLACK, Color::WHITE);
	for (int x = 0; x < res.X / 2; ++x)
	{
		for (int y = 0; y < res.Y; y += 2)
		{
			GotoXY(x * 2, y);
			cout << "  ";
		}
		for (int y = 1; y < res.Y; y += 2)
		{
			GotoXY(res.X - 2 - x * 2, y);
			cout << "  ";
		}
		Sleep(delayMs);
	}
	SetColor();
}
