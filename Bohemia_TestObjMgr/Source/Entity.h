// File:		Entity.h
// Name:		Emir Khanseitov
// Date:		17.11.2022
// Description: Header file for the class of the Entity. The Basic empty class with an id

#pragma once

#ifndef ENTITY_H
#define ENTITY_H

// STL includes
#include "cstdint"

// Custom includes
#include "ObjectManager.h"

namespace Bohemia_Test
{
	class Entity
	{
	public:

		// Custom c-tor to give a custom number of maximum amount of components for the CompMgr
		Entity(std::uint32_t custom_max_comps_num);

		// Getters and Setters for the ID of the Entity
		void SetID(unsigned int id_new);
		unsigned int GetID() const;

	private:

		// Simple unsigned int, to be using it as an index to our arrays
		std::uint32_t entity_id;

		// ObjectManager class (TODO: needs to be pointer? Needs to be new * ? Needs to be smart pointer?
		ObjectManager Components_Mgr;
	};
}

#endif 