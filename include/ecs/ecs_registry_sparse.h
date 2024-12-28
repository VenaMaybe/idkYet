// ecs_component_array.h
#pragma once
#include "ecs_sparse_set.h"
#include <vector>
#include <cassert>
#include "ecs_types.h"

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <algorithm>

// Base class for polymorphism
class IComponentArray {
public:
	virtual ~IComponentArray() = default;
};

template <typename T>
class ComponentArray : public IComponentArray {
public:
	void insert(Entity entity, const T& component) {
		sparseSet.insert(entity);
		components.push_back(component);
	}

	void remove(Entity entity) {
		if (!sparseSet.contains(entity)) {
			return; // nothing to remove
		}

		// index of the entity to remove
		uint32_t index = sparseSet.getIndex(entity);
		uint32_t lastIndex = components.size() - 1;

		// If it's not the last element, swap
		if (index != lastIndex) {
			// Move the last element to the hole
			components[index] = components[lastIndex];

			// Also fix the sparseSet so that the entity that was in 'lastIndex'
			// now knows it is in 'index'
			Entity lastEntity = sparseSet.getDense()[lastIndex];
			sparseSet.remove(lastEntity); // sets lastEntity's sparse to INVALID
			sparseSet.sparse[lastEntity] = index;  // reassign index in the sparse array
			sparseSet.dense[index] = lastEntity;   // put lastEntity in the hole
		}

		// pop_back the last component
		components.pop_back();

		// finally remove the old entity from the sparseSet
		sparseSet.remove(entity);
	}


	T* get(Entity entity) {
		if (sparseSet.contains(entity)) {
			return &components[sparseSet.getIndex(entity)];
		}
		return nullptr;
	}

	bool contains(Entity entity) const {
		return sparseSet.contains(entity);
	}

	const std::vector<Entity>& getEntities() const {
		return sparseSet.getDense();
	}

	// Changing this to be non-const for MovementSystem

	// Expose components for direct access in rendering
	std::vector<T>& getComponents() {
		return components;
	}

	uint32_t getIndex(Entity e) {
		return sparseSet.getIndex(e);
	}

private:
	std::vector<T> components;
	SparseSet sparseSet;
};


class Registry {
public:
	// Entity management
	Entity createEntity() {
		return nextEntityId++;
	}

	void destroyEntity(Entity entity) {
		// Implement entity destruction logic if needed
	}

	// Component management
	template<typename T>
	void addComponent(Entity entity, const T& component) {
		getComponentArray<T>()->insert(entity, component);
	}

	template<typename T>
	void removeComponent(Entity entity) {
		getComponentArray<T>()->remove(entity);
	}

	template<typename T>
	T* getComponent(Entity entity) {
		return getComponentArray<T>()->get(entity);
	}

	template<typename T>
	bool hasComponent(Entity entity) const {
		auto it = componentArrays.find(typeid(T));
		if (it != componentArrays.end()) {
			ComponentArray<T>* compArray = static_cast<ComponentArray<T>*>(it->second.get());
			return compArray->contains(entity);
		}
		return false;
	}

 	template<typename T>
	ComponentArray<T>* getComponentArray() {
		std::type_index ti(typeid(T));
		if (componentArrays.find(ti) == componentArrays.end()) {
			componentArrays[ti] = std::make_unique<ComponentArray<T>>();
		}
		return static_cast<ComponentArray<T>*>(componentArrays[ti].get());
	}

	// Query entities with specific components
	template<typename... Components>
	std::vector<Entity> getEntityWith() {
		// Collect all component entity lists
		std::vector<const std::vector<Entity>*> componentEntities = { &getComponentArray<Components>()->getEntities()... };

		// Find the smallest component entity list
		auto minIt = std::min_element(componentEntities.begin(), componentEntities.end(),
			[](const std::vector<Entity>* a, const std::vector<Entity>* b) {
				return a->size() < b->size();
			});

		if (minIt == componentEntities.end() || (*minIt)->empty()) {
			return {};
		}

		const std::vector<Entity>* smallestSet = *minIt;
		std::vector<Entity> result;

		// Iterate over the smallest set and check for presence in other sets
		for (Entity entity : *smallestSet) {
			bool hasAll = true;
			// Expand the parameter pack to check all components
			(..., (hasAll = hasAll && hasComponent<Components>(entity)));
			if (hasAll) {
				result.push_back(entity);
			}
		}

		return result;
	}

private:
	Entity nextEntityId = 0;
	std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> componentArrays;
};