#pragma once
#include "Commons.h"

class EventQueue;
class GameObject;
class Component;

class Subsystem
{
	// each subsystem will have its own event queue

public:
	Subsystem(SubsystemType _type, EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects) : type(_type), eventQueue(_eventQueue), gameObjects(_gameObjects) {};
	Subsystem(const Subsystem& other) : type(other.type), eventQueue(other.eventQueue), gameObjects(other.gameObjects) {};

	// inline makes these instructions accessible faster as they will be stored in the cache single line
	inline SubsystemType getType() { return type; }
	inline EventQueue* getEventQueue() { return eventQueue; }
	inline std::vector<GameObject*>* getGameObjects() { return gameObjects; }

	virtual void Update() = 0;
	virtual Component* addComponent(Component* component_) = 0;
	virtual int getNumComponents() = 0;
	//virtual void SetPlayerObject(GameObject* player) {};

protected:
	const SubsystemType type;
	EventQueue* eventQueue;
	std::vector<GameObject*>* gameObjects;

};

