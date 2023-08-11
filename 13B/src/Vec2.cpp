/**********************************************************************************************************
;**********								TODO
;**********************************************************************************************************
;
;PACKAGE NAME:	TODO
;
;FUNCTION:
;
;	This unit contains the source code designed to...TODO
;
;PUBLIC DECLARATIONS:
;
;	PUBLIC SYMBOLS
;	--------------
;	TODO
;
;	PUBLIC SUB-PROGRAMS
;	------------------
;	TODO
;
;PRIVATE DECLARATIONS:
;
;	PRIVATE SYMBOLS
;	---------------
;	TODO
;
;	PRIVATE SUB-PROGRAMS
;	--------------------
;	TODO
;
*/

#include <math.h>
#include "Vec2.h"


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
Vec2::Vec2() {}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin) {}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
bool Vec2::operator == (const Vec2& rhs) const		
{
	return (this->x == rhs.x && this->y == rhs.y);
}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
bool Vec2::operator != (const Vec2& rhs) const		
{
	return(this->x != rhs.x || this->y != rhs.y);
}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
Vec2 Vec2::operator + (const Vec2& rhs) const		
{
	return Vec2(this->x + rhs.x, this->y + rhs.y);
}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
Vec2 Vec2::operator - (const Vec2& rhs) const		
{
	return Vec2(this->x - rhs.x, this->y - rhs.y);
}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
Vec2 Vec2::operator / (const float val) const		
{
	return Vec2(this->x / val, this->y / val);
}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
Vec2 Vec2::operator * (const float val) const		
{
	return Vec2(this->x * val, this->y * val);
}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
double Vec2::length(const Vec2& rhs) const			
{
	Vec2 vec2_delta = *this - rhs;

	return sqrtf(pow(vec2_delta.x, 2) + pow(vec2_delta.y, 2));
}


/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	TODO
;
;FUNCTION:
;
;	This method is used to...TODO
;
;RETURN VALUE:
;	TODO
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	TODO
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	LOCAL SYMBOLS
;	-------------
;	TODO		- TODO
;
*/
void Vec2::normalize(const Vec2& rhs)// const			
{
	double length = this->length(rhs);
	this->x = (this->x - rhs.x) / length; 
	this->y = (this->y - rhs.y) / length;
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