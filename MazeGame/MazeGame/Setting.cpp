#include <iostream>
#include "Setting.h"
#include <conio.h>

#include "StateMachine.h"
#include "AudioManager.h"

using namespace std;

constexpr int pEscapeKey = 27;
constexpr int pSound = '1';
constexpr int pMainMenu = '2';

Setting::Setting(StateMachine* Owner)
	:p_Owner(Owner)
{

}


bool Setting::Update(bool processInput)
{
	if (processInput)
	{
		processInput();
	}
	return false;
}

void Setting::processInput()
{
	int userInput = _getch();
	if (userInput == pEscapeKey || (char)userInput == pMainMenu)
	{
		p_Owner->LoadScene(StateMachine::Scene::MainMenu);
	}
	else if ((char)userInput == pSound)
	{
		AudioManager::GetInstance()->ToggleSound();
		if (AudioManager::GetInstance()->IsSoundOn())
		{
			AudioManager::GetInstance()->PlayMoneySound();
		}
	}
}
