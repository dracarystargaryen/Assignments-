#include <iostream>
#include "Player.h"
#include "Key.h"
#include "AudioManager.h"
#include "Cat.h"

using namespace std;

constexpr char kStartingNumberOfLives = 5;


Player::Player()
	: PlaceableActor(0,0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(kStartingNumberOfLives)

{

}


bool Player::HasKey() {
	return m_pCurrentKey != nullptr;

}
void Player::PickupKey(Key* key) {
	m_pCurrentKey = key;
}
void Player::UseKey() {
	if (m_pCurrentKey) {

		m_pCurrentKey->Remove();
		m_pCurrentKey = nullptr;
	}
}

void Player::DropKey()
{
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw() {
	cout << "@";
}