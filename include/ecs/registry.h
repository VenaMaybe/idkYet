#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "entity.h"

// This is a base class so we can store different ComponentArray<T> 
// in a single container while still being able to operate on them 
// generically through a pointer to the base class
class IComponentArray {
public:
	virtual ~IComponentArray() = default;
};

// The icy seed vaults
template <typename T>// Generic array for any type T of components
class ComponentArray : public IComponentArray {
public:
	// Insert a component for a given entity
	void insert(Entity entity, const T& component) {
		// Map the entity -> index in the components array
		//		at key[entity] : index where entity's component is stored
		entityToIndex[entity] = static_cast<std::uint32_t>(components.size());
		components.push_back(component);
	}
	// Remove a component for a given entity
	void remove(Entity entity) {
		auto it = entityToIndex.find(entity);
		if (it != entityToIndex.end()) {
			std::uint32_t indexOfRemoved = it->second;
			std::uint32_t indexOfLast = static_cast<std::uint32_t(components.size() - 1); // Get the last thing's index

			// Goal is to keep the array compact

			// Swap the last element into the removed element's place
			components[indexOfRemoved] = components[indexOfLast];
			components.pop_back();

			// Update the entityToIndex mapping for the entity that we swapped
			Entity entityOfLast = 0;
			for (auto& pair : entityToIndex) {
				if (pair.second == indexOfLast) {
					entityOfLast = pair.first;
					break;
				}
			}
			entityToIndex[entityOfLast] = indexOfRemoved; // at this key location, set the index

			// Erase the removed entity from the map
			entityToIndex.erase(it);
		}
	}
	// Return a pointer to the component for a given entity (or nullptr if missing)
	T* get(Entity entity) {
		auto it = entityToIndex.find(entity);
		if (it != entityToIndex.end()) {
			// if exists, find and grab component type deal
			return &components[it->second];
		}
		return nullptr;
	}
private:
	// Contiguous storage of the components
	std::vector<T> components;
	// Maps entity -> index in the components vector
	std::unordered_map<Entity, std::uint32_t> entityToIndex;
};

// The scroll and ledger
// Stores what entities have what components
class Registry {
public:
	// Creates an entity (just an integer)
	inline Entity createEntity() {
		return nextEntityId++;
	}
	// Destroys an entity, implement later
	inline void destroyEntity(Entity entity);

	// Add a component T to an entity
	template<typename T>
	void addComponent(Entity entity, const T& component) {
		getComponentArray<T>()->insert(entity, component);
	}
	// Remove a component T from an entity
	template<typename T>
	void removeComponent(Entity entity) {
		getComponentArray<T>()->remove(entity);
	}
	// Get a pointer to component T owned by an entity
	template<typename T>
	T* getComponent(Entity entity) {
		return getComponentArray<T>()->get(entity);
	}

private:
	Entity nextEntityId = 0; // Simple entity id system

	// std::type_index let's you use typeid() as a key

	// This is the core data structure: unordered_map<type_index, unique_ptr<IComponentArray>>

	// So for each type T, we have a unique_ptr<ComponentArray<T>> stored under
	//   key = typeid(T)

	// This is how we store an unknown number of different component types at runtime.
	std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> componentArrays;

	// If the ComponentArray for type T doesn't exist, create it. Else: return existing.
	template<typename T>
	ComponentArray<T>* getComponentArray() {
		std::type_index ti(typeid(T));

		// If we haven't allocated an array for T yet, create one
		if (componentArrays.find(ti) == componentArrays.end()) {
			componentArrays[ti] = std::make_unique<ComponentArray<T>>();
		}
		
		// Downcast and return raw pointer
		return static_cast<ComponentArray<T>*>(componentArrays[ti].get());
	}
};

/* Notes */
// Don't use inline for template functions or methods inside a template class since they are implicitly treated as inline