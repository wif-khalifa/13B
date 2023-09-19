/*********************************************************************************************************
;**********								13B Entity Manager Implementation						**********	
;*********************************************************************************************************
;
;PACKAGE NAME:	EntityManager.cpp - 13B Entity Manager Implementation
;
;FUNCTION:
;
;	This unit contains the source code designed to create the 13B Entity Manager object.
;
;PUBLIC DECLARATIONS:
;	
;	PUBLIC SYMBOLS
;	--------------
;	None
;
;	PUBLIC SUB-PROGRAMS
;	------------------
;	EntityManager::EntityManager		- Default Constructor
;	EntityManager::update				- Adds/removes Entity objects from vectors/map
;	EntityManager::removeDeadEntities	- TODO
;	EntityManager::addEntity			- TODO
;	EntityManager::getEntities			- TODO
;	EntityManager::getEntities			- TODO
;
;PRIVATE DECLARATIONS:
;
;	PRIVATE SYMBOLS
;	---------------
;	m_totalEntities		- TODO
;	m_entities			- TODO
;	m_entitiesToAdd		- TODO
;	m_playerMapVec		- TODO
;	m_enemyMapVec		- TODO
;	m_bulletMapVec		- TODO
;	m_entityMap			- TODO
;
;	PRIVATE SUB-PROGRAMS
;	--------------------
;	None
;
*/

#include "EntityManager.h"
#include <iostream>	// For testing, delete later


/*********************************************************************************************************
;**********									EntityManager::EntityManager						**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	EntityManager::EntityManager - Default Constructor
;									
;FUNCTION:
;
;	This method is used to create the EntityManager object. All private attributes are defaulted.
;
;RETURN VALUE:
;	void
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	None
;
;	USER DEFINED TYPES
;	------------------
;	None
;
;	LOCAL SYMBOLS
;	-------------
;	None
*/
EntityManager::EntityManager()
	: m_totalEntities(0) {}


/*********************************************************************************************************
;**********									EntityManager::update								**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	EntityManager::update
;
;FUNCTION:
;
;	This method is used to add newly spawned Entity objects from vectors/map, as well as removing dead 
;	Entity objects from vectors/map. This method also clears vector for temporarily holding newly spawned
;	Entity objects each frame.
;
;RETURN VALUE:
;	void
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	None
;
;	USER DEFINED TYPES
;	------------------
;	None
;
;	LOCAL SYMBOLS
;	-------------
;	None
;	
*/
void EntityManager::update()
{
	// Add newly spawned Entities to Entity vector
	for (std::shared_ptr<Entity>& e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
	}

	// Add newly spawned Entities to Entity map
	for (std::shared_ptr<Entity>& e : m_entitiesToAdd)
	{
		m_entityMap[e->m_tag].push_back(e);
	}

	// Clear pending Entities vector for next frame
	m_entitiesToAdd.clear();

	// Remove dead Entities from the vector of all Entities
	removeDeadEntities(m_entities);

	// Remove dead Entities from each vector in the Entity map
	// C++17 way of iterating through [key,value] pairs in a map
	for (auto& [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}

}


/*********************************************************************************************************
;**********							EntityManager::removeDeadEntities							**********
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
void EntityManager::removeDeadEntities(std::vector<std::shared_ptr<Entity>>& vec)
{
	vec.erase(std::remove_if(vec.begin(),
							 vec.end(),
							 [&](std::shared_ptr<Entity>& e)
								{ return !e->isActive(); }),
							 vec.end());										
}


/*********************************************************************************************************
;**********								EntityManager::addEntity								**********
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
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(entity);

	return entity;
}


/*********************************************************************************************************
;**********								EntityManager::getEntities								**********
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
const EntityVec& EntityManager::getEntities()
{
	return m_entities;
}


/*********************************************************************************************************
;**********								EntityManager::getEntities								**********
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
const std::vector<std::shared_ptr<Entity>>& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}