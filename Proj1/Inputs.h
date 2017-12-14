#pragma once
#include <SDL.h>
#include <map>
#include "KeyMap.h"

class Input {
private:
	SDL_Event e;

	void process() {
		if (shoot == true) {
			attack = false;
		}
		if (shoot == false && walk == false && attack == false) { //(jump == false && walk == false && attack == false) {
			idle = true;
		}
	}
public:
	Input(bool inputWalk, bool inputShoot, bool inputQuit, bool inputFlip, bool inputAttack) :
		walk(inputWalk), shoot(inputShoot), quit(inputQuit), flip(inputFlip), attack(inputAttack) {};
	bool walk;
	bool shoot;
	bool quit;
	bool flip;
	bool attack;
	bool dying = false;
	bool idle = false;
	std::set<KeyMap::direction> directions;
	//KeyMap::direction direction;

	void processInput()
	{
		directions = {};
		walk = true;
		SDL_PumpEvents();
		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		//continuous-response keys
		if (keystate[SDL_SCANCODE_LEFT])
		{
			directions.insert(KeyMap::left);
		}
		if (keystate[SDL_SCANCODE_RIGHT])
		{
			directions.insert(KeyMap::right);
		}
		if (keystate[SDL_SCANCODE_UP])
		{
			directions.insert(KeyMap::up);
		}
		if (keystate[SDL_SCANCODE_DOWN])
		{
			directions.insert(KeyMap::down);
		}
		if (keystate[NULL]) {
			walk = false;
		}

		//single-hit keys, mouse, and other general SDL events (eg. windowing)
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				/*case SDL_MOUSEMOTION:
				break;*/

			case SDL_QUIT:
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE)
					quit = true; //quit
				break;
			}
		}
	}
};