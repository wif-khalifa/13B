#include "EntityManager.h"
#include <iostream>	// For testing, delete later

EntityManager::EntityManager()
	: m_totalEntities(0) {}


void init()
{
	// TODO
}


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


// TODO: Implement this function using std::remove_if OR std::remove if possible
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



std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	std::shared_ptr<Entity> entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(entity);

	return entity;
}


const EntityVec& EntityManager::getEntities()
{
	return m_entities;
}


const std::vector<std::shared_ptr<Entity>>& EntityManager::getEntities(const std::string& tag)
{
	// TODO: This is incorrect, return the correct vector from the map,
	// code updated from original, this may be all that's needed, need
	// to confirm
	return m_entityMap[tag];
}