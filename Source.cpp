
#include "GameClass.h"
#include <vector>


int main() {
	std::srand(time(NULL));
	int round=0;

	BaseCharacter allie;
	BaseCharacter enemy;

	while (allie.isAlive && enemy.isAlive )
	{
		enemy.takeDamage(allie.attack());
		enemy.deathRoll();
		if (enemy.isAlive == false)break;

		allie.takeDamage(enemy.attack());
		allie.deathRoll();
		if (allie.isAlive == false)break;

		round++;
	}

	if (allie.isAlive == true) std::cout << "we won!" << std::endl;
	else std::cout << "we lose!" << std::endl;
	std::cout << "number of rounds:" << round<<std::endl;

	system("pause");

	return 0;
}