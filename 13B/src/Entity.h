#pragma once

#include <memory>
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

#include <string>
#include "Components.h"

class Entity
{
private:

	// Make EntityManager friend class to enable it to construct Entity objects
	friend class EntityManager;

	bool		m_active	= true;
	std::string	m_tag		= "default";
	size_t		m_id		= 0;

	// Constructor
	Entity(const size_t id, const std::string& tag);

public:

	// Component Pointers, each Entity object will store at most one of these components,
	// by default all components are set to null, if needed for Entity type then it will
	// be initialized
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape>		cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput>		cInput;
	std::shared_ptr<CScore>		cScore;
	std::shared_ptr<CLifespan>	cLifespan;

	// Private member access functions
	bool	isActive()			const;
	const	std::string& tag()	const;
	const	size_t id()			const;
	void	destroy();
};