#pragma once
#include "Commons.h"

class Subsystem;
class EventQueue;
class GameObject;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	int Update();
	void Setup();

private:
	// probably should replace with arrays for more memmory control 
	std::vector<Subsystem*>* subsystems;
	std::vector<GameObject*>* gameObjects;
	EventQueue* eventQueue;
	bool inEditMode = false;
};

