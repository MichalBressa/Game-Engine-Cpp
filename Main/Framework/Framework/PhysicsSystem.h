#pragma once
#include <Box2D/Box2D.h>
#include "Subsystem.h"
#include "Commons.h"
#include "PhysicsComponent.h"

class PhysicsSystem : public Subsystem
{
public:
	PhysicsSystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects) : Subsystem(SubsystemType::Physics, _eventQueue, _gameObjects) {
		components = new std::vector<PhysicsComponent>;
		components->reserve(MAX_ENTITIES);
		//gravity.Set(0.0f, -9.81f);
	};
	PhysicsSystem(const PhysicsSystem& other) : Subsystem(other)
	{ 
		components->reserve(MAX_ENTITIES);
	};

	~PhysicsSystem()
	{
		//delete gravity;
		//delete world;
	};

	Component* addComponent(Component* component_);
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* getComponent(int i_) { return &(components->at(i_)); }

	void Update();
	inline int getNumComponents() { return components->size(); }
	b2World* GetWorld();

private:
	// should change into array later on for faster elements deleting 
	std::vector<PhysicsComponent>* components;
};

