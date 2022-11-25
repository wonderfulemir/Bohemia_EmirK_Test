// File:		ObjectManager.h
// Name:		Emir Khanseitov
// Date:		17.11.2022
// Description: Header file for the class of the Object Manager. This object is owned by 
//				the Entity class, and manages its components.
// 
// NOTES:		I'm interested in having the components cached upon iteration, so we need 
//				to have an array that would be thoroughly packed. But management would 
//				be done using unordered maps


// 1. Implement a generic ObjectManager
// - it's owned by Entity. BOOM DONE.
// - it can contain many Object's. (Make an IComponentArray + ComponentArray template)
// - Object's can be instantiated by other components on same Entity (methods on the component itself, that allow to instantiate other Comps needed)
// - Object automatically registers itself with ObjectManager (DELETE DFLT C-TOR, MAKE CUSTOM ONE, THAT NEEDS AN ENTITY PASSED TO IT)
// - Object unregisters itself when removed or detached from hierarchy (MGR is the ONE to have a function to REMOVE a componet from itself)
// - manager can iterate through Object's and call custom functions in it (FRIEND CLASS TO ALL COMPONENTS! Custom Mgr is friend class only to it's own components)

// 2. Implement EntityAction and EntityActionManager
// - EntityAction inherits from Object (Custom Component of EntityAction)
// - EntityAction has virtual method CanBeVisible (One virtual method of CanBeVisible)
// - EntityActionManager inherits from ObjectManager (Custom mgr, that manages only PARTICULAR components. Doesn't care about Removal cause that's done by Parent mgr,
//													  this one just iterates upon the PARTICULAR comps needed)
// - EntityActionManager allows to get all the actions that are visible

#pragma once

#ifndef OBJMGR_H
#define OBJMGR_H



// STL Containers
#include <array>

// Custom includes
#include "Component.h"

namespace Bohemia_Test
{
	class ObjectManager
	{
	public:




	private:



		// Containers
		//std::array<Entity, CUSTOM_MAX_COMPONENTS> objs_arr;
	};
}

#endif