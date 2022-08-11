#pragma once
#include "GameState.h"

class StateMachine;

class Setting : public GameState
{
	StateMachine* p_Owner;

public:
	Setting(StateMachine* p_Owner);
	~Setting() = default;

	virtual bool Update(bool process = true) override;
	void processInput() override;
	virtual void Draw() override;
};