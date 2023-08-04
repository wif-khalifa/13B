#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Vec2.h"		// added for testing, delete for final
#include <iostream>		// added for testing, delete for final

int main()
{
	Game g("config.txt");
	g.run();

	/*-----------------------	Test Code (delete later) -----------------------*/
	Vec2 player(640, 360);
	Vec2 bullet(840, 160);
	double pToB = player.length(bullet);
	double bToP = bullet.length(player);
		
	std::cout << pToB << std::endl;
	std::cout << bToP << std::endl;

	bullet.normalize(player);
	std::cout << bullet.x << " " << bullet.y << std::endl;
	std::cout << bullet.length(Vec2(0, 0)) << std::endl;
}