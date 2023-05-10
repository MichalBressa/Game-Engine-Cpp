#pragma once
#include "Component.h"

class SoundComponent : public Component
{
public:
	inline SoundComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::Sound, myObject_, mySystem_) {};
	inline SoundComponent(const SoundComponent& other) : Component(other) {};

	//SoundComponent& operator=(const SoundComponent& other);

	void Update();

private:
	/* This is where you stick data unique to the physics component! */

};

