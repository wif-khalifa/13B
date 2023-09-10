/*********************************************************************************************************
;**********								13B Entity Manager Interface							**********
;*********************************************************************************************************
;
;PACKAGE NAME:	EntityManager.h - 13B Entity Manager Interface
;
;FUNCTION:
;
;	This unit contains the declarations required to create the 13B Entity Manager object.
;
;PUBLIC DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	EntityManager - 13B Entity Manager class
;
;	PUBLIC SYMBOLS
;	--------------
;	None
;
;	PUBLIC SUB-PROGRAMS
;	------------------
;	EntityManager::EntityManager		- Default Constructor
;	EntityManager::init					- Initializes Entity Manager
;	EntityManager::update				- Updates all Entity map and vectors each frame
;	EntityManager::removeDeadEntities	- Removes dead Entities from map and vectors each frame
;	EntityManager::addEntity			- Adds newly spawned Entities to map and vectors
;	EntityManager::getEntities			- Returns all Entities in Entity vector
;	EntityManager::getEntities			- Returns vector with specified tag from Entity map
;
;PRIVATE DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	None
;
;	PRIVATE SYMBOLS
;	---------------
;	m_totalEntities		- Integer holding running count of Entity instances
;	m_entities			- Vector of pointers to all Entity instances
;	m_entitiesToAdd		- Vector for holding new Entities until next frame
;	m_entityMap			- Hash map for holding Entity vectors based on Entity type
;
;	PRIVATE SUB-PROGRAMS
;	--------------------
;	None
;
*/

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "Entity.h"

typedef std::vector	<std::shared_ptr<Entity>>	EntityVec;
typedef std::map	<std::string, EntityVec>	EntityMap;

class EntityManager
{
private:

	int m_totalEntities;

	std::vector	<std::shared_ptr<Entity>>	m_entities;
	std::vector	<std::shared_ptr<Entity>>	m_entitiesToAdd;
	std::map	<std::string, EntityVec>	m_entityMap;

public:

	EntityManager();
	
	void update();
	void removeDeadEntities(std::vector<std::shared_ptr<Entity>>& vec);

	std::shared_ptr<Entity> addEntity(const std::string& tag);
	
	const std::vector<std::shared_ptr<Entity>>& getEntities();
	const std::vector<std::shared_ptr<Entity>>& getEntities(const std::string& tag);
};