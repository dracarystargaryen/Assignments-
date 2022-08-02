#include "Player.h"
#include <iostream>

using namespace std;

constexpr char mPlayerSymbol = '@';


Player::Player() 
	: m_hasKey(false)

{

}
Player::~Player() {

}

int GetXPosition() {

}
int GetYPosition() {

}

void Player::SetPosition(int x, int y) {
	m_position.x = x;
	m_position.y = y;
}

bool Player::HasKey() {
	return m_hasKey;

}
void Player::PickupKey() {
	m_hasKey = true;
}
void Player::UseKey() {

}

void Player::Draw() {
	cout << mPlayerSymbol;
}