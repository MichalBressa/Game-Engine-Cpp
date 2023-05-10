#pragma once
#include "PhysicsSystem.h"
#include "EventQueue.h"

/*
SDL2 works in pixels while Box2D works in meters like other physics middleware
We need a scale Factor to be bale to use them together
in here 200px are 1 meter
*/
b2Vec2 gravity(0.f, 0.f);
b2World world(gravity);

// 120hz
float timeStep = 1.0f / 120.0f;
// velocityIterations equals 8 and positionIterations equals 3 as recomemnded by createor of box2d
// lower the number = better perfomrence but lower accuracy
int velocityIterations = 8;
int positionIterations = 3;

Component* PhysicsSystem::addComponent(Component* component_)
{
	if (component_->getType() == ComponentType::Physics)
	{
		PhysicsComponent* temp = static_cast<PhysicsComponent*>(component_);
		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Tried to push a non-physics component to the physics subsystem wot" << std::endl;
		return nullptr;
	}
}

b2World* PhysicsSystem::GetWorld()
{
	return &world;
}
/*
 * The Update method is the beating heart of our entity component system. We might be
 * worried that we won't benefit from ECS in this implementation, given that we've used
 * vectors, but post-2011 C++ compilers make vectors contiguous in memory, so they have
 * all the benefits of arrays, plus the additional functionality of vectors. (Note: be
 * mindful of the warning in PhysicsSubsystem.h regarding reserving memory, though! Just
 * to be sure you don't run into problems).
 */

void PhysicsSystem::Update()
{
	/*
	 * Entity component in a nutshell: every component updates itself, in a tight loop
	 * across contiguous memory
	 */

	//world.Step(timeStep, velocityIterations, positionIterations);
	world.Step(timeStep, velocityIterations, positionIterations);

	for (int i = 0; i < components->size(); i++)
	{
		components->at(i).Update();
	}

	/* After this, we check the event queue. */

	int eQsize = eventQueue->events.size();

	if (eQsize > 0)
	{
		Event* temp;

		for (int i = 0; i < eQsize; i++)
		{
			/* If there's an event, we check it out, and see if it's
			 * something this subsystem cares about (== type).
			 */

			temp = eventQueue->events[i];

			for (int j = 0; j < temp->systems.size(); j++)
			{
				if (temp->systems[j] == type)
				{
					/* If we care about it, we know we'll have a function
					 * to deal with it somewhere in the eventQueue. We'll
					 * look into that in more detail in EventQueue.h
					 */

					auto it = eventQueue->functionMap.find(type);

					auto it2 = it->second->find(temp->type);

					/* We find our function and pass in the event as its
					 * parameter. We then pop our subsystem off the event's
					 * subsystem list, so we don't react to it twice!
					 */

					it2->second(temp);

					temp->systems.erase(temp->systems.begin() + j);

					/* If we were the last subsystem to react to the event,
					 * we remove it from the event queue entirely, to save
					 * memory. Let's have a look at the event queue in
					 * EventQueue.h
					 */

					if (temp->systems.size() == 0)
					{
						delete eventQueue->events[i];
						eventQueue->events.erase(eventQueue->events.begin() + i);
					}
				}
			}
		}
	}
}