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
;	EntityManager::removeDeadEntities	- Check if Entity active, remove if false
;	EntityManager::addEntity			- Construct new Entity objects
;	EntityManager::getEntities			- Return all Entities in Entity vector
;	EntityManager::getEntities			- Return all Entities in vector with supplied ID
;
;PRIVATE DECLARATIONS:
;
;	PRIVATE SYMBOLS
;	---------------
;	m_totalEntities		- Running count of Entity objects
;	m_entities			- Main Entity object vector
;	m_entitiesToAdd		- Temporary vector for holding Entity objects until next frame
;	m_entityMap			- Map for holding Entity vectors organized by tag
;
;	PRIVATE SUB-PROGRAMS
;	--------------------
;	None
;
*/

#include "EntityManager.h"


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
;SUB-PROGRAM NAME:	EntityManager::removeDeadEntities
;
;FUNCTION:
;
;	This method is used to check the active flag for all Entity objects in the Entity vector, then
;	remove entities from vector if active flag is false.
;
;RETURN VALUE:
;	void
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	std::vector<std::shared_ptr<Entity>>&
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
;SUB-PROGRAM NAME:	EntityManager::addEntity
;
;FUNCTION:
;
;	This method is used to construct new Entity objects and add them to the temporary Entity holding 
;	vector.
;
;RETURN VALUE:
;	std::shared_ptr<Entity>
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	std::string&
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
;SUB-PROGRAM NAME:	EntityManager::getEntities
;
;FUNCTION:
;
;	This method is used to return all Entity objects in Entity vector.
;
;RETURN VALUE:
;	std::vector<std::shared_ptr<Entity>>&
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
const EntityVec& EntityManager::getEntities()
{
	return m_entities;
}


/*********************************************************************************************************
;**********								EntityManager::getEntities								**********
;*********************************************************************************************************
;
;SUB-PROGRAM NAME:	EntityManager::getEntities
;
;FUNCTION:
;
;	This method is used to return all Entitie objects with the specified tag from map.
;
;RETURN VALUE:
;	std::vector<std::shared_ptr<Entity>>&
;
;LOCAL DECLARATIONS:
;
;	FORMAL PARAMETERS
;	-----------------
;	std::string&
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
const std::vector<std::shared_ptr<Entity>>& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}