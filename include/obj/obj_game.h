#pragma once

#include "obj/object.h"
#include "ecs/ecs_registry.h"

// An instance of the loaded game
class GameInstance : public Object{
public:
	explicit GameInstance(std::string name = "GameInstance")
		: Object(name) {}

	// Set the registry
	void initialize(Registry* registry);
	void run();
	void shutdown();

private:
	// Could create a player in here
	void initializeGameEntities(Registry* registry);

	void handleInput();
	void update(float dt) override;
	void render() const override;
	void cleanupEntities();

	Registry* registry;
};