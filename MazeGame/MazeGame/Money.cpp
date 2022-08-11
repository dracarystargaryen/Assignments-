#include <iostream>
#include "Money.h"

using namespace std;

Money::Money(int i, int j, int value)
	: PlaceableActor(i, j)
	, m_value(value)

{


}

void Money::Draw()
{
	cout << "$";
}