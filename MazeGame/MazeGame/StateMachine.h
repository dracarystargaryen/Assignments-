#pragma once
#include "GameStateMachine.h"

class Game;
class GameState;

class StateMachine : public GameStateMachine
{
public:
	enum class Scene
	{
		None,
		MainMenu,
		Gameplay,
		Settings,
		HighScore,
		Lose,
		Win,
	};

private:
	Game* p_Owner;

	GameState* p_currentState;
	GameState* p_NextState;

public:
	StateMachine(Game* p_Owner);

	virtual bool Init() override;
	virtual bool UpdateState(bool processInput = true) override;
	virtual void DrawState() override;
	virtual void Change(GameState* newState) override;
	void LoadScene(Scene scene);
	virtual bool Cleanup() override;
};

