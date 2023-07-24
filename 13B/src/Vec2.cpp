#include <math.h>
#include "Vec2.h"

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin)
{

}

bool Vec2::operator == (const Vec2& rhs) const
{
	return (this->x == rhs.x && this->y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	// TODO
	return false;
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	// TODO
	return Vec2(0, 0);
}

Vec2 Vec2::operator / (const float val) const
{
	// TODO
	return Vec2(0, 0);
}

Vec2 Vec2::operator * (const float val) const
{
	return Vec2(this->x * val, this->y * val);
}

void Vec2::operator += (const Vec2& rhs) const
{
	// TODO
}

void Vec2::operator -= (const Vec2& rhs) const
{
	// TODO
}

void Vec2::operator /= (const Vec2& rhs) const
{
	// TODO
}

void Vec2::operator *= (const Vec2& rhs) const
{
	// TODO
}

float Vec2::dist(const Vec2& rhs) const
{
	// TODO
	return 0;
}

float Vec2::length() const
{
	// TODO
	return 0;
}