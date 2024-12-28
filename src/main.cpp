#include <memory>
#include <iostream>
#include <string>
#include "main_render.h"
#include "random.h"
#include "obj/obj_manager.h"
#include "obj/obj_game.h"

#include "ecs/ecs_registry_sparse.h"

int main() {
	ObjMan manager;		// All objects, e.g. Game, UI element, 
	Registry registry;	// All entities, e.g. Boid
	manager.addObject(std::make_unique<GameInstance>("MainGame")); // Main Game Instance (For now)
	GameInstance* mainGame = manager.getObjectByNameAs<GameInstance>("MainGame");

	mainGame->initialize(&registry);	

	auto frame = [&manager](){
		// handle input later
		float dt = GetFrameTime();
		manager.update(dt);
		manager.render();
	};

	beginRaylibEnv(frame);

	// Meows back to the computer
	return 0;
}