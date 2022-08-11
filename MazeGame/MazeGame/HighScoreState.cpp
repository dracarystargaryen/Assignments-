#include "HighScoreState.h"
#include <iostream>
#include <conio.h>
#include "StateMachine.h"
#include "Utility.h"


using namespace std;

HighScoreState::HighScoreState(StateMachine* Owner)
	: p_Owner(Owner)

{
	p_HighScore = Utility::WriteHighScore(0);
}

bool HighScoreState::Update(bool processInput)
{
	if (processInput)
	{
		ProcessInput();
	}
	return false;
}

void HighScoreState::processInput()
{
	int input = _getch();
	p_Owner->LoadScene(StateMachine::Scene::MainMenu);
}

void HighScoreState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << " -------High Scores ---------" << endl << endl;

	for (auto x = p_HighScore.rbegin(); x != p_HighScore.rend(); ++x)
	{
		cout << "         " << *x << endl;
	}

	cout << endl << endl;
	cout << " Press any key to go back." << endl << endl << endl;

	for (auto x = p_HighScore.rbegin(); x != p_HighScore.rend(); ++x)
	{
		cout << "           " << *x << endl;
	}

	cout << endl << endl;
	cout << "Press any key to go back." << endl << endl << endl;
}