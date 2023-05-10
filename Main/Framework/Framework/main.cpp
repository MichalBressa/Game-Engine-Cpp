#include <iostream>
#include "GameEngine.h"
#include "Commons.h"

using namespace std;

int main(int argc, char* argv[])
{
	GameEngine* game = new GameEngine();
	bool open = true;
	while (open)
	{
		open = game->Update();
	}
	delete game;
	return 0;
}