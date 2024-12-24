#pragma once
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