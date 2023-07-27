#include <math.h>
#include "Vec2.h"

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin) {}

bool Vec2::operator == (const Vec2& rhs) const		// Tested
{
	return (this->x == rhs.x && this->y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const		// Tested
{
	return(this->x != rhs.x || this->y != rhs.y);
}

Vec2 Vec2::operator + (const Vec2& rhs) const		// Tested 
{
	return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const		// Tested
{
	return Vec2(this->x - rhs.x, this->y - rhs.y);
}

Vec2 Vec2::operator / (const float val) const		// Tested
{
	return Vec2(this->x / val, this->y / val);
}

Vec2 Vec2::operator * (const float val) const		// Tested
{
	return Vec2(this->x * val, this->y * val);
}

float Vec2::length(const Vec2& rhs) const		// Tested
{
	float x_dist = rhs.x - this->x;
	float y_dist = rhs.y - this->y;

	return sqrtf(pow(x_dist, 2) + pow(y_dist, 2));
}

Vec2 Vec2::normalize() const 
{
	return Vec2(this->x / this->length(*this), this->y / this->length(*this));
}

/*	Implement later (maybe)
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
*/