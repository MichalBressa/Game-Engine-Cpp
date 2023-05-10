#pragma once

#include "GameObject.h"
#include "Component.h"

//struct ComponentsIndexes
//{
//	int physics = NULL;
//	int graphics = NULL;
//	int ai = NULL;
//	int io = NULL;
//};
/*
 * We've got several constructors here - this is basically to make our code more
 * versatile in how we create or copy GameObjects.
 */

GameObject::GameObject()
{
	name = new std::string("Object " + objectCount);
	objectID = objectCount;
	objectCount++;
	position.Set(0, 0);
}

GameObject::GameObject(std::string name_, b2Vec2 position_)
{
	name = new std::string();
	objectID = objectCount;
	*name = name_;
	objectCount++;
	position = position_;
}

GameObject::GameObject(std::string name_)
{
	name = new std::string();
	objectID = objectCount;
	*name = name_;
	position.Set(0, 0);
	objectCount++;
}

GameObject::GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_)
{
	objectID = objectCount;
	*name = name_;
	components = components_;
	position.Set(0, 0);
	objectCount++;
}

GameObject::GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_, b2Vec2 position_)
{
	objectID = objectCount;
	*name = name_;
	components = components_;
	position = position_;
	objectCount++;
}

GameObject::GameObject(const GameObject& other) : objectID(other.objectID), name(other.name), components(other.components) {};

GameObject::~GameObject()
{
	delete name;
}

GameObject& GameObject::operator=(const GameObject& other)
{
	if (this == &other)
		return *this;

	GameObject a(other);
	return a;
}

/*
 * addCOmponent is a short but crucial function. We take in a pointer to a
 * Component, check the component's type, and insert a pair (a connection
 * between that type and that specific pointer) onto our components map.
 */

void GameObject::addComponent(Component* component_)
{
	components.insert({ component_->getType(), component_ });
}

/*
 * Another short function, but one with some Here Be Dragn's warnings. You'll
 * see here I'm using the 'auto' keyword. This, basically, makes the compiler
 * work out what return type I expect from a given function. It can be very
 * useful, but depending on how many levels of abstraction you have, you might
 * find that auto can't work out (or works out wrongly) what you think you want.
 *
 * Here, we can pass in a ComponentType - say, ComponentType::Physics, and
 * return the pointer to that component - very useful when it comes to processing
 * events.
 *
 * Speaking of Components, let's pop along to Component.h to see how we're
 * structuring these.
 */

Component* GameObject::getComponent(ComponentType type_)
{
	auto it = components.find(type_);
	return it->second;
}

int GameObject::objectCount = 0;
