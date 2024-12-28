#pragma once
#include "raylib.h"
#include "rlgl.h"
#include "ecs_registry_sparse.h"
#include "ecs_components.h"

// Testing
#include <chrono>
#include <iostream>

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
	for (Entity e = 0; e < 10000; ++e) {
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

inline void MovementSystem_DirectIteration(Registry& registry, float dt) {
	// Direct access to arrays
	auto* posArray = registry.getComponentArray<Position>();
	auto* velArray = registry.getComponentArray<Velocity>();

	// If either is missing, nothing to update
	if (!posArray || !velArray) return;

	auto& posEntities   = posArray->getEntities();   // vector<Entity>
	auto& positions     = posArray->getComponents(); // vector<Position>
	
	auto& velEntities   = velArray->getEntities();   // vector<Entity>
	auto& velocities    = velArray->getComponents(); // vector<Velocity>

	// We need to handle "which array do we iterate?"
	// We'll pick the smaller array for efficiency:
	bool positionsIsSmaller = (posEntities.size() < velEntities.size());

	if (positionsIsSmaller) {
		// For each entity that has Position, see if it also has Velocity.
		for (size_t i = 0; i < posEntities.size(); i++) {
			Entity e = posEntities[i];
			if (velArray->contains(e)) {
				// pos is positions[i]
				Position& posRef = positions[i];

				// find velocity index
				uint32_t velIndex = velArray->getIndex(e);
				Velocity& velRef  = velocities[velIndex];

				posRef.x += velRef.dx * dt;
				posRef.y += velRef.dy * dt;
			}
		}
	} else {
		// For each entity that has Velocity, see if it also has Position
		for (size_t i = 0; i < velEntities.size(); i++) {
			Entity e = velEntities[i];
			if (posArray->contains(e)) {
				// vel is velocities[i]
				Velocity& velRef = velocities[i];

				uint32_t posIndex = posArray->getIndex(e);
				Position& posRef  = positions[posIndex];

				posRef.x += velRef.dx * dt;
				posRef.y += velRef.dy * dt;
			}
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

inline void RenderSystemRLGL(Registry& registry) {
	auto entities = registry.getEntityWith<Position>();
	
	Color color = RAYWHITE;
	Color* col = &color;

	// Start batch
	rlBegin(RL_QUADS);
	
	for (Entity entity : entities) {
		auto* pos = registry.getComponent<Position>(entity); // Measure this
		// Set the color for the current rectangle
		rlColor4ub(col->r, col->g, col->b, col->a);

		// Define the four corners of the rectangle
		rlVertex2f(pos->x, pos->y);             // Top-left
		rlVertex2f(pos->x, pos->y + 2);         // Bottom-left
		rlVertex2f(pos->x + 2, pos->y + 2);     // Bottom-right
		rlVertex2f(pos->x + 2, pos->y);         // Top-right
	}
	rlEnd();
}

// This works well if every entity with a position should be rendered 
inline void RenderSystemRLGL_DirectIteration(Registry& registry) {
	auto* posArray = registry.getComponentArray<Position>();
	if (!posArray) {
		return; // no Position array yet
	}

	const auto& entities   = posArray->getEntities();
	const auto& components = posArray->getComponents();

	Color color = RAYWHITE;
	rlBegin(RL_QUADS);

	// For every entity that actually has a Position...
	for (size_t i = 0; i < entities.size(); i++) {
		const auto& pos = components[i];  // direct reference to the Position struct
		rlColor4ub(color.r, color.g, color.b, color.a);

		rlVertex2f(pos.x,     pos.y);     // Top-left
		rlVertex2f(pos.x,     pos.y + 2); // Bottom-left
		rlVertex2f(pos.x + 2, pos.y + 2); // Bottom-right
		rlVertex2f(pos.x + 2, pos.y);     // Top-right
	}

	rlEnd();
}

// Tracks time

inline void RenderSystemRLGLtimed(Registry& registry) {
	// Measure time for `getEntityWith`
	auto start_get_entities = std::chrono::high_resolution_clock::now();

	auto entities = registry.getEntityWith<Position>();
	
	auto end_get_entities = std::chrono::high_resolution_clock::now();
	auto duration_get_entities = std::chrono::duration_cast<std::chrono::microseconds>(end_get_entities - start_get_entities).count();
	std::cout << "Time for getEntityWith: " << duration_get_entities << " microseconds" << std::endl;

	Color color = RAYWHITE;
	Color* col = &color;

	// Start batch
	rlBegin(RL_QUADS);

	// Measure time for iterating over entities and calling `getComponent`
	auto start_get_components = std::chrono::high_resolution_clock::now();
	
	for (Entity entity : entities) {
		auto* pos = registry.getComponent<Position>(entity); // Measure this
		// Set the color for the current rectangle
		rlColor4ub(col->r, col->g, col->b, col->a);

		// Define the four corners of the rectangle
		rlVertex2f(pos->x, pos->y);             // Top-left
		rlVertex2f(pos->x, pos->y + 2);         // Bottom-left
		rlVertex2f(pos->x + 2, pos->y + 2);     // Bottom-right
		rlVertex2f(pos->x + 2, pos->y);         // Top-right
	}
   
	auto end_get_components = std::chrono::high_resolution_clock::now();
	auto duration_get_components = std::chrono::duration_cast<std::chrono::microseconds>(end_get_components - start_get_components).count();
	std::cout << "Time for getComponent calls: " << duration_get_components << " microseconds" << std::endl;

	rlEnd();
}
