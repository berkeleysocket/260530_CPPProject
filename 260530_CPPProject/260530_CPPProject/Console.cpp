#include "Console.h"

void SetUniCodeMode()
{
	(void)_setmode(_fileno(stdout), _O_U16TEXT);
}

void SetDefaultMode()
{
	(void)_setmode(_fileno(stdout), _O_TEXT);
}

void RenderChar(char ch, int delayTime, bool isSkip)
{
	cout << ch;
	if (strchr("@#$%^&", ch))
	{
		if (!isSkip)
			Sleep(200);
		cout << "\b \b";
		if (!isSkip)
			Sleep(100);
	}

	if (isSkip)
		return;

	int calcDelay = delayTime + (rand() % 11 - 5);
	switch (ch)
	{
	case '!':
	case '?':
	case '.':
		calcDelay += 400; // 0.4초
		break;
	case ',':
		calcDelay += 200; // 0.2초
		break;
	case '\n':
		calcDelay += 500; // 0.5초
		break;
	case ' ':
		calcDelay += 50; // 0.05초
		break;
	}

	Sleep(std::max(0, calcDelay));
}

void RenderDialogue(const string& text, int delayTime)
{
	bool isSkip = false;
	for (int i = 0; i < text.size(); ++i)
	{
		// 스킵기능 추가
		if (!isSkip && _kbhit())
		{
			(void)_getch();
			isSkip = true;
		}
		RenderChar(text[i], delayTime, isSkip);
	}
}

void SetConsoleGameTitle(const wstring& title)
{
	SetConsoleTitle(title.c_str());
	// string.c_str => string의 내부 버퍼에 대한 포인터를 반환
}

void SetConsoleSize(int width, int height)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// = () {uniform Initializer}
	SMALL_RECT rect = { 0,0,1,1 };
	SetConsoleWindowInfo(handle, true, &rect);

	// 버퍼 크기를 설정
	COORD size = {(short)width, (short)height};
	SetConsoleScreenBufferSize(handle, size);
	// 뷰포트 크기 설정
	rect.Right = width - 1;
	rect.Bottom = height - 1;
	// 120칸은 0~ 119이기 때문에 1빼줌
	// 뷰포트 크기 줄이기
	SetConsoleWindowInfo(handle, true, &rect);

	// 텀이 있어야 함.
	//Sleep(100);

	HWND hWnd = GetConsoleWindow();

	/*RECT windowRt;
	GetWindowRect(hWnd, &windowRt);
	int windowWidth = windowRt.right - windowRt.left;
	int windowHeight = windowRt.bottom - windowRt.top;*/
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontInfo);
	
	int windowWidth = fontInfo.dwFontSize.X * width;
	int windowHeight = fontInfo.dwFontSize.Y * height;

	int screenWidth  = GetSystemMetrics(SM_CXSCREEN); // 가로
	int screenHeight = GetSystemMetrics(SM_CYSCREEN); // 세로
	int posX = (screenWidth - windowWidth) / 2;
	int posY = (screenHeight - windowHeight) / 2;

	SetWindowPos(hWnd, nullptr, posX, posY, 0, 0, SWP_NOSIZE);
	// cx, cy == 0,0 크기는 보존해주세요
}

void SetConsoleFullScreen()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontInfo);

	SetConsoleDisplayMode(handle, CONSOLE_FULLSCREEN_MODE, 0);

	int width = GetSystemMetrics(SM_CXSCREEN) / fontInfo.dwFontSize.X;
	int height = GetSystemMetrics(SM_CYSCREEN) / fontInfo.dwFontSize.Y;
	SetConsoleSize(width, height);
}

void SetConsoleWindowStyle(bool showTitleBar)
{
	HWND hWnd = GetConsoleWindow();
	LONG style = GetWindowLong(hWnd, GWL_STYLE);
	// Style에서 빼는거 NAND연산으로 빼기;
	style &= ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX 
		& ~WS_SYSMENU;

	if (!showTitleBar)
		style &= ~WS_CAPTION;

	// GWLSTYLE = GetWindowLong();
	SetWindowLong(hWnd, GWL_STYLE, style);

	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0
		, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void ShakeConsoleWindow(int intensity, int duration, int interval)
{
	// intensity: 강도
	// duration : 총 지속시간
	// interval: 간격
	HWND hWnd = GetConsoleWindow();
	RECT windowRt;
	GetWindowRect(hWnd, &windowRt);
	int originX = windowRt.left;
	int originY = windowRt.top;
	// 진동
	int count = duration / interval;
	for (int i = 0; i < count; ++i)
	{
		int offsetX = rand() % (intensity * 2 + 1) - intensity;
		int offsetY = rand() % (intensity * 2 + 1) - intensity;

		SetWindowPos(hWnd, nullptr, 
			originX + offsetX, originY + offsetY, 0, 0, SWP_NOSIZE);

		Sleep(interval);
	}

	// 제자리
	SetWindowPos(hWnd, nullptr, originX, originY, 0, 0, SWP_NOSIZE);
}

void SetConsoleMouseInputDisabled()
{
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(handle, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	mode |= ENABLE_MOUSE_INPUT; 
	mode |= ENABLE_EXTENDED_FLAGS; 

	SetConsoleMode(handle, mode);
}

POINT GetMouseCellPos()
{
	POINT pt;
	GetCursorPos(&pt);

	HWND hWnd = GetConsoleWindow();
	ScreenToClient(hWnd, &pt); // 스크린 좌표를 콘솔 좌표로 변환

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontInfo);

	POINT cellPos = { pt.x / fontInfo.dwFontSize.X,
					  pt.y / fontInfo.dwFontSize.Y };
	
	return cellPos;
}

COORD GetConsoleResolution()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);

	short width = info.srWindow.Right - info.srWindow.Left  + 1;
	short height = info.srWindow.Bottom - info.srWindow.Top + 1;
	//return COORD{ width, height };
	return { width, height };
}

void GotoXY(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD curPos = { (short)x,(short)y };

	SetConsoleCursorPosition(handle, curPos);
}
BOOL IsGotoXY(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD curPos = { (short)x,(short)y };

	return SetConsoleCursorPosition(handle, curPos);
}

void SetCursorVisible(bool visible, DWORD size)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = visible; // on, off
	curInfo.dwSize = size; // 1, 100
	SetConsoleCursorInfo(handle, &curInfo);
}

int GetCursorX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

void SetColor(Color textColor, Color bgColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int text = (int)textColor;
	int bg = (int)bgColor;

	SetConsoleTextAttribute(handle, (bg << 4) | text);
}

void DrawBar(int x, int y, const string& label, int value, int maxValue, int barWidth, const string& fillChar, const string& emptyChar)
{
	Color color;
	if (value > maxValue * 0.6f)
		color = Color::LIGHT_GREEN;
	else if (value > maxValue * 0.3f)
		color = Color::LIGHT_YELLOW;
	else
		color = Color::LIGHT_RED;
	GotoXY(x, y);
	SetColor();
	cout << label;
	SetColor(color);
	int fillCount = barWidth * value / maxValue;
	for (int i = 0; i < barWidth; i++)
	{
		cout << (i < fillCount ? fillChar : emptyChar);
	}
	SetColor();
	//cout << " " << value << "/" << maxValue << " ";
	int digits = std::to_string(maxValue).size();
	cout << " " << std::setw(digits)<< value << "/" << std::setw(digits)
		<< maxValue;
}

void DrawLine(char ch, int width)
{
	// setw 는 한번 하면 끝
	// setfill 은 한번 하면 영원히
	cout << std::setfill(ch) << std::setw(width) << "" 
		<< std::setfill(' ') << endl;
}

bool GetKey(int vKey)
{
	return GetAsyncKeyState(vKey) & 0x8000;
}

// 정적 전역 변수 
static bool prevDown[256] = {}; // 콕
static bool curDown[256] = {}; // 콕
bool GetKeyDown(int vKey)
{
	return curDown[vKey] && !prevDown[vKey];
	// 정적 지역 변수
	//static bool prevDown[256] = {};
	/*bool cur = GetAsyncKeyState(vKey) & 0x8000;
	bool down = cur && !prevDown[vKey];
	prevDown[vKey] = cur;
	return down;*/
}

void UpdateInput()
{
	for (int i = 0; i < 256; i++)
	{
		// 직전 프레임의 cur과 prev의 데이터 갱신
		prevDown[i] = curDown[i];
		// 지금 딱! 이 프레임에 눌렸어요?
		curDown[i] = GetAsyncKeyState(i) & 0x8000;
 	}
}

void FrameSync(int fps)
{
	static ULONGLONG prevTick = GetTickCount64();
	ULONGLONG targetTick = 1000 / fps;

	ULONGLONG curTick = GetTickCount64();
	ULONGLONG elapsed = curTick - prevTick;
	if (elapsed < targetTick)
		Sleep(targetTick - elapsed);

	prevTick = GetTickCount64();
}

void SetConsoleFont(const wstring& fontName, COORD size, UINT weight)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info = {};
	info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	info.dwFontSize = size; // 폭, 높이
	info.FontWeight = weight; // FW_ ~ 
	// 폰트 이름 복사
	wcscpy_s(info.FaceName, fontName.c_str());
	SetCurrentConsoleFontEx(handle, false, &info);
}