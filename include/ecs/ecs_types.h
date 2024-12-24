// ECS.h
#pragma once
#include <cstdint> 

// Type alias for entity handle/ID
using Entity = std::uint32_t;

// Maybe useful later?
const Entity MAX_ENTITIES = 5000;

// Forward declare the registry
class Registry;

/*

modify to use 
using ComponentType = std::type_index;
using ComponentID = std::uint32_t;

constexpr Entity INVALID_ENTITY = 0;

and other Aliases later!!


*/