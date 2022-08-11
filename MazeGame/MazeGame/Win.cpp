#include <iostream>
#include <conio.h>
#include "StateMachine.h"

#include "Win.h"

using namespace std;

Win::Win(StateMachine* Owner)
	:p_Owner(Owner)
{

}

bool Win::Update(bool processInput)
{
	if (processInput)
	{
		int input = _getch();
		p_Owner->LoadScene(StateMachine::Scene::MainMenu);
	}
	return false;
}

void Win::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "------Well Done------" << endl << endl;
	cout << " You win! " << endl << endl << endl;
	cout << "Press any key to back to main menu" << endl << endl << endl;
}