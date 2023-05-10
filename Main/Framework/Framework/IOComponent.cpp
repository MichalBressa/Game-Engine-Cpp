#pragma once

#include "IOComponent.h"
#include "GameObject.h"
#include "IOSystem.h"
#include "EventQueue.h"

inline IOComponent& IOComponent::operator=(const IOComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}


void IOComponent::Update()
{
	std::vector<GameObject*> objects;
	std::vector<SubsystemType> systems;
	Event* event = new Event();

	objects.push_back(myObject);
	/*
		Input via keyboard can only be received from the player
		This mean that object influenced by the input will player game object that could be passed into IOsystem from game engien class
		when player is created
	
	*/
	SDL_Event e;
	while(SDL_PollEvent(&e)) 
	{
        switch( e.type )
		{
            // Look for a keypress 
            case SDL_KEYDOWN:
				// Check the SDLKey values and move change the coords 
				switch (e.key.keysym.sym) 
				{
				case SDLK_a:
					// left
					systems.push_back(SubsystemType::Physics);
					event->assignObjects(objects);
					event->assignSystems(systems);
					event->assignType(EventType::MoveLeft);
					mySystem->getEventQueue()->events.push_back(event);
					std::cout << "SDLK_a pressed" << std::endl;
					break;
				case SDLK_d:
					// right
					systems.push_back(SubsystemType::Physics);
					event->assignObjects(objects);
					event->assignSystems(systems);
					event->assignType(EventType::MoveRight);
					mySystem->getEventQueue()->events.push_back(event);
					std::cout << "SDLK_d pressed" << std::endl;
					break;
				case SDLK_w:
					// up
					systems.push_back(SubsystemType::Physics);
					event->assignObjects(objects);
					event->assignSystems(systems);
					event->assignType(EventType::MoveUp);
					mySystem->getEventQueue()->events.push_back(event);
					std::cout << "SDLK_w pressed" << std::endl;
					break;
				case SDLK_s:
					// down
					systems.push_back(SubsystemType::Physics);
					event->assignObjects(objects);
					event->assignSystems(systems);
					event->assignType(EventType::MoveDown);
					mySystem->getEventQueue()->events.push_back(event);
					std::cout << "SDLK_s pressed" << std::endl;
					break;
				default:
					
					break;
				}
				break;

			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_a:
					systems.push_back(SubsystemType::Physics);
					event->assignObjects(objects);
					event->assignSystems(systems);
					event->assignType(EventType::MoveLeftEND);
					mySystem->getEventQueue()->events.push_back(event);
					std::cout << "SDLK_a UP" << std::endl;
					break;
				case SDLK_d:
					systems.push_back(SubsystemType::Physics);
					event->assignObjects(objects);
					event->assignSystems(systems);
					event->assignType(EventType::MoveRightEND);
					mySystem->getEventQueue()->events.push_back(event);
					std::cout << "SDLK_d UP" << std::endl;
					break;
				case SDLK_w:
					systems.push_back(SubsystemType::Physics);
					event->assignObjects(objects);
					event->assignSystems(systems);
					event->assignType(EventType::MoveUpEND);
					mySystem->getEventQueue()->events.push_back(event);
					std::cout << "SDLK_w UP" << std::endl;
					break;
				case SDLK_s:
					systems.push_back(SubsystemType::Physics);
					event->assignObjects(objects);
					event->assignSystems(systems);
					event->assignType(EventType::MoveDownEND);
					mySystem->getEventQueue()->events.push_back(event);
					std::cout << "SDLK_s UP" << std::endl;
					break;
				case SDLK_ESCAPE:
					event->assignType(EventType::Exit);
					std::cout << "EXIT pressed" << std::endl;
					mySystem->getEventQueue()->events.push_back(event);
					// exit event
					break;
				default:
					break;
				}
				break;

			default:
				break;
		}
	}

};



/*
	I was working on alternative way of handling input that would allow user to press 2 keys at the same time

	SDL_Event e;
	const Uint8* keyboard_state;
	while(SDL_PollEvent(&e))
	{

		keyboard_state = SDL_GetKeyboardState(NULL);
		if (keyboard_state[SDL_SCANCODE_A])
		{
			systems.push_back(SubsystemType::Physics);
			event->assignObjects(objects);
			event->assignSystems(systems);
			event->assignType(EventType::MoveLeft);
			mySystem->getEventQueue()->events.push_back(event);
			std::cout << "SDLK_a pressed" << std::endl;
		}

		if (keyboard_state[SDL_SCANCODE_W])
		{
			systems.push_back(SubsystemType::Physics);
			event->assignObjects(objects);
			event->assignSystems(systems);
			event->assignType(EventType::MoveUp);
			mySystem->getEventQueue()->events.push_back(event);
			std::cout << "SDLK_w pressed" << std::endl;
		}

		if (keyboard_state[SDL_SCANCODE_S])
		{
			systems.push_back(SubsystemType::Physics);
			event->assignObjects(objects);
			event->assignSystems(systems);
			event->assignType(EventType::MoveDown);
			mySystem->getEventQueue()->events.push_back(event);
			std::cout << "SDLK_s pressed" << std::endl;
		}

		if (keyboard_state[SDL_SCANCODE_D])
		{
			systems.push_back(SubsystemType::Physics);
			event->assignObjects(objects);
			event->assignSystems(systems);
			event->assignType(EventType::MoveRight);
			mySystem->getEventQueue()->events.push_back(event);
			std::cout << "SDLK_d pressed" << std::endl;
		}


		if (keyboard_state[SDL_SCANCODE_ESCAPE])
		{
			event->assignType(EventType::Exit);
			std::cout << "EXIT pressed" << std::endl;
			mySystem->getEventQueue()->events.push_back(event);
			// exit event
		}


*/