#pragma once

#include "Includes.h"

int rollDice(int numberOfFaces)//���� ����� ���� � ��������� ������������ ������
{
	int value = std::rand() % numberOfFaces + 1;

	if(numberOfFaces==10 && value==10) value += std::rand() % numberOfFaces + 1;

	return value;
}

int rollRange(int min, int range)// ����� ����� �� ��������� �� range �� ������� � ���������� � ���� min
{
	if (range == 0)return 0;
	int value = std::rand() % range + min;

	return value;
}

int armorPenetration(int sp, int damage, int btm) {
	int totalDamage = 0;
	int stoppedDamage = sp - damage;

	if (stoppedDamage >= 0)return 0;// ������ ��� ����� �� �������
	stoppedDamage += btm;
	if (stoppedDamage >= 0) totalDamage = 1;

	totalDamage = std::abs(stoppedDamage);

	return totalDamage;
}