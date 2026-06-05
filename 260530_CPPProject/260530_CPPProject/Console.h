#pragma once
#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <iomanip> // 조작자
#include <string> // 내부적으로 메서드를 쓰고 싶으면 include
#include"Color.h"
#pragma comment(lib, "winmm.lib")

using std::cout;
using std::wcout;
using std::endl;
using std::string;
using std::wstring;

// 아스키 아트
void SetUniCodeMode();
void SetDefaultMode();

// 다이얼 로그
void RenderDialogue(const string& text, int delayTime);
void RenderChar(char ch, int delayTime, bool isSkip);

// 창
void SetConsoleGameTitle(const wstring& title);
void SetConsoleSize(int width, int height); // 버퍼랑 뷰 포트를 일치시키기
void SetConsoleFullScreen();
void SetConsoleWindowStyle(bool showTitleBar);
void ShakeConsoleWindow(int intensity, int duration, int interval);
void SetConsoleMouseInputDisabled(); 
POINT GetMouseCellPos(); 
COORD GetConsoleResolution();

void GotoXY(int x, int y);
BOOL IsGotoXY(int x, int y);
// c+++에서는 헤더쪽에 넣어야 함.
void SetCursorVisible(bool visible, DWORD size = 1);
int GetCursorX();


// 색상
void SetColor(Color textColor = Color::WHITE, Color bgColor = Color::BLACK);
void DrawBar(int x, int y, const string& label,
    int value, int maxValue, int barWidth, const string& fillChar = "■", const string& emptyChar = "□");
void DrawLine(char ch, int width);

bool GetKey(int vKey);
bool GetKeyDown(int vKey); 
void UpdateInput();

// 시간
void FrameSync(int fps);
void SetConsoleFont(const wstring& fontName, COORD size, UINT weight = FW_NORMAL);