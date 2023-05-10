#pragma once
#include "Commons.h"
#include "Subsystem.h"
#include "AIComponent.h"
class AISystem : public Subsystem
{
public:
	AISystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::AI, eQ_, gameObjects_) {
		components = new std::vector<AIComponent>;
		components->reserve(MAX_ENTITIES);
	};
	AISystem(const AISystem& other) : Subsystem(other) { components->reserve(MAX_ENTITIES); };

	Component* addComponent(Component* component_);
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* getComponent(int i_) { return &(components->at(i_)); }

	void Update();
	inline int getNumComponents() { return components->size(); }
private:
	std::vector<AIComponent>* components;
};

