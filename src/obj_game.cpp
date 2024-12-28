#include "obj/obj_game.h"
#include "ecs/ecs_components.h"
#include "ecs/ecs_system.h"
#include "main_render.h"
#include "random.h"

void GameInstance::initialize(Registry* registry) {
	if (registry) { // if exists, set the registry
		this->registry = registry;
	}

	// Create the default lil guys
	initializeGameEntities(registry);
}

void GameInstance::update(float dt) {
	// MovementSystem(*registry, dt);
	MovementSystem_DirectIteration(*registry, dt);
}

void GameInstance::render() const {
	RenderSystemRLGL_DirectIteration(*registry);
	// RenderSystem(*registry);
}

void GameInstance::initializeGameEntities(Registry* r) {
	for (size_t i = 0; i < 100000; i++)	{
		Entity lilGuy = r->createEntity();
		float width = static_cast<float>(SCREEN_WIDTH);
		float height = static_cast<float>(SCREEN_HEIGHT);
		r->addComponent(lilGuy, Position{width/2, height/2});
		r->addComponent(lilGuy, Velocity{Random::getRandomFloat(-20.f, 20.f), Random::getRandomFloat(-20.f, 20.f)});
	}
}