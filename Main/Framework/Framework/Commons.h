#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <iostream>
#include <string>
#include "Box2D/Box2D.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h> 

enum class ObjectShape { Ractangle, Circle};		
enum class EventType { MoveUp, MoveDown, MoveLeft, MoveRight, MoveUpEND, MoveDownEND, MoveLeftEND, MoveRightEND, Exit, Graphics, Unassigned };
enum class SubsystemType { Physics, IO, AI, Sound, Graphics, Unassigned, FileSystem, Network};
enum class ComponentType { Physics, IO, AI, Sound, Graphics, Unassigned };
enum class BehaviourType { Patrol, Hunt, Unassigned };

#define MAX_ENTITIES 10

