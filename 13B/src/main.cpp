#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Vec2.h"		// added for testing, delete for final
#include <iostream>		// added for testing, delete for final

int main()
{
	//Game g("config.txt");
	//g.run();

	/*-----------------------	Test Code (delete for final) -----------------------*/
	Vec2 v1(1, 1);
	Vec2 v2(4, 6);

	std::cout << v2.x << "," << v2.y << std::endl;
}