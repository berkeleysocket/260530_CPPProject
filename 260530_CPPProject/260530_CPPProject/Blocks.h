#pragma once
#include <iostream>
#include <string>
#include <queue>

#include "Actor.h"
#include "Position.h"
#include "Dir.h"
#include "Color.h"
#include "SoundManager.h"
#include "IButtonInteractable.h"

using std::string;
using std::queue;

struct GameState;

enum class GenerateBlockType
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


	PORTAL_RED = 'P',	//빨간색 포탈 - 빨간색 포탈이랑 연결됨. 맵에 딱 두 개만 존재가능.
	PORTAL_BLUE = 'p',	//파란색 포탈 - 파란색 포탈이랑 연결됨. 맵에 딱 두 개만 존재가능.

	BUTTON_RED = 'B',	//빨간색 버튼 - 레이저, 빨간색 벽이랑 상호작용함.
	BUTTON_BLUE = 'b',	//파란색 버튼 - 파란색 벽이랑 상호작용함.
	BUTTON_CLONE = 'N', //클론 버튼 - 클론 관련 기믹과 상호작용함.

	SWITCHABLEBRICK_RED_ON = 'W',	//빨간색 벽이 켜져있는 버전.
	SWITCHABLEBRICK_RED_OFF = 'w',	//빨간색 벽이 꺼져있는 버전.
	SWITCHABLEBRICK_BLUE_ON = 'Q',	//파란색 벽이 켜져있는 버전.
	SWITCHABLEBRICK_BLUE_OFF = 'q',	//파란색 벽이 꺼져있는 버전.
	SWITCHABLEBRICK_CLONE_ON = 'C',  //클론 벽이 꺼져있는 버전.
	SWITCHABLEBRICK_CLONE_OFF = 'c', //클론 벽이 꺼져있는 버전.

	BRICK_KILL = 'o', //상호작용하면 죽이는 블록

	//렌더링 용
	LASERBEAM_UP = 'K',
	LASERBEAM_DOWN = 'k',
	LASERBEAM_RIGHT = 'V',
	LASERBEAM_LEFT = 'v',
	SWITCHABLEBRICK_RED_OFF_BEAM = 'A',
	SWITCHABLEBRICK_BLUE_OFF_BEAM = 'a',
	SWITCHABLEBRICK_CLONE_OFF_BEAM = 'F',
};

enum class BlockType
{
	EMPTY = '.', //빈 공간.
	START = 'S', //스타트 지점.
	BRICK = '0', //일반 벽.
	END = 'E',	//종착점.

	LASERCORE = 'L',
	PORTAL = 'P',
	BUTTON = 'B',
	SWITCHABLEBRICK = 'W',
	BRICK_KILL = 'K', 
	LASERBEAM = 'V',
};

enum class BlockAffiliation
{
	NONE = 0,
	RED = 1,
	BLUE = 2,
	CLONE = 3,
	PLAYER = 4
};

class Block
{
public:
	Block(BlockAffiliation affiliation);
	virtual ~Block() = default;
protected:
	string m_image;
	Color m_color;
	BlockAffiliation m_affiliation;
	BlockType m_type;
	Position m_position;
public:
	void SetPosition(Position position) { m_position = position; }
	void SetType(BlockType type) { m_type = type; }
	const string GetImage() const { return m_image; }
	const Color GetColor() const { return m_color; };
	const BlockAffiliation GetAffiliation() const { return m_affiliation; };;
	const BlockType GetType() const { return m_type; }
	const Position GetPosition() const { return m_position; }
};

class EmptyBlock : public Block
{
public:
	EmptyBlock(BlockAffiliation affiliation);
};

#pragma region Brick
class Brick : public Block
{
public:
	Brick(BlockAffiliation affiliation);
};

class KillBrick : public Block
{
public:
	KillBrick(BlockAffiliation affiliation);
};
#pragma endregion

#pragma region Laser
class LaserCore : public Block, IButtonInteractable
{
public:
	LaserCore(BlockAffiliation affiliation, bool autoRotation, bool isActive, Dir castingDir);
private:
	bool m_isActive;
	bool m_autoRotation;
	Dir m_dir;
	queue<Position> m_beamPosQueue;
public:
	const Dir GetBeamDirection() const { return m_dir; }
public:
	void TryDrawCast(GameState& state);
	void ChangeDirection(GameState& state);
	void Toggle(GameState& state);
	void Clear(GameState& state);
	void Interaction(GameState& state) override;
};

class LaserBeam : public Block
{
public:
	LaserBeam(BlockAffiliation affiliation, Dir beamDirection);
#pragma endregion

};

#pragma region Button
class Button : public Block
{
public:
	Button(BlockAffiliation affiliation);
public:
	void Press(GameState& state);
};
#pragma endregion

#pragma region Portal
class Portal : public Block
{
public:
	Portal(BlockAffiliation affiliation);
public:
	void Warp(GameState& state, Actor& actor);
};
#pragma endregion

#pragma region SwitchableBrick
class SwitchableBrick : public Block, IButtonInteractable
{
public:
	SwitchableBrick(BlockAffiliation affiliation, bool isActive);
private:
	bool m_isActive;
public:
	bool GetIsActive() { return m_isActive; }
private:
	void Toggle(GameState& state);
public:
	void OnLaserBrickMode(GameState& state);
	void OffLaserBrickMode(GameState& state);
	void Interaction(GameState& state) override;
};
#pragma endregion

class EndBlock : public Block
{
public:
	EndBlock(BlockAffiliation affiliation);
};

Block* GenerateBlock(GenerateBlockType type);
bool IsPlayerPassable(Block* block);
bool IsClonePassable(Block* block);

