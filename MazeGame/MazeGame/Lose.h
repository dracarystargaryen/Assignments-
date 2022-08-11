#pragma once
#include "GameState.h"

class StateMachine;

class Lose : public GameState
{
	StateMachine* p_Owner;

public:
	Lose(StateMachine* Owner);
	~Lose() = default;

	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
};