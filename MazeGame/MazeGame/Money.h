#pragma once
#include "PlaceableActor.h"

class Money : public PlaceableActor
{
public:
	Money(int i, int j, int value);

	int GetValue() const { return m_value; }

	virtual ActorType GetType() override { return ActorType::Money; }
	virtual void Draw() override;

private:
	int m_value;
};