#pragma once
#include "GameState.h"
#include "Player.h"

#include <windows.h>
#include <vector>
#include <string>

namespace std
{
	class thread;
}

class Level;
class StateMachine;

class Gameplay : public GameState
{
	StateMachine* p_Owner;

		Player p_Player;
		Level* p_Level;

		bool p_LevelBeat;
		int p_skipFrame;
		static constexpr int skipFrames = 2;

		int p_currentLevel;

		std::vector<std::string> p_LevelName;

public:
	Gameplay(StateMachine* p_Owner);
	~Gameplay();

	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

protected:
	void processInput() override;
	void CheckBeat();

	bool p_shouldProcess = false;
	std::thread* p_inputThread = nullptr;

private:
	void HandleCollisions(int newPlayerX, int newPlayerY);
	bool Load();
	void DrawHUD(const HANDLE& console);
};