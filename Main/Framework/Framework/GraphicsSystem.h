#pragma once
#include "Commons.h"
#include "Subsystem.h"
#include "GraphicsComponent.h"

class GraphicsSystem : public Subsystem
{

	/*
	Initialize SDL and create the needed sections
	It is always good to check if each area actually initializes! If not, a print out will save you wondering why something doesn't work.
	You could also breakpoint and check if things are NULL still or not as well.
	*/

	/* Graphics could operate only on game object vector
	* It only need to draw everything that is an initialized game object 
	so there is no need to give it the event queue
	*/

public:
	GraphicsSystem(const GraphicsSystem& other) : Subsystem(other) {
		components->reserve(MAX_ENTITIES);
		window = other.window;
		renderer = other.renderer;
	};

	GraphicsSystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects) : Subsystem(SubsystemType::Graphics, _eventQueue, _gameObjects) {
		components = new std::vector<GraphicsComponent>;
		components->reserve(MAX_ENTITIES);
		window = nullptr;
		renderer = nullptr;
		SetUp();
	};

	~GraphicsSystem();


	Component* addComponent(Component* component_);
	inline void removeComponent(int i_) { components->erase(components->begin() + i_); }
	inline Component* getComponent(int i_) { return &(components->at(i_)); }
	void RunGraphicsPlaceholder();
	void SetUp();
	inline void Update();
	inline int getNumComponents() { return components->size(); }
	static SDL_Renderer* GetRenderer();

private:
	// should change into array later on for faster elements deleting 
	std::vector<GraphicsComponent>* components;
	SDL_Window* window;
	static SDL_Renderer* renderer;
	

};

