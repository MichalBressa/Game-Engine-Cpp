#pragma once
#include "Commons.h"

class GameObject;
class Subsystem;

class Component
{
public:
	inline Component(ComponentType type_, GameObject* myObject_, Subsystem* mySystem_) : type(type_), myObject(myObject_), mySystem(mySystem_) {};
	inline Component(const Component& other) : type(other.type), myObject(other.myObject), mySystem(other.mySystem) {};

	inline const ComponentType getType() { return type; }
	inline GameObject* getMyObject() { return myObject; }
	inline Subsystem* getMySystem() { return mySystem; }

	virtual void Update() = 0;

protected:
	const ComponentType type;
	GameObject* myObject;
	Subsystem* mySystem;

};

