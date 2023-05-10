#pragma once
#include "Commons.h"
#include "Component.h"
class GraphicsSystem;

class GraphicsComponent : public Component
{
public:
	GraphicsComponent(GameObject* myObject_, Subsystem* mySystem_, SDL_Renderer* renderer);

	GraphicsComponent& operator=(const GraphicsComponent& other);

	void Update();
	void AddSurface(char* fileName);
	void UpdatePosition();

	~GraphicsComponent() {};

private:
	/* This is where you stick data unique to the component! */
	// texture
	SDL_Renderer* renderer;
	SDL_Rect rect;
	SDL_Rect outlineRect;

};

