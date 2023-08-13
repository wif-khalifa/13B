/*********************************************************************************************************
;**********								13B Entity Implementation								**********										 
;*********************************************************************************************************
;
;PACKAGE NAME:	TODO - TODO
;
;FUNCTION:
;
;	This unit contains the source code designed to create the...TODO
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
;	TODO		- TODO
;
;	PRIVATE SUB-PROGRAMS
;	--------------------
;	TODO
;
*/

#include "Entity.h"


/*********************************************************************************************************
;**********										Entity::Entity									**********
;*********************************************************************************************************
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
Entity::Entity(const size_t id, const std::string& tag)
	: m_id(id), m_tag(tag) {}


/*********************************************************************************************************
;**********									Entity::isActive									**********
;*********************************************************************************************************
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
bool Entity::isActive() const
{
	return this->m_active;
}


/*********************************************************************************************************
;**********										Entity::tag										**********
;*********************************************************************************************************
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
const std::string& Entity::tag() const
{
	return this->m_tag;
}


/*********************************************************************************************************
;**********										Entity::id										**********
;*********************************************************************************************************
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
const size_t Entity::id() const
{
	return this->m_id;
}


/*********************************************************************************************************
;**********									Entity::destroy										**********
;*********************************************************************************************************
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
void Entity::destroy()
{
	this->m_active = false;
}