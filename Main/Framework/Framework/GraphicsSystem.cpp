#pragma once
#include "GraphicsSystem.h"
#include <stdio.h>

//SDL_Window* window = nullptr;
SDL_Renderer* GraphicsSystem::renderer = nullptr;
SDL_Texture* catImage = nullptr;

SDL_Rect rect;
SDL_Rect outlineRect;

void GraphicsSystem::RunGraphicsPlaceholder()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL Conversion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 540, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				int flag = IMG_INIT_JPG;
				int initted = IMG_Init(IMG_INIT_JPG);
				if ((initted & flag) != flag)
				{
					printf("IMG_Init: Failed to init required jpg and png support!\n");
					printf("IMG_Init: %s\n", IMG_GetError());
				}
			}
		}
	}

	/*
	Loading in the image and making it a texture
	*/
	SDL_Surface* loadedSurface = IMG_Load("../Textures/keyboardcat.jpg");
	if (loadedSurface == nullptr)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	else
	{
		catImage = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (catImage == nullptr)
		{
			printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
		}

		SDL_FreeSurface(loadedSurface);
	}

	rect.w = 198.0f;
	rect.h = 198.0f;
	rect.x = 600.0f;
	rect.y = 2.0f;

	outlineRect.w = 201.0f;
	outlineRect.h = 201.0f;
	outlineRect.x = 598.0f;
	outlineRect.y = 1.0f;

	//Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderFillRect(renderer, &outlineRect);

	SDL_RenderCopy(renderer, catImage, nullptr, &rect);

	filledCircleRGBA(renderer, 100, 100, 100, 255, 255, 0, 255);

	//Update screen
	SDL_RenderPresent(renderer);
	

	// Make sure we clean up all the areas we used
	IMG_Quit();

	SDL_DestroyTexture(catImage);
	catImage = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}

void GraphicsSystem::SetUp()
{
	//if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	//{
	//	printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	//}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDL Conversion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			if (renderer == nullptr)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				int flag = IMG_INIT_JPG;
				int initted = IMG_Init(IMG_INIT_JPG);
				if ((initted & flag) != flag)
				{
					printf("IMG_Init: Failed to init required jpg and png support!\n");
					printf("IMG_Init: %s\n", IMG_GetError());
				}
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	//SDL_Delay(4000);
}



GraphicsSystem::~GraphicsSystem()
{
	// Make sure we clean up all the areas we used
	IMG_Quit();

	SDL_DestroyTexture(catImage);
	catImage = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	//Quit SDL subsystems
	SDL_Quit();

	delete components;
	delete window;
	delete renderer;
}

Component* GraphicsSystem::addComponent(Component* component_)
{
	if (component_->getType() == ComponentType::Graphics)
	{
		GraphicsComponent* temp = static_cast<GraphicsComponent*>(component_);
		components->push_back(*temp);
		return &(components->back());
	}
	else
	{
		std::cout << "Tried to push a non-graphics component to the graphics subsystem wot" << std::endl;
		return nullptr;
	}
}

/*
 * The Update method is the beating heart of our entity component system. We might be
 * worried that we won't benefit from ECS in this implementation, given that we've used
 * vectors, but post-2011 C++ compilers make vectors contiguous in memory, so they have
 * all the benefits of arrays, plus the additional functionality of vectors. (Note: be
 * mindful of the warning in PhysicsSubsystem.h regarding reserving memory, though! Just
 * to be sure you don't run into problems).
 */

void GraphicsSystem::Update()
{
	// event queue is useless here
	// should go through all game objects and draw them
	SDL_RenderClear(renderer);

	// stuff to render
	for (int i = 0; i < components->size(); i++)
	{
		// that should trigger update in each graphics component that uses SDL_RenderCopy to add its texture/image to the renderer
		components->at(i).Update();
	}
	// and render the result
	SDL_RenderPresent(renderer);

}

SDL_Renderer* GraphicsSystem::GetRenderer()
{
	return renderer;
}
