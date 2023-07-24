#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Vec2.h"		// added for testing, delete for final
#include <iostream>		// added for testing, delete for final

int main()
{
	Game g("config.txt");
	g.run();

	/*-----------------------	Test Code (delete for final) -----------------------*/
	Vec2 v1(1, 1);
	Vec2 v2(1, 1);

	v1 = v1 + v2;
	std::cout << v1.x << "," << v1.y << std::endl;
}