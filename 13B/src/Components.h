#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"

/*------------------------------------	Components	------------------------------------
;	All component classes are pure data, and essentially structs as all members are
;	public, component classes have no added functionality outside of constructor.
*/ 
class CTransform
{
public:

	Vec2 pos		= { 0.0, 0.0 };
	Vec2 velocity	= { 0.0, 0.0 };
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
	bool shoot	= false;

	CInput() {}
};