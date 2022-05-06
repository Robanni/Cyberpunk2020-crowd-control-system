
#include "GameClass.h"
#include <vector>


int main() {
	std::srand(time(NULL));

	begining://������ � �������� ��� �� ��� ��� �����. ����� �������� � ������

	int round=0;
	int weWantToWatchRounds;
	unsigned numberOfAllies, numberOfEnemies ;

	std::cout << "Number of allies:";
	std::cin >> numberOfAllies;
	std::cout << std::endl << "Number of Enemies:";
	std::cin >> numberOfEnemies;
	std::cout << std::endl;
	std::cout << "What round do you want to watch:";
	std::cin >> weWantToWatchRounds;
	std::cout << std::endl;

	std::vector<BaseCharacter*> allieTeam(numberOfAllies,nullptr);
	std::vector<BaseCharacter*> enemyTeam(numberOfEnemies,nullptr);

	for (auto i = allieTeam.begin(); i != allieTeam.end(); ++i)
	{
		(*i) = new BaseCharacter();//�������� ���������
	}
	
	for (auto i = enemyTeam.begin(); i != enemyTeam.end(); ++i)
	{
		(*i) = new BaseCharacter();// �������� ���������
	}

	while (allieTeam.size() != 0 && enemyTeam.size() != 0)
	{
		int i, j;//���������� ��� ��������
		for (i = 0, j = 0; i <allieTeam.size(); ++i, ++j) {// ������ ������ ���� �������������� ���� ���� �� ����

			if (enemyTeam.empty()) break;//���� ��������� ������ ���� �� ���� ���������
			if (j >= enemyTeam.size() )j = 0;// ���� �� ������� �� ����� �������, �� ���� � ��� ������ 

			enemyTeam[j]->takeDamage(allieTeam[i]->attack());//���� �������� ����
			enemyTeam[j]->deathRoll();//����� ����� �� ������� 

			if (enemyTeam[j]->isAlive == false)// �������� ������ 
			{
				enemyTeam.erase(enemyTeam.begin()+j);//��� ������� �� ������
				j--; //����� �������� �� ������� ����� ����� ��������� ��� ��� ������ ��������� 
			}
		}

		for (i = 0, j = 0; i < enemyTeam.size(); ++i, ++j) {// ����� ��� ��� � ������� ����

			if (allieTeam.empty()) break;
			if (j >= allieTeam.size())j = 0;

			allieTeam[j]->takeDamage(enemyTeam[i]->attack());
			allieTeam[j]->deathRoll();

			if (allieTeam[j]->isAlive == false)
			{
				allieTeam.erase(allieTeam.begin() + j);
				j--;
			}
		}
	
		round++;
		if (round == weWantToWatchRounds) {// ����� �� ����������� ������������� �������
			int allieHurt = 0;
			int enemyHurt = 0;


			std::cout << "Allie number:" << allieTeam.size() << std::endl;
			for (size_t i = 0; i < allieTeam.size(); i++)
			{
				if (allieTeam[i]->howMuchDamage() > 16) allieHurt++;//������� ��������
			}
			std::cout << "Allie hurted guys:" << allieHurt << std::endl;
			std::cout << std::endl;


			std::cout << "Enemy number:" << enemyTeam.size() << std::endl;
			for (size_t i = 0; i < enemyTeam.size(); i++)
			{
				if (enemyTeam[i]->howMuchDamage() > 16) enemyHurt++;
			}
			std::cout << "Enemy hurted guys:" << enemyHurt << std::endl;
			std::cout << std::endl;


			std::cout << "Number of rounds:" << round << std::endl;
			std::cout << std::endl;


			std::cout << "What round do you want to watch:";
			std::cin >> weWantToWatchRounds;
			std::cout << std::endl;
		}

	}

	int theyWillDie = 0;

	if(allieTeam.size() != 0) 
	{
		for (size_t i = 0; i < allieTeam.size(); i++)
		{
			if (allieTeam[i]->howMuchDamage() > 16) theyWillDie++;
		}
	}
	else
	{
		for (size_t i = 0; i < enemyTeam.size(); i++)
		{
			if (enemyTeam[i]->howMuchDamage() > 16) theyWillDie++;
		}
	}

	std::cout << "Allie number:" << allieTeam.size() << std::endl;
	std::cout << "Enemy number:" << enemyTeam.size() << std::endl;
	std::cout << "they survived but will die:" << theyWillDie << std::endl;
	std::cout << "Number of rounds:" << round<<std::endl;

	char request;
	std::cout << "Next fight?(y|n)" << std::endl;
	std::cin >> request;
	if (request == 'y') goto begining;//������ � �������� ���, �� ��� ��� �����. ������� � ������ 

	return 0;
}