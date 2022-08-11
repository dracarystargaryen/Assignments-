#include "Cat.h"
#include "PlaceableActor.h"
#include "MazeGame.cpp"
#include <iostream>


using namespace std;

constexpr char cPlayerSymbol = 'c';

Cat::Cat() 
	: hasKey(false)
{

}

void Cat::SetPosition(int x, int y) {
	m_position.x = x;
	m_position.y = y;
}

bool Cat::HasKey() {
	return hasKey;

}
void Cat::PickupKey() {
	hasKey = true;
}
void Cat::UseKey() {

}

void Cat::Draw() {
	cout << mPlayerSymbol;
}