#pragma once
#include "EventQueue.h"
#include "GameObject.h"
#include "AIComponent.h"
#include "PhysicsComponent.h"

Component* ptr;
PhysicsComponent* tempPhysics;

void MoveRight(Event* event_)
{
	//std::cout << "A move right! It was applied to entity \"" << std::endl;//event_->objects[0]->getName() << "\"" << std::endl;
	ptr = event_->objects[0]->getComponent(ComponentType::Physics);
	tempPhysics = static_cast<PhysicsComponent*>(ptr);

	tempPhysics->AddToDirection(b2Vec2(2, 0));

	//tempPhysics->SetVelocity(5, 0);
}

void MoveRightEND(Event* event_) 
{
	//std::cout << "A move right Ended! It was applied to entity \"" << std::endl;  //event_->objects[0]->getName() << "\"" << std::endl;
	ptr = event_->objects[0]->getComponent(ComponentType::Physics);
	tempPhysics = static_cast<PhysicsComponent*>(ptr);
	
	//tempPhysics->AddToDirection(b2Vec2(-2, 0));
	tempPhysics->SetDirectionToZero();

	//tempPhysics->SetVelocity(0, 0);
}

void MoveLeft(Event* event_)
{
	//std::cout << "A move Left! It was applied to entity \"" << std::endl;  //event_->objects[0]->getName() << "\"" << std::endl;
	ptr = event_->objects[0]->getComponent(ComponentType::Physics);
	tempPhysics = static_cast<PhysicsComponent*>(ptr);

	tempPhysics->AddToDirection(b2Vec2(-2, 0));

	//tempPhysics->SetVelocity(0, 0);
}

void MoveLeftEND(Event* event_)
{
	//std::cout << "A move Left END! It was applied to entity \"" << std::endl;  //event_->objects[0]->getName() << "\"" << std::endl;
	ptr = event_->objects[0]->getComponent(ComponentType::Physics);
	tempPhysics = static_cast<PhysicsComponent*>(ptr);

	//tempPhysics->AddToDirection(b2Vec2(2, 0));
	tempPhysics->SetDirectionToZero();
	//tempPhysics->SetVelocity(0, 0);
}

void MoveUp(Event* event_)
{
	//std::cout << "A move Up! It was applied to entity \"" << std::endl;  //event_->objects[0]->getName() << "\"" << std::endl;
	ptr = event_->objects[0]->getComponent(ComponentType::Physics);
	tempPhysics = static_cast<PhysicsComponent*>(ptr);

	tempPhysics->AddToDirection(b2Vec2(0, 2));

	//tempPhysics->SetVelocity(0, 0);
}

void MoveUpEND(Event* event_)
{
	//std::cout << "A move Up END! It was applied to entity \"" << std::endl;  //event_->objects[0]->getName() << "\"" << std::endl;
	ptr = event_->objects[0]->getComponent(ComponentType::Physics);
	tempPhysics = static_cast<PhysicsComponent*>(ptr);

	//tempPhysics->AddToDirection(b2Vec2(0, -2));
	tempPhysics->SetDirectionToZero();

	//tempPhysics->SetVelocity(0, 0);
}

void MoveDown(Event* event_)
{
	//std::cout << "A move Down! It was applied to entity \"" << std::endl;  //event_->objects[0]->getName() << "\"" << std::endl;
	ptr = event_->objects[0]->getComponent(ComponentType::Physics);
	tempPhysics = static_cast<PhysicsComponent*>(ptr);

	tempPhysics->AddToDirection(b2Vec2(0, -2));

	//tempPhysics->SetVelocity(0, 0);
}

void MoveDownEND(Event* event_)
{
	//std::cout << "A move Down END! It was applied to entity \"" << std::endl;  //event_->objects[0]->getName() << "\"" << std::endl;
	ptr = event_->objects[0]->getComponent(ComponentType::Physics);
	tempPhysics = static_cast<PhysicsComponent*>(ptr);

	//tempPhysics->AddToDirection(b2Vec2(0, 2));
	tempPhysics->SetDirectionToZero();

	//tempPhysics->SetVelocity(0, 0);
}


/* Here's where we initialise the map(s). Note that we're initialising one
 * map for each subsystem, because it reduces our search time for finding the
 * right function, than having all of the subsystems in one long map. Once
 * we've got the map associated with our subsystem, we check in that map for
 * the right EventType, and that provides us with the desired function
 *
 * (see the it2->second line in any of the Subsystem update methods).
 *
 * The last thing we really should take a look at is the Event class itself.
 * We can find it in Event.h.
 */

void EventQueue::InitialiseFunctionMaps()
{
	// it can ramain as map of type and map. 
	// type will be checked here to send it into correct place
	// subsystem will access the second map and resolve event 

	std::unordered_map<EventType, void(*)(Event*)>* physicsMap = new std::unordered_map<EventType, void(*)(Event*)>;

	physicsMap->insert({ EventType::MoveRight, &MoveRight });
	physicsMap->insert({ EventType::MoveRightEND, &MoveRightEND });
	physicsMap->insert({ EventType::MoveLeft, &MoveLeft });
	physicsMap->insert({ EventType::MoveLeftEND, &MoveLeftEND });
	physicsMap->insert({ EventType::MoveUp, &MoveUp });
	physicsMap->insert({ EventType::MoveUpEND, &MoveUpEND });
	physicsMap->insert({ EventType::MoveDown, &MoveDown });
	physicsMap->insert({ EventType::MoveDownEND, &MoveDownEND });
	
	functionMaps.push_back(physicsMap);
	functionMap.insert({ SubsystemType::Physics, physicsMap });

	std::unordered_map<EventType, void(*)(Event*)>* aiMap = new std::unordered_map<EventType, void(*)(Event*)>;

	//aiMap->insert({ EventType::MoveUp, &AIHandleMoveUp });
	//aiMap->insert({ EventType::MoveDown, &AIHandleMoveDown });

	functionMaps.push_back(aiMap);
	functionMap.insert({ SubsystemType::AI, aiMap });
}

EventQueue::~EventQueue()
{
	//delete ptr;
	//delete tempPhysics;
}

void EventQueue::popEvent(Event* event_)
{
	for (int i = 0; i < events.size(); i++)
	{
		if (events[i] == event_)
		{
			delete events[i];
			events.erase(events.begin() + i);
		}

	}
}

