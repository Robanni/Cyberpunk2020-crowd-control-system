
#include "GameClass.h"
#include <vector>


int main() {
	std::srand(time(NULL));

	begining://Старье и спагетти код но мне все равно. Точка переноса в начало

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
		(*i) = new BaseCharacter();// Рождение персонажа
	}

	while (allieTeam.size() != 0 && enemyTeam.size() != 0)
	{
		int i, j;//переменные для перебора
		for (i = 0, j = 0; i <allieTeam.size(); ++i, ++j) {// честно говоря даже комментировать этот блок не хочу

			if (enemyTeam.empty()) break;//Если вражеский массив пуст то цикл кончается
			if (j >= enemyTeam.size() )j = 0;// если мы выходим за рамки вектора, то идем в его начало 

			enemyTeam[j]->takeDamage(allieTeam[i]->attack());//Враг получает урон
			enemyTeam[j]->deathRoll();//Ролит чтобы не умереть 

			if (enemyTeam[j]->isAlive == false)// Проверка смерти 
			{
				enemyTeam.erase(enemyTeam.begin()+j);//его удаляют из списка
				j--; //чтобы остаться на прошлом месте нужен декримент так как вектор сдвинется 
			}
		}

		for (i = 0, j = 0; i < enemyTeam.size(); ++i, ++j) {// Здесь все как в приколе выше

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
		if (round == weWantToWatchRounds) {// Пауза на колличество просмотренных раундов
			int allieHurt = 0;
			int enemyHurt = 0;


			std::cout << "Allie number:" << allieTeam.size() << std::endl;
			for (size_t i = 0; i < allieTeam.size(); i++)
			{
				if (allieTeam[i]->howMuchDamage() > 16) allieHurt++;//Раненые союзники
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
	if (request == 'y') goto begining;//Старье и спагетти код, но мне все равно. Перенос в начало 

	return 0;
}