#pragma once
#include "GameFunctions.h"

class BaseWeapon {
public:
	int qtyOfDamage;//����������� �����
	int damageBonus;//����� �����
	int hitBonus;//����� ��������� 
	int numberOfAttacks;
};


class BaseCharacter {
public:
	BaseCharacter();
	~BaseCharacter();

	int attack();// ���������� ����� � �������� �� �� numberOfDamage
	int howMuchDamage();//���������� �������� ����������� �����
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
	weapon.qtyOfDamage = rollRange(2, 3);
	weapon.numberOfAttacks = rollRange(1, 3);

	//������������� ������
	Ref = rollRange(6, 5);
	Body = rollRange(4, 8);

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

	if (rollHit < rollRange(10,11)) return 0; // ���� �� ����� �� ���� 0, ��������� ��������� �� 10 �� 20 

	switch (weapon.numberOfAttacks)
	{
	case 1:
		totalDamage += dealWeaponDamage(weapon.qtyOfDamage, 1);
		break;
	case 2:
		switch ((int)std::floor(rollDice(4) / 2))//��������� �� int ����������� ���������
		{
		case 1:
			totalDamage += dealWeaponDamage(weapon.qtyOfDamage, 1);
			break;
		case 2:
			totalDamage += dealWeaponDamage(weapon.qtyOfDamage, 2);
			break;
		case 3:
			totalDamage += dealWeaponDamage(weapon.qtyOfDamage, 3);
			break;
		}
		break;
	case 3:
		switch ((int)std::floor(rollDice(6) / 2))//��������� �� int ����������� ���������
		{
		case 1:
			totalDamage += dealWeaponDamage(weapon.qtyOfDamage, 1);
			break;
		case 2:
			totalDamage += dealWeaponDamage(weapon.qtyOfDamage, 2);
			break;
		case 3:
			totalDamage += dealWeaponDamage(weapon.qtyOfDamage, 3);
			break;
		}
		break;
	}
		
	if (rollDice(100) == 100) totalDamage += rollDice(6) * 7; // ���������� ���� ���� ��� ��� ��� ������ �������

	totalDamage += weapon.damageBonus;

	return totalDamage;
}

inline int BaseCharacter::howMuchDamage()
{
	return takenDamage;
}

inline void BaseCharacter::takeDamage(int damage)
{
	int totalDamage = 0;
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
