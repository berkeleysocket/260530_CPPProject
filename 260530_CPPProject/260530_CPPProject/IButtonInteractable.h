#pragma once
#include "GameState.h"

class IButtonInteractable
{
public:
	virtual ~IButtonInteractable() = default;
public:
	virtual void OnButtonPressed(GameState& state) = 0;
};
