#include <math.h>
#include "Vec2.h"

Vec2::Vec2() {}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin) {}

bool Vec2::operator == (const Vec2& rhs) const		
{
	return (this->x == rhs.x && this->y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const		
{
	return(this->x != rhs.x || this->y != rhs.y);
}

Vec2 Vec2::operator + (const Vec2& rhs) const		
{
	return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const		
{
	return Vec2(this->x - rhs.x, this->y - rhs.y);
}

Vec2 Vec2::operator / (const float val) const		
{
	return Vec2(this->x / val, this->y / val);
}

Vec2 Vec2::operator * (const float val) const		
{
	return Vec2(this->x * val, this->y * val);
}

// Calculate length of hypoteneuse (distance between two entities)
double Vec2::length(const Vec2& rhs) const			
{
	Vec2 vec2_delta = *this - rhs;

	return sqrtf(pow(vec2_delta.x, 2) + pow(vec2_delta.y, 2));
}

// Function works as written, however UML shows return type as void
Vec2 Vec2::normalize(Vec2& rhs) const				// Tested
{
	double length = this->length(rhs);
	return Vec2(this->x / length, this->y / length);
}

/* Implement later, maybe
Vec2 Vec2::operator += (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
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