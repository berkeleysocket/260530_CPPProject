#pragma once
#include "GameState.h"

class IButtonInteractable
{
public:
	virtual ~IButtonInteractable() = default;
public:
	virtual void Interaction(GameState& state) = 0;
};
