#include "obj/obj_game.h"

void GameInstance::initialize(Registry* registry) {
	if (registry) { // if exists, set the registry
		this->registry = registry;
	}
}

void GameInstance::update(float dt) {
}

void GameInstance::render() const {
}