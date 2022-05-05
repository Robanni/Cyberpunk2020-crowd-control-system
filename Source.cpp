
#include "GameClass.h"
#include <vector>


int main() {
	std::srand(time(NULL));
	int round=0;
	unsigned numberOfAllies, numberOfEnemies ;

	std::cout << "Number of allies:";
	std::cin >> numberOfAllies;
	std::cout << std::endl << "Number of Enemies:";
	std::cin >> numberOfEnemies;
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
	}

	std::cout << "Allie number:" << allieTeam.size() << std::endl;
	std::cout << "Enemy number:" << enemyTeam.size() << std::endl;
	std::cout << "Number of rounds:" << round<<std::endl;

	system("pause");

	return 0;
}