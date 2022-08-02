#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;


constexpr char mPlayerSymbol = '@';
constexpr char WALL = 219;
constexpr char KEY = 232;
constexpr char DOOR = 179;
constexpr char GOAL = 36;
constexpr char kOpenDoorColor = 10;
constexpr char kClosedDoorColor = 12;
constexpr char kRegularColor = 7;


int GetIndexFromCoordinates(int x, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHaskHey);
bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey);
void PlayDoorClosedSound();
void PlayDoorOpenSound();
void PlayKeyPickupSound();
void PlayWinSound();
char* LoadLevel(string levelName, int& width, int& height);
bool ConvertLevel(char* level, int width, int height, int& playerX, int& playerY);


int main()
{
	 int width = 0;
	 int height = 0;

	 char* levelArray = LoadLevel("Level1.txtg", width, height);


	int playerX = 1;
	int playerY = 1;
	bool anyWarnings = ConvertLevel(levelArray, width, height, playerX, playerY);
	if (anyWarnings) {

		cout << "There were some warnings in the level data, see above." << endl;
		system("pause");
	}

	bool playerHasKey = false;
	bool gameOver = false;

	while (!gameOver) {

		system("cls");
		DrawLevel(levelArray, width, height, playerX, playerY, playerHasKey);
		gameOver = UpdatePlayerPosition(levelArray, playerX, playerY, width, playerHasKey);
	}
	system("cls");
	DrawLevel(levelArray, width, height, playerX, playerY, playerHasKey);
	cout << "You won!" << endl;
	PlayWinSound();

	delete[] levelArray;
	
}

char* LoadLevel(string levelName, int& width, int& height) {
	levelName.insert(0, "../");
	ifstream levelFile;
	levelFile.open(levelName);
	if (!levelFile) {
		cout << "Opening file failed!" << endl;
		return nullptr;
	}
	else {
		constexpr int tempSize = 25;
		char temp[tempSize];

		levelFile.getline(temp, tempSize, '\n');
		width = atoi(temp);

		levelFile.getline(temp, tempSize, '\n');
		height = atoi(temp);

		char* levelData = new char[width * height];
		levelFile.read(levelData, width * height);
		return levelData;
	}
}

bool ConvertLevel(char* level, int width, int height, int& playerX, int& playerY) {
	bool anyWarnings = false;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index = GetIndexFromCoordinates(x, y, width);

			switch (level[index]) {
			case '+':
			case '-':
			case '|':
				level[index] = WALL;
					break;
			case '*':
				level[index] = KEY;
				break;
			case 'D':
				level[index] = DOOR;
				break;
			case 'X': 
				level[index] = GOAL;
				break;
			case '@':
				level[index] = ' ';
				playerX = x;
				playerY = y;
				break;
			case ' ':
				break;
				default:
					cout << "Invalid character in level file: " << level[index] << endl;
					anyWarnings = true;
					break;
			}
		}
	}
	return anyWarnings;
}

	int GetIndexFromCoordinates(int x, int y, int width)
	{
		return x + y * width;
	}

	void DrawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHasKey)
	{
		for (int y = 0; y < height; y++) {

			for (int x = 0; x < width; x++) {
				if (playerX == x && playerY == y) {
					cout << mPlayerSymbol;
				}
				else {
					int index = GetIndexFromCoordinates(x, y, width);
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					if (level[index] == DOOR) {
						if (playerHasKey) {
							SetConsoleTextAttribute(console, kOpenDoorColor);
						}
						else {
							SetConsoleTextAttribute(console, kOpenDoorColor);
						}
					}
					cout << level[index];
				}

			}
			cout << endl;
		}
	}
   bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey) {
		char input = _getch();

		int newPlayerX = playerX;
		int newPlayerY = playerY;

		switch (input) {
		case 'w':
		case 'W': 
		{
			playerY--;
			break;
		}
		case 'a':
		case 'A':
		{
			playerY++;
			break;
		}
		case 's':
		case 'S':
		{
			playerX--;
			break;
		}
		case 'd':
		case 'D':
		{
			playerX++;
			break;
		}
		default:
			break;
		}

		int index = GetIndexFromCoordinates(newPlayerX, newPlayerY, width);
		if (level[index] == ' ') {
			playerX = newPlayerX;
			playerY = newPlayerY;
		}
		else if (level[index] == KEY) {
			playerHasKey = true;
			level[index] = ' ';
			playerX = newPlayerX;
			playerY = newPlayerY;
			PlayKeyPickupSound();

		}
		else if (level[index] == DOOR && playerHasKey) {
			level[index] = ' ';
			playerHasKey = false;
			playerX = newPlayerX;
			playerY = newPlayerY;
			PlayDoorOpenSound();
		}
		else if (level[index] == DOOR && !playerHasKey) {
			PlayDoorClosedSound();
		}

		else if (level[index] == GOAL) {
			level[index] = ' ';
			playerX = newPlayerX;
			playerY = newPlayerY;
			return true;
			
		}
		return false;
}

   void PlayDoorClosedSound() {
	   Beep(500, 75);
	   Beep(500, 75);
   }
   void PlayDoorOpenSound() {
	   Beep(1397, 200);
   }
   void PlayKeyPickupSound() {
	   Beep(1568, 200);
   }
   void PlayWinSound() {
	   Beep(1568, 200);
	   Beep(1568, 200);
	   Beep(1568, 200);
	   Beep(1245, 1000);
	   Beep(1397, 200);
	   Beep(1397, 200);
	   Beep(1397, 200);
	   Beep(1175, 1000);
   }

 


