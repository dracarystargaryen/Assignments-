#pragma once
#include <string>
#include <vector>

class Level {
	char* m_pLevelData;
	int m_height;
	int m_width;

	std::vector<PlaceableActor*> m_pActors;

public:
	Level();
	~Level();


	bool Load(std::string levelName, int* playerX, int* playerY);
	void Draw(int x, int y);
	void ActorUpdate();
	PlaceableActor* CheckForCollisions(int x, int y);

	bool IsSpace(int x, int y);
	bool IsDoor(int x, int y);
	bool IsWALL(int x, int y);
	bool IsKey(int x, int y);
	bool IsGoal(int x, int y);

	void PickUpKey(int x, int y);
	void OpenDoor(int x, int y);

	int GetHeight() { return m_height;  }
	int GetWidth() { return m_width; }

	static constexpr char WALL = (char)219;


private:
	bool Convert(int* playerX, int* playerY);
	int GetIndexFromCoordinates(int x, int y);



};
