#include <iostream>
#include <conio.h>
#include <windows.h>

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


int main()
{
	constexpr int mWidth = 25;
	constexpr int mHeight = 15;

	char levelArray[]{ WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,'*',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,WALL,WALL,WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,' ',' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','D',' ',' ',' ',WALL,
					   WALL,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',WALL,' ',' ',' ',WALL,
					   WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL, };

	int playerX = 1;
	int playerY = 1;
	bool playerHasKey = false;
	bool gameOver = false;

	while (!gameOver) {

		system("cls");
		DrawLevel(levelArray, mWidth, mHeight, playerX, playerY, playerHasKey);
		gameOver = UpdatePlayerPosition(levelArray, playerX, playerY, mWidth, playerHasKey);
	}
	system("cls");
	DrawLevel(levelArray, mWidth, mHeight, playerX, playerY, playerHasKey);
	cout << "You won!" << endl;
	PlayWinSound();
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



