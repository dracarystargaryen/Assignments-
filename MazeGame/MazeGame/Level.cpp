#include <windows.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"
#include "MazeGame.cpp"
using namespace std;

constexpr char WALL = (char)219;
constexpr char KEY = (char)232;
constexpr char DOOR = (char)179;
constexpr char GOAL = (char)36;

Level::Level()

	:m_pLevelData(nullptr)
	,m_height(0)
	,m_width(0)

{

}

Level::~Level() {
	if (m_pLevelData != nullptr) {
		delete[]  m_pLevelData;
		m_pLevelData = nullptr;
	}
	while (!m_pActors.empty())
	{
		delete m_pActors.back();
		m_pActors.pop_back();
	}
}


bool Level::Load(std::string levelName, int* playerX, int* playerY) {
	levelName.insert(0, "../");
	ifstream levelFile;
	levelFile.open(levelName);
	if (!levelFile) {
		cout << "Opening file failed!" << endl;
		return false;
	}
	else {
		constexpr int tempSize = 25;
		char temp[tempSize];

		levelFile.getline(temp, tempSize, '\n');
m_width = atoi(temp);

levelFile.getline(temp, tempSize, '\n');
m_height = atoi(temp);

m_pLevelData = new char[m_width * m_height];
levelFile.read(m_pLevelData, (long long)m_width* (long long)m_height);

bool anyWarnings = Convert(playerX, playerY);
if (anyWarnings) {
	cout << "There were some warnings in the level data, see above. " << endl;
	system("pause");
}
return true;
	}
}
void Level::Draw(int x, int y) {
	int index = GetIndexFromCoordinates(x, y);
	cout << m_pLevelData[index];
}

bool Level::IsSpace(int x, int y) {
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == ' ';
}
bool Level::IsDoor(int x, int y) {
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == DOOR;

}
bool Level::IsWALL(int x, int y)
{
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == WALL;
}

bool Level::IsKey(int x, int y) {
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == KEY;

}
bool Level::IsGoal(int x, int y) {
	return m_pLevelData[GetIndexFromCoordinates(x, y)] == GOAL;
}

void Level::PickUpKey(int x, int y) {
	m_pLevelData[GetIndexFromCoordinates(x, y)] = ' ';
}
void Level::OpenDoor(int x, int y) {
	m_pLevelData[GetIndexFromCoordinates(x, y)] = ' ';
}

bool Level::Convert(int* playerX, int* playerY) {
	bool anyWarnings = false;

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			int index = GetIndexFromCoordinates(x, y);

			switch (m_pLevelData[index]) {
			case '+':
			case '-':
			case '|':
				m_pLevelData[index] = WALLL;
				break;
			case '*':
				m_pLevelData[index] = KEY;
				break;
			case 'D':
				m_pLevelData[index] = DOOR;
				break;
			case 'X':
				m_pLevelData[index] = GOAL;
				break;
			case '@':
				m_pLevelData[index] = ' ';
				if (playerX != nullptr && playerY != nullptr) {
					*playerX = x;
					*playerY = y;
				}
				break;
			case ' ':
				break;
			default:
				cout << "Invalid character in level file: " << m_pLevelData[index] << endl;
				anyWarnings = true;
				break;
			}
		}
	}
	return anyWarnings;

}


int Level::GetIndexFromCoordinates(int x, int y) {
	return x + y * m_width;
}


PlaceableActor* Level::UpdateActor(int x, int y)
{
	PlaceableActor* collidedActor = nullptr;

	for (auto actor = m_pActors.begin(); actor != m_pActors.end(); ++actor)
	{
		(*actor)->Update();

		if (!(*actor))->IsActive())
		{
		  continue;
		}

		if (x == (*actor)->GetPosition() && y == (*actor)->GetYPosition())
		{
			assert(collidedActor == nullptr);
			collidedActor = (*actor);
		};
	}
	return collidedActor;
}