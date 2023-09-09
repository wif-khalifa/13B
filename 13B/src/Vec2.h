/**********************************************************************************************************
;**********
;**********************************************************************************************************
;
;PACKAGE NAME:	TODO
;
;FUNCTION:
;
;	This unit contains the definitions required to create the...TODO
;
;
;PUBLIC DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	TODO
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
;	USER DEFINED TYPES
;	------------------
;	TODO
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

#pragma once

class Vec2
{
public:

	float x = 0;
	float y = 0;

	Vec2();
	Vec2(float xin, float yin);

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator / (const float val) const;
	Vec2 operator * (const float val) const;

	double length(const Vec2& rhs) const;	
	
	void normalize(const Vec2& rhs);
};