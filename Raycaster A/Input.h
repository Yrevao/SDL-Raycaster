#pragma once
#include <iostream>
#include <SDL.h>

#include "Data.h"

class Input {
public:
	Data runData;
	SDL_Event ev;

	Input();
	void mainLoop(); // main game loop
	void quit(); // unload everything
};