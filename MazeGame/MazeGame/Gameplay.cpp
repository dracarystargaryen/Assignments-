#include <iostream>
#include <conio.h>
#include <windows.h>
#include <assert.h>
#include <thread>

#include "Gameplay.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Level.h"
#include "Money.h"
#include "Goal.h"
#include "AudioManager.h"
#include "Utility.h"
#include "StateMachine.h"


using namespace std;

constexpr int pArrowInput = 224;
constexpr int pLeftArrow = 75;
constexpr int pRightArrow = 77;
constexpr int pUpArrow = 72;
constexpr int pDownArrow = 80;
constexpr int pEscapeKey = 27;

constexpr unsigned int SleepTime = 101;

Gameplay::Gameplay(StateMachine* Owner)
	: p_Owner(Owner)
	, p_LevelBeat(false)
	, p_skipFrame(0)
	, p_currentLevel(0)
	, p_Level(nullptr)
{
	p_LevelName.push_back("Level1.txt");
	p_LevelName.push_back("Level2.txt");
	p_LevelName.push_back("Level3.txt");

	p_inputThread = new std::thread(&Gameplay::processInput, this);

}

Gameplay::~Gameplay()
{
	delete p_Level;
	p_Level = nullptr;
}

bool Gameplay::Load()
{
	if (p_Level)
	{
		delete p_Level;
		p_Level = nullptr;
	}
	p_Level = new Level();
	return p_Level->Load(p_LevelName.at(p_currentLevel), p_Player.GetXPositionPointer(), p_Player.GetYPositionPointer());
}

void Gameplay::Enter()
{
	Load();
	p_shouldProcess = true;

}

void Gameplay::processInput()
{
	while (p_shouldProcess)
	{
		int input = _getch();
		int arrow = 0;
		int newPlayerX = p_Player.GetXPosition();
		int newPlayerY = p_Player.GetYPosition();

		if (input == pArrowInput)
		{
			arrow = _getch();
		}
		if ((input == pArrowInput && arrow == pLeftArrow) ||
			(char)input == 'A' || (char)input == 'a')
		{
			newPlayerX--;
		}
		else if ((input == pArrowInput && arrow == pRightArrow) ||
			(char)input == 'D' || (char)input == 'd')
		{
			newPlayerX++;
		}
		else if ((input == pArrowInput && arrow == pUpArrow) ||
			(char)input == 'W' || (char)input == 'w')
		{
			newPlayerY--;
		}
		else if ((input == pArrowInput && arrow == pDownArrow) ||
			(char)input == 'S' || (char)input == 's')
		{
			newPlayerY++;
		}
		else if (input == pEscapeKey)
		{
			p_Owner->LoadScene(StateMachine::Scene::MainMenu);
		}
		else if ((char)input == 'Z' || (char)input == 'z')
		{
			p_Player.DropKey();
		}
		if (newPlayerX != p_Player.GetXPosition() || newPlayerY != p_Player.GetYPosition())
		{
			HandleCollisions(newPlayerX, newPlayerY);
		}
		this_thread::sleep_for(chrono::milliseconds(SleepTime));
	}
}

void Gameplay::CheckBeat()
{
	if (p_LevelBeat)
	{
		++p_skipFrame;
		if (p_skipFrame > skipFrames)
		{
			p_LevelBeat = false;
			p_skipFrame = 0;
			++p_currentLevel;
			if (p_currentLevel == p_LevelName.size())
			{
				Utility::WriteHighScore(p_Player.GetMoney());
				AudioManager::GetInstance()->PlayWinSound();
				p_Owner->LoadScene(StateMachine::Scene::Win);
			}
			else {
				Load();
			}
		}
	}
}

bool Gameplay::Update(bool processInput)
{
	p_Level->ActorUpdate();
	HandleCollisions(p_Player.GetXPosition(), p_Player.GetYPosition());
	CheckBeat();
	return false;
}

void Gameplay::HandleCollisions(int newPlayerX, int newPlayerY)
{
	PlaceableActor* collideActor = p_Level->CheckForCollisions(newPlayerX, newPlayerY);
	if (collideActor != nullptr)
	{
		switch (collideActor->GetType()) {
		case ActorType::Enemy:
		{
			Enemy* collidedEnemy = dynamic_cast<Enemy*>(collideActor);
			assert(collideActor);
			AudioManager::GetInstance()->PlayLoseLivesSound();
			collidedEnemy->Remove();
			p_Player.SetPosition(newPlayerX, newPlayerY);

			p_Player.DecrementLives();
			if (p_Player.GetLives() < 0)
			{
				p_shouldProcess = false;
				_putch(1);
				AudioManager::GetInstance()->PlayLoseSound();
				p_Owner->LoadScene(StateMachine::Scene::Lose);
			  }
			break;
		    }
		//Set Money
		case ActorType::Money:
		{
			Money* collidedMoney = dynamic_cast<Money*>(collideActor);
			assert(collidedMoney);
			AudioManager::GetInstance()->PlayMoneySound();
			collidedMoney->Remove();
			p_Player.AddMoney(collidedMoney->GetValue());
			p_Player.SetPosition(newPlayerX, newPlayerY);
			break;
		    }
		//Set Key
		case ActorType::Key:
		{
			Key* collidedKey = dynamic_cast<Key*>(collideActor);
			assert(collidedKey);
			if (!p_Player.HasKey())
			{
				p_Player.PickupKey(collidedKey);
				collidedKey->Remove();
				p_Player.SetPosition(newPlayerX, newPlayerY);
				AudioManager::GetInstance()->PlayKeyPickupSound();
			}
			break;
		  }
		//Set Door
		case ActorType::Door:
		{
			Door* collideDoor = dynamic_cast<Door*>(collideActor);
			assert(collideDoor);
			if (!collideDoor->IsOpen())
			{
				if (p_Player.HasKey(collideDoor->GetColor()))
				{
					collideDoor->Open();
					collideDoor->Remove();
					p_Player.UseKey();
					p_Player.SetPosition(newPlayerX, newPlayerY);
					AudioManager::GetInstance()->PlayDoorOpenSound();
				}
				else
				{
					AudioManager::GetInstance()->PlayDoorClosedSound();
				}
			}
			else
			{
				p_Player.SetPosition(newPlayerX, newPlayerY);
			}
			break;
		  }
		//Set Goal
		case ActorType::Goal:
		{
			Goal* collideGoal = dynamic_cast<Goal*>(collideActor);
			assert(collideGoal);
			collideGoal->Remove();
			p_Player.SetPosition(newPlayerX, newPlayerY);
			p_LevelBeat = true;
			p_shouldProcess = false;
			_putch(1);
			break;

		   }
		default:
			break;
	    }
	
	}
	else if (p_Level->IsSpace(newPlayerX, newPlayerY))
	{
		p_Player.SetPosition(newPlayerX, newPlayerY);

	}
	else if (p_Level->IsWALL(newPlayerX, newPlayerY))
	{
		//Do nothing as this is wall collisions
	}
}

void Gameplay::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");

	p_Level->Draw();

	//Set Player Position
	COORD actorCursorPosition;
	actorCursorPosition.X = p_Player.GetXPosition();
	actorCursorPosition.Y = p_Player.GetYPosition();
	SetConsoleCursorPosition(console, actorCursorPosition);
	p_Player.Draw();

	//Cursor points to the end of the game
	COORD currentCursorPosition;
	currentCursorPosition.X = 0;
	currentCursorPosition.Y = p_Level->GetHeight();
	SetConsoleCursorPosition(console, currentCursorPosition);

	DrawHUD(console);
	this_thread::sleep_for(chrono::milliseconds(SleepTime));
}


void Gameplay::DrawHUD(const HANDLE& console)
{
	cout << endl;

	// Top Border
	for (int i = 0; i < p_Level->GetWidth(); ++i)
	{
		cout << Level::WALL;
	}
	cout << endl;

	// Left Side border
	cout << Level::WALL;

	cout << " wasd-move " << Level::WALL << " z-drop key " << Level::WALL;

	cout << " $:" << p_Player.GetMoney() << " " << Level::WALL;
	cout << " lives:" << p_Player.GetLives() << " " << Level::WALL;
	cout << " key:";
	if (p_Player.HasKey())
	{
		p_Player.GetKey()->Draw();
	}
	else
	{
		cout << " ";
	}

	// RightSide border
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);

	COORD pos;
	pos.X = p_Level->GetWidth() - 1;
	pos.Y = csbi.dwCursorPosition.Y;
	SetConsoleCursorPosition(console, pos);

	cout << Level::WALL;
	cout << endl;

	// Bottom Border
	for (int i = 0; i < p_Level->GetWidth(); ++i)
	{
		cout << Level::WALL;
	}
	cout << endl;
}