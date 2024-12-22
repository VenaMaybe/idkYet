// ECS.h
#pragma once
#include <cstdint> 

// Type alias for entity handle/ID
using Entity = std::uint32_t;

// Maybe useful later?
const Entity MAX_ENTITIES = 5000;

// Forward declare the registry
class Registry;