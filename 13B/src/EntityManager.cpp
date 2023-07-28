#include <memory>
#include "EntityManager.h"

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

	// TODO: Add newly spawned Entities to Entity map
	for (std::shared_ptr<Entity>& e : m_entitiesToAdd)
	{
		m_entityMap.insert({ e->m_tag, m_entities });
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

void EntityManager::removeDeadEntities(EntityVec& vec)
{
	// TODO: Remove all dead Entities from the input vector
	//		 this is called by the update() function

	for (auto e : vec)
	{
		if (!e->isActive())
		{
			// remove from vec, use std::remove_if from std C++ library
		}
	}
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