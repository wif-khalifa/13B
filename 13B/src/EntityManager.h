/*********************************************************************************************************
;**********								13B Entity Manager Interface							**********
;*********************************************************************************************************
;
;PACKAGE NAME:	EntityManager.h - 13B Entity Manager Interface
;
;FUNCTION:
;
;	This unit contains the definitions required to create the 13B Entity Manager object.
;
;PUBLIC DECLARATIONS:
;
;	USER DEFINED TYPES
;	------------------
;	EntityManager	- 13B Entity Manager class
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
;	USER DEFINED TYPES
;	------------------
;	None
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
	
	void init();
	void update();
	void removeDeadEntities(std::vector<std::shared_ptr<Entity>>& vec);

	std::shared_ptr<Entity> addEntity(const std::string& tag);
	
	const std::vector<std::shared_ptr<Entity>>& getEntities();
	const std::vector<std::shared_ptr<Entity>>& getEntities(const std::string& tag);
};