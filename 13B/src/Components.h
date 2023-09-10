/*********************************************************************************************************
;**********								13B Components Interface								**********
;*********************************************************************************************************
;
;PACKAGE NAME:	Components.h - 13B Components Interface
;
;FUNCTION:
;
;	This unit contains the declarations and definitions required to create components for use with 
;	Entity objects in the 13B game engine. Components are declared as uninitialized pointers in each
;	Entity object, when initialized in an Entity object the Entity include the data specified by 
;	the component for use in the applicable system.
;
;	All component classes are pure data, and essentially structs as all members are
;	public, component classes have no added functionality outside of constructor.

;
;PUBLIC DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	CTransform	- 13B Transform Class
;	CShape		- 13B Shape Class
;	CCollision	- 13B Collision Class
;	CScore		- 13B Score Class
;	CLifespan	- 13B Lifespan Class
;	CInput		- 13B Input Class
;
;	PUBLIC SYMBOLS
;	--------------
;	pos			- Vector for holding Entity position
;	velocity	- Vector for holding Entity velocity
;	angle		- Vector for holding Entity rotation angle
;	circle		- Circle object from SFML for holding shape characteristics
;	radius		- Float for holding Entity's collision radius
;	score		- Integer for holding player score
;	remaining	- Integer for holding Entity's remaining lifespan
;	total		- Integer for holding Entity's total lifespa
;	up			- Boolean for holding 'up' key press
;	left		- Boolean for holding 'left' key press
;	down		- Boolean for holding 'down' key press
;	right		- Boolean for holding 'right' key press
;
;	PUBLIC SUB-PROGRAMS
;	------------------
;	Components::CTransform	- Constructor
;	Components::CShape		- Constructor
;	Components::CCollision	- Constructor
;	Components::CScore		- Constructor
;	Components::CLifespan	- Constructor
;	Components::CInput		- Constructor
;
;PRIVATE DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	None
;
;	PRIVATE SYMBOLS
;	---------------
;	None
;
;	PRIVATE SUB-PROGRAMS
;	--------------------
;	None
;
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"


class CTransform
{
public:

	Vec2  pos		= { 0.0, 0.0 };
	Vec2  velocity	= { 0.0, 0.0 };
	float angle		= 0;

	CTransform(const Vec2& p, const Vec2& v, float a)
		: pos(p), velocity(v), angle(a) {}
};

class CShape
{
public:

	sf::CircleShape circle;

	CShape(float radius,
		   int points,
		   const sf::Color& fill,
		   const sf::Color& outline,
		   float thickness)
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}
};

class CCollision
{
public:

	float radius = 0;

	CCollision(float r)
		: radius(r) {}
};

class CScore
{
public:

	int score = 0;	// 100*vertices for large enemies, 200*vertices for small enemies

	CScore(int s)
		: score(s) {}
};

class CLifespan
{
public:
	int remaining	= 0;	// remaining lifespan of Entity in frames
	int total		= 0;	// total lifespan of Entity in frames

	CLifespan(int r, int t)
		: remaining(r), total(t) {}
};

class CInput
{
public:
	bool up		= false;
	bool left	= false;
	bool down	= false;
	bool right	= false;

	CInput() {}
};