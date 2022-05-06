#pragma once

#include "Includes.h"

int rollDice(int numberOfFaces)
//тупо ролим дайс с указанным колличеством граней
{
	int value = std::rand() % numberOfFaces + 1;

	if(numberOfFaces==10 && value==10) value += std::rand() % numberOfFaces + 1;

	return value;
}

int rollRange(int min, int range)
// ролит число из диапазона до range не включая и прибавляет к нему min
{
	if (range == 0)return 0;
	int value = std::rand() % range + min;

	return value;
}

int armorPenetration(int sp, int damage, int btm)
{
	int totalDamage = 0;
	int stoppedDamage = sp - damage;

	if (stoppedDamage >= 0)return 0;// случай где броня не пробита
	stoppedDamage += btm;
	if (stoppedDamage >= 0) totalDamage = 1;

	totalDamage = std::abs(stoppedDamage);

	return totalDamage;
}

int dealWeaponDamage(int weaponDamageQty, int numberOfAttacks) 
{
	int damage = 0;
	for (size_t i = 0; i != numberOfAttacks; i++)
	{
		for (int i = 0; i < weaponDamageQty; i++)
		{
			damage += rollDice(6);//Ролим несколько d6 
		}
	}
	return damage;
}