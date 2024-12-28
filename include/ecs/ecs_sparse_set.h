#include <vector>
#include <cassert>

#include "ecs_types.h"

class SparseSet {
public:
	//
	explicit SparseSet(size_t max_entities = 1000)
		: sparse(max_entities, INVALID_INDEX), dense() {} // vec(size, initalized_to)

	// Insert an entity into the set
	void insert(Entity entity) {
		ensureCapacity(entity);

		assert(sparse[entity] == INVALID_INDEX && "Entity already exists!");

		sparse[entity] = dense.size();
		dense.push_back(entity);
	}

	// Remove an entity from the set
	void remove(Entity entityToDelete) {
		assert(entityToDelete < sparse.size() && "Entity out of bounds!");
		assert(sparse[entityToDelete] != INVALID_INDEX && "Entity does not exist!");

		uint32_t index = sparse[entityToDelete]; // Get index of entity to delete
		Entity lastEntity = dense.back(); // get last entity

		dense[index] = lastEntity; // set deleted entity to lastEntity
		sparse[lastEntity] = index; // set 

		dense.pop_back();
		sparse[entityToDelete] = INVALID_INDEX;
	}

	// Check if an entity is in the set
	bool contains(Entity entity) const {
		return entity < sparse.size() && sparse[entity] != INVALID_INDEX;
	}

	// Get the index of an entity in the dense array
	uint32_t getIndex(Entity entity) const {
		assert(contains(entity) && "Entity does not exist!");
		return sparse[entity];
	}

	// Get the dense array
	const std::vector<Entity>& getDense() const {
		return dense;
	}

private:
	// max value of uint32_t to indicate an invalid index
	static constexpr uint32_t INVALID_INDEX = static_cast<uint32_t>(-1); // Sets to max value via two's complement

	// Sprace and dense arrays
	std::vector<uint32_t> sparse; // maps entity to index 	(stores indicies)
	std::vector<Entity> dense; // maps index to entity 		(stores entities)

	// Ensure the sparse array can hold the entity
	void ensureCapacity(Entity entity) {
		if (entity >= sparse.size()) {
			sparse.resize(entity + 1, INVALID_INDEX);
		}
	}
};