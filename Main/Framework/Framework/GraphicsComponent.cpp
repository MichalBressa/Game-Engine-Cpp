#pragma once
#include "GraphicsComponent.h"
#include "GraphicsSystem.h"
#include "GameObject.h"

/*
 * The Update method is the beating heart of our entity component system. We might be
 * worried that we won't benefit from ECS in this implementation, given that we've used
 * vectors, but post-2011 C++ compilers make vectors contiguous in memory, so they have
 * all the benefits of arrays, plus the additional functionality of vectors. (Note: be
 * mindful of the warning in PhysicsSubsystem.h regarding reserving memory, though! Just
 * to be sure you don't run into problems).
 */
SDL_Texture* texture = nullptr;

//SDL_Window* window = nullptr;

GraphicsComponent::GraphicsComponent(GameObject* myObject_, Subsystem* mySystem_, SDL_Renderer* renderer_) : Component(ComponentType::Graphics, myObject_, mySystem_)
{
	//graphicsSystemInst = GraphicsSystem::GetInstance();
	//Loading in the image and making it a texture
	renderer = renderer_;

	SDL_Surface* loadedSurface = IMG_Load("../Textures/keyboardcat.jpg");
	if (loadedSurface == nullptr)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == nullptr)
		{
			printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}
	// width and height
	rect.w = 98.0f;
	rect.h = 98.0f;
	// position
	rect.y = myObject_->GetGraphicsPosition().y;
	rect.x = myObject_->GetGraphicsPosition().x;
	//rect.y = 500;
	//rect.x = 500;

	outlineRect.w = 101.0f;
	outlineRect.h = 101.0f;
	outlineRect.x = rect.x + 2;
	outlineRect.y = rect.y + 2;
	//rect.y = 500;
	//rect.x = 500;

};

void GraphicsComponent::UpdatePosition()
{
	rect.y = myObject->GetGraphicsPosition().y;
	rect.x = myObject->GetGraphicsPosition().x;

	//std::cout << "X: " << rect.x << "   Y: " << rect.y << std::endl;

	outlineRect.x = rect.x + 2;
	outlineRect.y = rect.y + 2;
}

inline GraphicsComponent& GraphicsComponent::operator=(const GraphicsComponent& other)
{
	if (this == &other)
	{
		return *this;
	}
	memcpy(this, &other, sizeof(other));
	return *this;
}

void GraphicsComponent::Update()
{
	//std::cout << "The graphics component of " << myObject->getName() << " is updating" << std::endl;
	UpdatePosition(); // recalculate position on screen 

	SDL_RenderFillRect(renderer, &outlineRect);

	SDL_RenderCopy(renderer, texture, nullptr, &rect);

}

void GraphicsComponent::AddSurface(char* fileName)
{
	//Loading in the image and making it a texture
	SDL_Surface* loadedSurface = IMG_Load(fileName);
	if (loadedSurface == nullptr)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == nullptr)
		{
			printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

}


