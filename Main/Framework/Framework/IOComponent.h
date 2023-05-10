#pragma once
#include "Commons.h"
#include "Component.h"
class IOComponent : public Component
{
public:
	IOComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::IO, myObject_, mySystem_) {};
	IOComponent(const IOComponent& other) : Component(other) {};

	IOComponent& operator=(const IOComponent& other);

	void Update();

private:
	/* This is where you stick data unique to the IO component! */
};