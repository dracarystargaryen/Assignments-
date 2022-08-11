#pragma once
#include "Player.h";
#include "Level.h";
#include "GameStateMachine.h"


class Game {
	Player m_player;
	Level m_level;
	bool m_isGameOver;
	GameStateMachine* m_pStateMachine;


public:
	Game();
	void Initialize(GameStateMachine* pStateMachine);


	bool Load();


	bool Load();
	void Run();

	void Deinitialize();

	bool IsGameOver();

private:
	bool Update();
	void Draw();


};
