#include "Console.h"
#include "TitleScene.h"

void InitTitle()
{
	SetConsoleSize(100, 30);
}

void UpdateTitle(GameState& state)
{
	UpdateInput();
	if (GetKeyDown(VK_UP))
	{
		state.curMenu = (Menu)((((int)state.curMenu - 1) + ((int)Menu::QUIT + 1)) % ((int)Menu::QUIT + 1));
		SoundManager::GetInst()->Play("Selecte");
	}
	if (GetKeyDown(VK_DOWN))
	{
		state.curMenu = (Menu)(((int)state.curMenu +1) % ((int)Menu::QUIT + 1));
		SoundManager::GetInst()->Play("Selecte");
	}
	// 엔터					//스페이스
	if (GetKeyDown(VK_RETURN) || GetKeyDown(VK_SPACE))
	{
		SoundManager::GetInst()->Play("RealSelecte");
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
	int y = res.Y /1.16f;
	SetColor();

	SetDefaultMode();
	const string labels[] = { "게임 시작", "게임 종료" };
	for (int i = 0; i < 2; i++)
	{
		GotoXY(x - 2, y + i);
		cout << (i == (int)state.curMenu ? "> " : "  ") << labels[i];
	}

	const wstring title[] =
	{
		L"████████▄     ▄████████    ▄████████ ████████▄  ",
		L"███   ▀███   ███    ███   ███    ███ ███   ▀███ ",
		L"███    ███   ███    █▀    ███    ███ ███    ███ ",
		L"███    ███  ▄███▄▄▄       ███    ███ ███    ███ ",
		L"███    ███ ▀▀███▀▀▀     ▀███████████ ███    ███ ",
		L"███    ███   ███    █▄    ███    ███ ███    ███ ",
		L"███   ▄███   ███    ███   ███    ███ ███   ▄███ ",
		L"████████▀    ██████████   ███    █▀  ████████▀  ",

		L" ▄███████▄  ███    █▄   ▄███████▄   ▄███████▄     ▄████████  ▄█",
		L" ███    ███ ███    ███ ██▀     ▄██ ██▀     ▄██   ███    ███ ███",
		L" ███    ███ ███    ███       ▄███▀       ▄███▀   ███    █▀  ███",
		L" ███    ███ ███    ███  ▀█▀▄███▀▄▄  ▀█▀▄███▀▄▄  ▄███▄▄▄     ███",
		L"▀█████████▀ ███    ███   ▄███▀   ▀   ▄███▀   ▀ ▀▀███▀▀▀     ███",
		L" ███        ███    ███ ▄███▀       ▄███▀         ███    █▄  ███",
		L" ███        ███    ███ ███▄     ▄█ ███▄     ▄█   ███    ███ ███▌    ▄",
		L"▄████▀      ████████▀   ▀████████▀  ▀████████▀   ██████████ █████▄▄██",
	};
	
	
	int titleX = (res.X - 45)/ 2;
	int titleY = res.Y / 10;
	SetUniCodeMode();

	for (int i = 0; i < 8; ++i)
	{
		GotoXY(titleX, titleY + i);
		wcout << title[i];
	}


	for (int i = 8; i < 16; ++i)
	{
		GotoXY(titleX-5, titleY + 2+i);
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
	CrossAnim(res, delayMs);
}
void CrossAnim(COORD res, int delayMs)
{
	system("cls");
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
