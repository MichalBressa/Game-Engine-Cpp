#pragma once
#include "Commons.h"
#include "Subsystem.h"
#include "IOComponent.h"

class IOSystem : public Subsystem
{
public:
	IOSystem(EventQueue* eQ_, std::vector<GameObject*>* gameObjects_) : Subsystem(SubsystemType::IO, eQ_, gameObjects_) {
		components = new std::vector<IOComponent>;
		components->reserve(MAX_ENTITIES);
	};
	IOSystem(const IOSystem& other) : Subsystem(other) { components->reserve(MAX_ENTITIES); };

	Component* addComponent(Component* component_);
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* getComponent(int i_) { return &(components->at(i_)); }

	void Update();
	inline int getNumComponents() { return components->size(); }


private:
	std::vector<IOComponent>* components;
};
