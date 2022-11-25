// File:		Entity.h
// Name:		Emir Khanseitov
// Date:		17.11.2022
// Description: Implementation file for the class of the Entity. The Basic empty class with an id

#include "Entity.h"

namespace Bohemia_Test
{
	// Getters and Setters for the ID of the Entity

	void Entity::SetID(unsigned int id_new)
	{
		entity_id = id_new;
	}

	unsigned int Entity::GetID() const
	{
		return entity_id;
	}
}
