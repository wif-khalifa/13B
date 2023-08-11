/**********************************************************************************************************
;**********								13B Entity Manager Implementation						 **********	
;**********************************************************************************************************
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
;	EntityManager::init					- TODO
;	EntityManager::update				- TODO
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


/**********************************************************************************************************
;**********
;**********************************************************************************************************
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
;	exampleVar1		- Var that does blah
;	exampleVar2		- Var that does blah
*/
EntityManager::EntityManager()
	: m_totalEntities(0) {}


/**********************************************************************************************************
;**********					
;**********************************************************************************************************
;
;SUB-PROGRAM NAME:	EntityManager::init - Initialize EntityManager object
;
;FUNCTION:
;
;	This method is used to initialize the EntityManager object
;
;RETURN VALUE:
;	void.
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
;	exampleVar1		- Var that does blah
;	exampleVar2		- Var that does blah
*/
void init()
{
	// TODO
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
		//m_entityMap.insert({ e->m_tag, m_entities });
		if (e->m_tag == "player")
		{
			m_entityMap[e->m_tag].push_back(e);
		}
		else if (e->m_tag == "enemy")
		{
			m_entityMap[e->m_tag].push_back(e);
		}
		else if (e->m_tag == "bullet")
		{
			m_entityMap[e->m_tag].push_back(e);
		}
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
void EntityManager::removeDeadEntities(std::vector<std::shared_ptr<Entity>>& vec)
{
	// Remove all dead Entities from the Entity vector and Entity map
	m_entities.erase(std::remove_if(m_entities.begin(), 
									m_entities.end(), 
									[&](std::shared_ptr<Entity>& e) 
										{ return !e->isActive(); }), 
									m_entities.end());

	m_playerMapVec.erase(std::remove_if(m_playerMapVec.begin(),
										m_playerMapVec.end(),
										[&](std::shared_ptr<Entity>& e)
											{ return !e->isActive(); }),			
										m_playerMapVec.end());

	m_enemyMapVec.erase(std::remove_if(m_enemyMapVec.begin(),
									   m_enemyMapVec.end(),
									   [&](std::shared_ptr<Entity>& e)
											{ return !e->isActive(); }),
									   m_enemyMapVec.end());

	m_bulletMapVec.erase(std::remove_if(m_bulletMapVec.begin(),
										m_bulletMapVec.end(),
										[&](std::shared_ptr<Entity>& e)
											{ return !e->isActive(); }),
										m_bulletMapVec.end());
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
std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(entity);

	return entity;
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
const EntityVec& EntityManager::getEntities()
{
	return m_entities;
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
const std::vector<std::shared_ptr<Entity>>& EntityManager::getEntities(const std::string& tag)
{
	// TODO: This is incorrect, return the correct vector from the map,
	// code updated from original, this may be all that's needed, need
	// to confirm
	return m_entityMap[tag];
}