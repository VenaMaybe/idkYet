#include "obj/obj_game.h"
#include "ecs/ecs_components.h"
#include "ecs/ecs_system.h"
#include "random.h"

void GameInstance::initialize(Registry* registry) {
	if (registry) { // if exists, set the registry
		this->registry = registry;
	}

	// Create the default lil guys
	initializeGameEntities(registry);
}

void GameInstance::update(float dt) {
	MovementSystem(*registry, dt);
	// MovementSystemAll(*registry, dt);
}

void GameInstance::render() const {
	RenderSystem(*registry);
}

void GameInstance::initializeGameEntities(Registry* r) {
	for (size_t i = 0; i < 10000; i++)	{
		Entity lilGuy = r->createEntity();
		r->addComponent(lilGuy, Position{400.f, 225.f});
		r->addComponent(lilGuy, Velocity{Random::getRandomFloat(-20.f, 20.f), Random::getRandomFloat(-20.f, 20.f)});
	}
}