#pragma once
#include <SDL.h>

class Input {
public:
	Input(bool inputWalk, bool inputShoot, bool inputQuit, bool inputFlip, bool inputAttack) :
		walk(inputWalk), shoot(inputShoot), quit(inputQuit), flip(inputFlip), attack(inputAttack) {};
	bool walk;
	bool shoot;
	bool quit;
	bool flip;
	bool attack;
	bool idle = false;

	void process () {
		if (shoot == true) {
			attack = false;
		}
		else { //(jump == false && walk == false && attack == false) {
			idle = true;
		}
	}

	void handle (SDL_Event* e) {
		if (e->type == SDL_QUIT) {
			quit = true;
		}

		// abstract non-quit key actions to key states instead of reading PollEvent (saves needing both key_down and key_up switch)
		else if (e->type == SDL_KEYDOWN) {
			switch (e->key.keysym.sym) {
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_RIGHT:
				walk = true;
				flip = false;
				break;
			case SDLK_LEFT:
				walk = true;
				flip = true;
				break;
			case SDLK_f:
				if (attack == false) {
					attack = true;
				}
				break;
			case SDLK_r:
				if (shoot == false) {
					shoot = true;
				}
				break;
			case SDLK_SPACE:
				// Do something
				break;
			}
		}
		else if (e->type == SDL_KEYUP) {
			switch (e->key.keysym.sym) {
			case SDLK_RIGHT:
				walk = false;
				break;
			case SDLK_LEFT:
				walk = false;
				break;
			case SDLK_ESCAPE:
				quit = false;
				break;
			}
		}
	}
};