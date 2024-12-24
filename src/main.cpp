#include <memory>
#include <iostream>
#include <string>
#include "main_render.h"
#include "random.h"
#include "obj/obj_manager.h"
#include "obj/obj_game.h"

#include "ecs/ecs_registry.h"

int main() {
	ObjMan manager;		// All objects, e.g. Game, UI element, 
	Registry registry;	// All entities, e.g. Boid
	manager.addObject(std::make_unique<GameInstance>("MainGame")); // Main Game Instance (For now)
	GameInstance* mainGame = manager.getObjectByNameAs<GameInstance>("MainGame");


	


	auto frame = [&manager](){
		// handle input later
		float dt = GetFrameTime();
		manager.update(dt);
		manager.render();
	};


	beginRaylibEnv(frame);










	// // Create some entities
	// Entity e1 = registry.createEntity();
	// Entity e2 = registry.createEntity();

	// // Add components to the first entity
	// registry.addComponent<ecsTransform>(e1, ecsTransform{0.0f, 0.0f});
	// registry.addComponent<ecsVelocity>(e1, ecsVelocity{1.0f, 0.5f});

	// // Add components to the second entity
	// registry.addComponent<ecsTransform>(e2, ecsTransform{10.0f, 10.0f});
	// registry.addComponent<ecsVelocity>(e2, ecsVelocity{-1.0f, -0.2f});

	// // Create a system
	// MovementSystem movementSystem;

	// // In a real game loop, you'd do something like:
	// float deltaTime = 1.0f; // pretend 1 second per frame for this example
	// movementSystem.update(registry, deltaTime);






	// Meows back to the computer
	return 0;
}