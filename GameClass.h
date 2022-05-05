#pragma once
#include "GameFunctions.h"

class BaseWeapon {
public:
	int qtyOfDamage;
	int damageBonus;
	int hitBonus;
};


class BaseCharacter {
public:
	BaseCharacter();
	~BaseCharacter();

	int attack();// ���������� ����� � �������� �� �� numberOfDamage
	void takeDamage(int damage);//�������� ����
	void deathRoll();
	bool isAlive;
protected:
	BaseWeapon weapon;//������ ���������
	//
	// �������������� ���������
	//
	// ���� ������
	int Ref;
	int Body;
	//
	// �������������� ������ � ������������
	//
	int Save;
	int BTM;
	int takenDamage;
	//
	// ����� ���������
	//
	int SPHead;
	int SPTorso;
	int SPRArm;
	int SPLArm;
	int SPRLeg;
	int SPLLeg;

};

//���������� �������, ������������ � �������������

//���������� BaseCharacter
BaseCharacter::BaseCharacter()
{
	// ������������� ������
	weapon.damageBonus = rollRange(0, 4);
	weapon.hitBonus = rollRange(0, 4);
	weapon.qtyOfDamage = rollRange(2, 5);

	//������������� ������
	Ref = rollRange(6, 5);
	Body = rollRange(10, 1);

	//������������� �����
	SPHead = rollRange(0, 14);
	SPTorso = rollRange(0, 18);
	SPRArm = rollRange(0, 12);
	SPLArm = rollRange(0, 12);
	SPRLeg = rollRange(0, 10);
	SPLLeg = rollRange(0, 10);

	//������������� ��������
	takenDamage = 0;
	Save = Body;
	if (Body <= 2)// ��� ����������� ����������� ���������� ����������� ������������� ����� 
	{
		BTM = 0;
	}
	else if (Body <= 4)
	{
		BTM = 1;
	}
	else if (Body <= 7)
	{
		BTM = 2;
	}
	else if (Body <= 9)
	{
		BTM = 3;
	}
	else
	{
		BTM = 4;
	}
	isAlive = true;
}

inline BaseCharacter::~BaseCharacter()
{
}

inline int BaseCharacter::attack()
{
	int totalDamage = 0;
	int rollHit = rollDice(10) + Ref + weapon.hitBonus;//����� ���������, ������ ��������� �� ���� ��� � ���� �������� ������� 5

	if (rollHit < 15) return 0; // ���� �� ����� �� ���� 0, ����������, ��� ��������� ������ ����������, ��� ��� ����� ��������� ��� 

	for (int i = 0; i < weapon.qtyOfDamage; i++)
	{
		totalDamage += rollDice(6);//����� ��������� d6 
	}
	
	totalDamage += weapon.damageBonus;

	return totalDamage;/*�������� d6 �� ����������� ���� d6, ���������
								��� ��� �� ���������� ��� �� ����� ����� ������ ������ ��������, ����� ��������� ������*/
}

inline void BaseCharacter::takeDamage(int damage)
{
	int totalDamage =0;
	int hadShotIn = rollDice(10);
	
	switch (hadShotIn)
	{
	case 1:
		totalDamage = armorPenetration(SPHead, damage, BTM)*2;
		break;
	case 2:
	case 3:
	case 4:
		totalDamage = armorPenetration(SPTorso, damage, BTM);
		break;
	case 5:
		totalDamage = armorPenetration(SPRArm, damage, BTM);
		break;
	case 6:
		totalDamage = armorPenetration(SPLArm, damage, BTM);
		break;
	case 7:
	case 8:
		totalDamage = armorPenetration(SPRLeg, damage, BTM);
		break;
	case 9:
	case 10:
		totalDamage = armorPenetration(SPLArm, damage, BTM);
		break;
	}

	takenDamage += totalDamage;
}

inline void BaseCharacter::deathRoll()
{
	int deathPosition = std::ceil(takenDamage / 4);
	int deathChance = deathPosition - 4;

	if (deathPosition >= 4) {
		if (rollDice(10) > Save - deathChance)isAlive = false;
	}
}
