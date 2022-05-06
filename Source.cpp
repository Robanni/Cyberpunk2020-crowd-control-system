
#include "GameClass.h"
#include <vector>


int main() {
	std::srand(time(NULL));

	begining://—тарье и спагетти код но мне все равно. “очка переноса в начало

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
		(*i) = new BaseCharacter();//рождение персонажа
	}
	
	for (auto i = enemyTeam.begin(); i != enemyTeam.end(); ++i)
	{
		(*i) = new BaseCharacter();// –ождение персонажа
	}

	while (allieTeam.size() != 0 && enemyTeam.size() != 0)
	{
		int i, j;//переменные дл€ перебора
		for (i = 0, j = 0; i <allieTeam.size(); ++i, ++j) {// честно говор€ даже комментировать этот блок не хочу

			if (enemyTeam.empty()) break;//≈сли вражеский массив пуст то цикл кончаетс€
			if (j >= enemyTeam.size() )j = 0;// если мы выходим за рамки вектора, то идем в его начало 

			enemyTeam[j]->takeDamage(allieTeam[i]->attack());//¬раг получает урон
			enemyTeam[j]->deathRoll();//–олит чтобы не умереть 

			if (enemyTeam[j]->isAlive == false)// ѕроверка смерти 
			{
				enemyTeam.erase(enemyTeam.begin()+j);//его удал€ют из списка
				j--; //чтобы остатьс€ на прошлом месте нужен декримент так как вектор сдвинетс€ 
			}
		}

		for (i = 0, j = 0; i < enemyTeam.size(); ++i, ++j) {// «десь все как в приколе выше

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
		if (round == weWantToWatchRounds) {// ѕауза на колличество просмотренных раундов
			std::cout << "Allie number:" << allieTeam.size() << std::endl;
			std::cout << "Enemy number:" << enemyTeam.size() << std::endl;
			std::cout << "Number of rounds:" << round << std::endl;

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
	if (request == 'y') goto begining;//—тарье и спагетти код, но мне все равно. ѕеренос в начало 

	return 0;
}