#pragma once
#include <iostream>
#include <string>
#include <queue>

#include "Actor.h"
#include "Position.h"
#include "Dir.h"
#include "Color.h"
#include "SoundManager.h"

using std::string;
using std::queue;

struct GameState;

enum class BlockType
{
	EMPTY = '.', //빈 공간.
	START = 'S', //스타트 지점.
	BRICK = '0', //일반 벽.
	END = 'E',	//종착점.

	//static : 안 돌아가는 레이저.
	//auto : 돌아가는 레이저.
	//up, down, left, right : 시작 방향.
	//on/off : 시작 켜짐 여부
	LASERCORE_UP_AUTO = 'U',
	LASERCORE_UP_STATIC_ON = 'u',
	LASERCORE_UP_STATIC_OFF = 'H',
	LASERCORE_DOWN_AUTO = 'D',
	LASERCORE_DOWN_STATIC_ON = 'd',
	LASERCORE_DOWN_STATIC_OFF = 'Y',
	LASERCORE_LEFT_AUTO = 'L',
	LASERCORE_LEFT_STATIC_ON = 'l',
	LASERCORE_LEFT_STATIC_OFF = 'T',
	LASERCORE_RIGHT_AUTO = 'R',
	LASERCORE_RIGHT_STATIC_ON = 'r',
	LASERCORE_RIGHT_STATIC_OFF = 'O',

	//LaserBeam은 렌더링 용이므로 사용할 필요 없음.
	LASERBEAM_UP = 'K',
	LASERBEAM_DOWN = 'k',
	LASERBEAM_RIGHT = 'V',
	LASERBEAM_LEFT = 'v',

	PORTAL_RED = 'P',	//빨간색 포탈 - 빨간색 포탈이랑 연결됨. 맵에 딱 두 개만 존재가능.
	PORTAL_BLUE = 'p',	//파란색 포탈 - 파란색 포탈이랑 연결됨. 맵에 딱 두 개만 존재가능.

	BUTTON_RED = 'B',	//빨간색 버튼 - 레이저, 빨간색 벽이랑 상호작용함.
	BUTTON_BLUE = 'b',	//파란색 버튼 - 파란색 벽이랑 상호작용함.
	BUTTON_CLONE = 'N',

	SWITCHABLEBRICK_RED_ON = 'W',	//빨간색 벽이 켜져있는 버전.
	SWITCHABLEBRICK_RED_OFF = 'w',	//빨간색 벽이 꺼져있는 버전.
	SWITCHABLEBRICK_BLUE_ON = 'Q',	//파란색 벽이 켜져있는 버전.
	SWITCHABLEBRICK_BLUE_OFF = 'q',	//파란색 벽이 꺼져있는 버전.
	SWITCHABLEBRICK_CLONE_ON = 'C', //클론 벽이 꺼져있는 버전.
	SWITCHABLEBRICK_CLONE_OFF = 'c', //클론 벽이 꺼져있는 버전.

	BRICK_KILL = 'o',
};

class Block
{
protected:
	string m_image;
	Color m_color;
public:
	Position m_position;
	const string GetImage() const;
	const Color GetColor() const;
};

class EmptyBlock : public Block
{
public:
	EmptyBlock();
};

#pragma region Brick
class Brick : public Block
{
public:
	Brick();
};

class KillBrick : public Block
{
public:
	KillBrick();
};
#pragma endregion


class LaserCore : public Block
{
public:
	LaserCore(bool autoRotation, bool isActive, Dir castingDir);
private:
	bool m_isActive;
	bool m_autoRotation;
	Dir m_dir;
	queue<Position> m_beamPosQueue;
public:
	void TryDrawCast(GameState& state);
	void ChangeDirection(GameState& state);
	void Toggle(GameState& state);
	void Clear(GameState& state);
	const Dir GetBeamDirection() const;
};

class LaserBeamUp : public Block
{
public:
	LaserBeamUp();
};

class LaserBeamDown : public Block
{
public:
	LaserBeamDown();
};

class LaserBeamRight : public Block
{
public:
	LaserBeamRight();
};

class LaserBeamLeft : public Block
{
public:
	LaserBeamLeft();
};

#pragma region Button
class RedButton : public Block
{
public:
	RedButton();
public:
	void Press(GameState& state);
};

class BlueButton : public Block
{
public:
	BlueButton();
public:
	void Press(GameState& state);
};

class CloneButton : public Block
{
public:
	CloneButton();
public:
	void Press(GameState& state);
};
#pragma endregion

#pragma region Portal
class Portal : public Block
{
public:
	void Warp(GameState& state, Actor& actor, Position portalPosition, BlockType portalType);
};

class RedPortal : public Portal
{
public:
	RedPortal();
};

class BluePortal : public Portal
{
public:
	BluePortal();
};
#pragma endregion

#pragma region SwitchableBrick
class RedSwitchableBrick : public Block
{
public:
	RedSwitchableBrick(bool isActive);
private:
	bool m_isActive;
public:
	bool GetIsActive();
	void Toggle(GameState& state);
};

class BlueSwitchableBrick : public Block
{
public:
	BlueSwitchableBrick(bool isActive);
private:
	bool m_isActive;
public:
	bool GetIsActive();
	void Toggle(GameState& state);
};

class CloneSwitchableBrick : public Block
{
public: 
	CloneSwitchableBrick(bool isActive);
private:
	bool m_isActive;
public:
	bool GetIsActive();
	void Toggle(GameState& state);
};
#pragma endregion

class EndBlock : public Block
{
public:
	EndBlock();
};

Block* GenerateBlock(BlockType type);
bool IsPassable(Block* block, BlockType blockType);

