#pragma once
#include "PlaceableActor.h"

class Key;

class Player : public PlaceableActor
{
public:
	Player();

	void SetPosition(int x, int y);

	//inventory interface or composition
	bool HasKey();
	void PickupKey(Key* key);
	bool HasKey(ActorColor color);
	void UseKey();
	void DropKey();
	Key* GetKey() { return m_pCurrentKey; }

	void AddMoney(int money) { m_money += money; }
	int GetMoney() { return m_money; }

	//ILiveable
	//create a function OnLoseLive or ColllideWithEnemy
	int GetLives() { return m_lives; }
	void DecrementLives() { m_lives--; }

	virtual ActorType GetType() override { return ActorType::Player; }
	virtual void Draw() override;
private:
	Key* m_pCurrentKey;
	int m_money;
	int m_lives;
};