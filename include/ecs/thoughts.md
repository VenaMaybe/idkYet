> Entity

A lightweight ID
Doesn't store data or behavior

> Component

Plain old data
Holds data needed by a game part (transform, physics, ...)
An entity can have components

> System

Code that operates on a set of entities that have certain components

> Registry

A container that stores:
	The mapping from Entity -> Component for each component type
	The logic to create/destroy entities and attach/detach components

Note that this could be separated into EntityManager, ComponentManager, and SystemManger

> End

The idea of to separate data from logic