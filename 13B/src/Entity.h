/*********************************************************************************************************
;**********								13B Entity Manager Interface
;*********************************************************************************************************
;
;PACKAGE NAME:	Entity.h - 13B Entity Interface
;
;FUNCTION:
;
;	This unit contains the declarations required to create the 13B Entity object.
;
;
;PUBLIC DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	Entity - 13B Entity class
;
;	PUBLIC SYMBOLS
;	--------------
;	Entity::cTransform - Transform component to be attached to Entity
;	Entity::cShape	   - Shape component for attachment to Entity
;	Entity::cCollision - Collision component for attachment to Entity
;	Entity::cInput	   - Input component for attachment to Entity
;	Entity::cScore	   - Score component for attachment to Entity
;	Entity::cLifespan  - Lifespan component for attachment to Entity
;
;	PUBLIC SUB-PROGRAMS
;	------------------
;	Entity::isActive - Return boolean indicating whether Entity is active		
;	Entity::tag		 - Return string used for identifying Entity type
;	Entity::id		 - Return size_t used for numerical identification of Entity
;	Entity::destroy	 - Set Entity active flag to false
;
;PRIVATE DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	TODO
;
;	PRIVATE SYMBOLS
;	---------------
;	m_active - Boolean indicating whether Entity is active
;	m_tag	 - String used for identifying Entity type
;	m_id	 - size_t used for numerical identification of Entity
;
;	PRIVATE SUB-PROGRAMS
;	--------------------
;	Entity::Entity - Constructor
;
*/

#pragma once

#include <memory>
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