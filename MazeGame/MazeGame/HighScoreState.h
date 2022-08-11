#pragma once
#include "GameState.h"

#include <set>

using namespace std;

class StateMachine;

class HighScoreState : public GameState
{
	StateMachine* p_Owner;
	set<int> p_HighScore;


public:
	HighScoreState(StateMachine* Owner);
	~HighScoreState() = default;

	virtual bool Update(bool processInput = true) override;
	void processInput() override;
	virtual void Draw() override;
	
};