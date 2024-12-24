#pragma once

#include "ecs_registry.h"
#include "ecs_types.h"
#include "example_components.h" // For Transform, Velocity
#include <iostream>

class MovementSystem {
public:
	void update(Registry& registry, float dt) {
		// For simplicity, assume entity IDs range from [0..nextEntityId).
		// A real ECS might store a container of "active" entities.
		for (Entity e = 0; e < 1000; ++e) {
			// Attempt to fetch the needed components for movement
			ecsTransform* transform = registry.getComponent<ecsTransform>(e);
			ecsVelocity* velocity = registry.getComponent<ecsVelocity>(e);
			
			// If both exist, update transform by velocity
			if (transform && velocity) {
				transform->x += velocity->vx * dt;
				transform->y += velocity->vy * dt;
				std::cout << "Entity " << e 
					<< " moved to (" << transform->x 
					<< ", " << transform->y << ")"
					<< std::endl;
			}
		}
	}
};
