#pragma once
#include "GameState.h"

class StateMachine;

class Win : public GameState
{
	StateMachine* p_Owner;

public:
	Win(StateMachine* p_Owner);
	~Win() = default;

	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
};