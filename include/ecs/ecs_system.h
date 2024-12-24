#pragma once
#include "raylib.h"
#include "ecs_registry.h"
#include "ecs_components.h"


inline void MovementSystem(Registry& registry, float dt) {
	auto entities = registry.getEntityWith<Position, Velocity>();
	for (Entity entity : entities) {
		auto* pos = registry.getComponent<Position>(entity);
		auto* vel = registry.getComponent<Velocity>(entity);

		pos->x += vel->dx * dt;
		pos->y += vel->dy * dt;
	}
}

void MovementSystemAll(Registry& registry, float dt) {
	// For simplicity, assume entity IDs range from [0..nextEntityId).
	// A real ECS might store a container of "active" entities.
	for (Entity e = 0; e < 5000; ++e) {
		// Attempt to fetch the needed components for movement
		auto* pos = registry.getComponent<Position>(e);
		auto* vel = registry.getComponent<Velocity>(e);

		
		// If both exist, update transform by velocity
		if (pos && vel) {
			pos->x += vel->dx * dt;
			pos->y += vel->dy * dt;
		}
	}
}


inline void RenderSystem(Registry& registry) {
//	DrawCircle(10, 10, 10, RAYWHITE);
 	auto entities = registry.getEntityWith<Position>();
	for (Entity entity : entities) {
		auto* pos = registry.getComponent<Position>(entity);
		DrawRectangle(pos->x, pos->y, 2, 2, RAYWHITE);
	}
}

inline void RenderSystemAll(Registry& registry) {
//	DrawCircle(10, 10, 10, RAYWHITE);
	for (Entity e = 0; e < 5000; ++e) {
		// Attempt to fetch the needed components for movement
		auto* pos = registry.getComponent<Position>(e);
		DrawCircle(pos->x, pos->y, 2, RAYWHITE);
	}
}