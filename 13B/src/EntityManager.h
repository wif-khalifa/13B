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

	std::vector<std::shared_ptr<Entity>>	m_entities;
	std::vector<std::shared_ptr<Entity>>	m_entitiesToAdd;
	
	std::map<std::string, EntityVec>		m_entityMap;

public:

	EntityManager();
	
	void init();
	void update();
	void removeDeadEntities(std::vector<std::shared_ptr<Entity>>& vec);

	std::shared_ptr<Entity> addEntity(const std::string& tag);
	
	const std::vector<std::shared_ptr<Entity>>& getEntities();
	const std::vector<std::shared_ptr<Entity>>& getEntities(const std::string& tag);
};