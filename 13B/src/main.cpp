#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Vec2.h"		// added for testing, delete for final
#include <iostream>		// added for testing, delete for final

int main()
{
	//Game g("config.txt");
	//g.run();

	/*-----------------------	Test Code (delete for final) -----------------------*/
	EntityManager e;
	e.addEntity("pitufo");
	e.update();
}