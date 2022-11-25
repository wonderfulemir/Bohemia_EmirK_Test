// 19.11.2022

#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

// STL includes
#include <array>
#include <unordered_map>
#include <assert.h>

// Custom includes
#include "Entity.h"

namespace Bohemia_Test
{
	// Default parameter of the maximum amount of components
	const std::uint32_t DEFAULT_MAX_COMPONENTS = 6900;

	// An Interace class, from which any particular Component class is inheritable
	class IComponent
	{
	private:
		// A simple type alias
		using ComponentType = std::uint8_t;

		// Used to define the size of arrays later on
		const ComponentType MAX_COMPONENTS = 32;
	};


	// An Interface class, from which any component array is inheritable
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};


	// Templated class of Array of components that will try to maintain array density
	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:

		// Insert data at the end, and update the maps that point to places
		void InsertData(Entity entity, T component)
		{
			assert(mEntityToIndexMap.find(entity.GetID()) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

			size_t newIndex = mSize;
			mEntityToIndexMap[entity.GetID()] = newIndex;
			mIndexToEntityMap[newIndex] = entity.GetID();
			mComponentArray[newIndex] = component;
			++mSize;
		}

		// Take whatever was at the end and put the data into deleted entity place to keep density
		void RemoveData(Entity entity)
		{
			assert(mEntityToIndexMap.find(entity.GetID()) != mEntityToIndexMap.end() && "Removing non-existent component.");

			// Update the Entity at the end, and put it into same place where the removed entity was
			size_t indexOfRemovedEntity = mEntityToIndexMap[entity.GetID()];
			size_t indexOfLastElement = mSize - 1;
			mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

			// Update the maps to point to the newly placed spot
			Entity entityOfLastElement;
			entityOfLastElement.SetID(mIndexToEntityMap[indexOfLastElement]);
			mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			// Finally delete the last most element in the maps, and decrease the current size of the array
			mEntityToIndexMap.erase(entity.GetID());
			mIndexToEntityMap.erase(indexOfLastElement);

			--mSize;
		}

		// Grab the given Component's data
		T& GetData(Entity entity)
		{
			assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

			// Return a reference to the entity's component
			return mComponentArray[mEntityToIndexMap[entity]];
		}

		// Destroy entity if necessary from the component manager
		void EntityDestroyed(Entity entity) override
		{
			if (mEntityToIndexMap.find(entity.GetID()) != mEntityToIndexMap.end())
			{
				// Remove the entity's component if it existed
				RemoveData(entity);
			}
		}

	private:
		// The packed array of generic components, set to a specified maximum amount, 
		// matching the maximum number of entities with unique spots allowed to 
		// exist simultaneously.
		std::array<T, DEFAULT_MAX_COMPONENTS> mComponentArray;

		// Map from an entity ID to an array index.
		std::unordered_map<std::uint32_t, size_t> mEntityToIndexMap;

		// Map from an array index to an entity ID.
		std::unordered_map<size_t, std::uint32_t> mIndexToEntityMap;

		// Total size of valid entries in the array currently.
		size_t mSize;

	};
}

#endif