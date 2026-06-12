#pragma once
#include"GameState.h"

void InitTitle();
void UpdateTitle(GameState& state);
void RenderTitle(const GameState& state);
void UpdateInfo(GameState& state);
void RenderInfo(const GameState& state);

void PlayTransition();
//void FlashAnim(COORD res, int count, int delayMs);
//void CrossAnim(COORD res, int delayMs);

