#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Vec2.h"		// added for testing, delete for final
#include <iostream>		// added for testing, delete for final

int main()
{
	//Game g("config.txt");
	//g.run();

	/*-----------------------	Test Code (delete for final) -----------------------*/
	Vec2 v1(5, 5);
	Vec2 v2(10, 10);

	v1.normalize(v2);

	std::cout << sqrtf(pow(v1.x, 2) + pow(v1.y, 2)) << std::endl;
}