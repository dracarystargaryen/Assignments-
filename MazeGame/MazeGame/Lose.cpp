#include <iostream>
#include <conio.h>

#include "StateMachine.h"

#include "Lose.h"

using namespace std;

Lose::Lose(StateMachine* Owner)
	: p_Owner(Owner)
{

}

bool Lose::Update(bool processInput)
{
	if (processInput)
	{
		int userInput = _getch();
		p_Owner->LoadScene(StateMachine::Scene::MainMenu);
	}
	return false;
}

void Lose::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "-----Game Over-----" << endl << endl;
	cout << "Try Again!" << endl << endl << endl;
	cout << "Press any key to go back." << endl << endl << endl;
}