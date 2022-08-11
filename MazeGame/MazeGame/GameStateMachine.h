#pragma once

class GameState;

class GameStateMachine
{

public:
	virtual ~GameStateMachine() = default;

	virtual bool Init() = 0;
	virtual bool UpdateState(bool process = true) = 0;
	virtual void DrawState() = 0;
	virtual void Change(GameState* newState) = 0;
	virtual bool Cleanup() = 0;
};