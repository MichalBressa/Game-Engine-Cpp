#include "GameEngine.h"

#include "GameObject.h"
#include "PhysicsSystem.h"
#include "IOSystem.h"
#include "AISystem.h"
#include "EventQueue.h"
#include "GraphicsSystem.h"
#include "FileSystem.h"
#include "NetworkSystem.h"

GraphicsSystem* graphicsSystem;
PhysicsSystem* physicsSystem;
FileSystem* fileSystem;

GameEngine::GameEngine()
{
	eventQueue = new EventQueue();
	gameObjects = new std::vector<GameObject*>;
	subsystems = new std::vector<Subsystem*>;

	physicsSystem = new PhysicsSystem(eventQueue, gameObjects);
	IOSystem* ioSystem = new IOSystem(eventQueue, gameObjects);
	AISystem* aiSystem = new AISystem(eventQueue, gameObjects);
	graphicsSystem = new GraphicsSystem(eventQueue, gameObjects);	// should be the last in order to render all changes after they happen
	NetworkSystem* netSystem = new NetworkSystem(eventQueue, gameObjects);

	fileSystem = &FileSystem::instance(eventQueue, gameObjects);

	/* Lastly, we push these subsystems (yay Polymorphism!) onto our vector of
	 * Subsystem pointers, so we can iterate through them in our Update() method.
	 * After that, we call our SetupDemo method, which will parameterise this
	 * demo code. */

	subsystems->push_back(physicsSystem);
	subsystems->push_back(ioSystem);
	subsystems->push_back(aiSystem);
	subsystems->push_back(graphicsSystem);
	subsystems->push_back(fileSystem);
	subsystems->push_back(netSystem);

	if (inEditMode)
	{
		// initialize additional subsystems like UI for creating game objects
		// push to subsystems vector
	}

	Setup();
}

GameEngine::~GameEngine()
{
	for (int i = 0; i < subsystems->size(); i++)
	{
		delete subsystems->at(i);
	}

	for (int i = 0; i < gameObjects->size(); i++)
	{
		delete gameObjects->at(i);
	}

	subsystems->clear();
	gameObjects->clear();

	delete subsystems;
	delete gameObjects;
	delete eventQueue;
}

int GameEngine::Update()
{
	int i, eQSize;
	//std::cout << subsystems->size() << std::endl;
	/*
	 * Each subsystem calls its own Update method (hence adhering to the core
	 * principles of ECS, despite their being sat on the heap).
	 */

	for (i = 0; i < subsystems->size(); i++)
	{
		//std::cout << i << std::endl;
		subsystems->at(i)->Update();
	}

	/*
	 * And lastly we check our event queue. We should be aware that other subsystems
	 * are checking the event queue too, every frame! But our 'GameEngine' class is
	 * checking it here to do some housekeeping.
	 *
	 * First, it checks to see if we've opted to exit the game - if we have, it returns
	 * 'false' to the running variable in our Main method, and deletes the Game Engine.
	 *
	 * Next, it checks to see if any events have outlived their usefulness. So, it looks
	 * to see if any subsystems are still to react to this event. If not, it deletes the
	 * event and clears it from the event queue's vector of events.
	 */

	eQSize = eventQueue->events.size();

	if (eQSize > 0)
	{
		for (i = 0; i < eQSize; i++)
		{
			if (eventQueue->events[i]->type == EventType::Exit)
			{
				return false;
			}

			if (eventQueue->events[i]->systems.size() == 0)
			{
				delete eventQueue->events[i];
				eventQueue->events.erase(eventQueue->events.begin() + i);
			}
		}
	}

	return true;
}

void GameEngine::Setup() 
{
	gameObjects->push_back(new GameObject("Player", b2Vec2(4, -4)));
	PhysicsComponent playerPhysics(gameObjects->back(), subsystems->at(0), physicsSystem->GetWorld(), b2_dynamicBody, 5.f, 1, 1);
	IOComponent playerIO(gameObjects->back(), subsystems->at(1));
	GraphicsComponent playerGraphics(gameObjects->back(), subsystems->at(2), graphicsSystem->GetRenderer());
	gameObjects->back()->addComponent(subsystems->at(0)->addComponent(&playerPhysics));
	gameObjects->back()->addComponent(subsystems->at(1)->addComponent(&playerIO));
	gameObjects->back()->addComponent(subsystems->at(3)->addComponent(&playerGraphics));


	gameObjects->push_back(new GameObject("Obj1", b2Vec2(10, -4)));
	PhysicsComponent objPhysics(gameObjects->back(), subsystems->at(0), physicsSystem->GetWorld(), b2_dynamicBody, 5.f, 1, 1);
	GraphicsComponent objGraphics(gameObjects->back(), subsystems->at(2), graphicsSystem->GetRenderer());
	gameObjects->back()->addComponent(subsystems->at(0)->addComponent(&objPhysics));
	gameObjects->back()->addComponent(subsystems->at(3)->addComponent(&objGraphics));


	// using JSON to create objects
	try {
		fileSystem->ReadFile("jsontest.json");
			// check if object has certain components with simple bool s 
			gameObjects->push_back(new GameObject(fileSystem->fileData["obj1"]["Name"].asString(), b2Vec2(fileSystem->fileData["obj1"]["X"].asFloat(), fileSystem->fileData["obj1"]["Y"].asFloat())));
			if (fileSystem->fileData["obj1"]["PhysicsComponent"].asInt() == 1)
			{
				if (fileSystem->fileData["obj1"]["Type"].asString() == "b2_dynamicBody")
				{
					PhysicsComponent objPhysics(gameObjects->back(), subsystems->at(0), physicsSystem->GetWorld(), b2_dynamicBody, 5.f, fileSystem->fileData["obj1"]["W"].asFloat(), fileSystem->fileData["obj1"]["H"].asFloat());
				}
				else if (fileSystem->fileData["obj1"]["Type"].asString() == "b2_kinematicBody")
				{
					PhysicsComponent objPhysics(gameObjects->back(), subsystems->at(0), physicsSystem->GetWorld(), b2_kinematicBody, 5.f, fileSystem->fileData["obj1"]["W"].asFloat(), fileSystem->fileData["obj1"]["H"].asFloat());
				}
				else if (fileSystem->fileData["obj1"]["Type"].asString() == "b2_staticBody")
				{
					PhysicsComponent objPhysics(gameObjects->back(), subsystems->at(0), physicsSystem->GetWorld(), b2_staticBody, 5.f, fileSystem->fileData["obj1"]["W"].asFloat(), fileSystem->fileData["obj1"]["H"].asFloat());
				}
			}
			if (fileSystem->fileData["obj1"]["GraphicsComponent"].asInt() == 1)
			{
				GraphicsComponent objGraphics(gameObjects->back(), subsystems->at(2), graphicsSystem->GetRenderer());
			}

		//throw 1; // Throw an exception when a problem arise
	}
	catch (...) {
		std::cout << "Reading JSON file error" << std::endl;
	}
	// ObjCount indicates how many objects are saved in the json file
	
	// from here JSON functionality should be easy to expand
}

//  I was trying to make the process of reading files easier for the user 
//	unfortunately I didn't make it work but an idea was as follows:  in Json file there would be object count that would determin how many 
//	objects will be there and so how many times does the loop must run
// 
//	Objects would be indexed by same name followed by the number so that e.g. obj1, obj2, obj3
//	that should allow me to do each name as char array and change number at the end to the same number as loop run
// 
//fileSystem->ReadFile("jsontest.json");
//
//for (int i = 0; i < fileSystem->fileData["ObjCount"].asInt(); i++)
//{
//	// check if object has certain components with simple bool s 
//	gameObjects->push_back(new GameObject(fileSystem->fileData[i]["Name"].asString(), b2Vec2(fileSystem->fileData[i]["X"].asFloat(), fileSystem->fileData[i]["Y"].asFloat())));
//	if (fileSystem->fileData["PhysicsComponent"].asInt() == 1)
//	{
//		if (fileSystem->fileData[i]["Type"].asString() == "b2_dynamicBody")
//		{
//			PhysicsComponent objPhysics(gameObjects->back(), subsystems->at(0), physicsSystem->GetWorld(), b2_dynamicBody, 5.f, fileSystem->fileData[i]["W"].asFloat(), fileSystem->fileData[i]["H"].asFloat());
//		}
//		else if (fileSystem->fileData[i]["Type"].asString() == "b2_kinematicBody")
//		{
//			PhysicsComponent objPhysics(gameObjects->back(), subsystems->at(0), physicsSystem->GetWorld(), b2_kinematicBody, 5.f, fileSystem->fileData[i]["W"].asFloat(), fileSystem->fileData[i]["H"].asFloat());
//		}
//		else if (fileSystem->fileData[i]["Type"].asString() == "b2_staticBody")
//		{
//			PhysicsComponent objPhysics(gameObjects->back(), subsystems->at(0), physicsSystem->GetWorld(), b2_staticBody, 5.f, fileSystem->fileData[i]["W"].asFloat(), fileSystem->fileData[i]["H"].asFloat());
//		}
//	}
//	if (fileSystem->fileData["GraphicsComponent"].asInt() == 1)
//	{
//		GraphicsComponent objGraphics(gameObjects->back(), subsystems->at(2), graphicsSystem->GetRenderer());
//	}
//}
