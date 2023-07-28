#include "Entity.h"

Entity::Entity(const size_t id, const std::string& tag)
	: m_id(id), m_tag(tag) {}

bool Entity::isActive() const
{
	// TODO
	return 0;
}

const std::string& Entity::tag() const
{
	// TODO
	return "tag";
}

const size_t Entity::id() const
{
	// TODO
	return 0;
}

void Entity::destroy()
{
	// TODO
}