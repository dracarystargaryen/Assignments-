#include "StateMachine.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "Setting.h"
#include "HighScoreState.h"
#include "Lose.h"
#include "Win.h"
#include "Game.h"


StateMachine::StateMachine(Game* Owner)
	:p_Owner(Owner)
	, p_currentState(nullptr)
	, p_NextState(nullptr)

{

}

bool StateMachine::Init()
{
	LoadScene(Scene::MainMenu);
	return true;
}

bool StateMachine::UpdateState(bool processInput)
{
	bool done = false;
	if (p_NextState != nullptr)
	{
		Change(p_NextState);
		p_NextState = nullptr;
	}

	if (p_currentState != nullptr)
	{
		done = p_currentState->Update(processInput);
	}
	return done;
}

void StateMachine::DrawState()
{
	if (p_currentState != nullptr)
	{
		p_currentState->Draw();
	}
}

void StateMachine::Change(GameState* newState)
{
	if (p_currentState != nullptr)
	{
		p_currentState->Exit();
	}
	delete p_currentState;
	p_currentState = newState;
	newState->Enter();
}

void StateMachine::LoadScene(Scene scene)
{
	switch (scene)
	{
	case Scene::None:
			break;
	case Scene::MainMenu:
		p_currentState = new MainMenu(this);
		break;
	case Scene::Gameplay:
		p_currentState = new Gameplay(this);
		break;
	case Scene::Setting:
		p_currentState = Setting(this);
		break;
	case Scene::HighScore:
		p_currentState = HighScoreState(this);
		break;
	case Scene::Win:
		p_currentState = new Win(this);
		break;
	case Scene::Lose:
		p_currentState = new Lose(this);
		break;

	}
}


bool StateMachine::Cleanup()
{
	if (p_currentState != nullptr)
	{
		p_currentState->Exit();
		delete p_currentState;
	}
	return true;
}