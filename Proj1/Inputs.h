#pragma once
#include <SDL.h>

class Input {
private:
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
	SDL_Keycode direction;
	bool dying = false;
	bool idle = false;

	void handle (SDL_Event* e, bool& quit) {
		std::cout << e->key.keysym.sym << std::endl;
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
				direction = e->key.keysym.sym;
				break;
			case SDLK_LEFT:
				walk = true;
				direction = e->key.keysym.sym;
				break;
			case SDLK_DOWN:
				walk = true;
				direction = e->key.keysym.sym;
				break;
			case SDLK_UP:
				walk = true;
				direction = e->key.keysym.sym;
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
			default:
				walk = false;
				shoot = false;
				attack = false;
				direction = NULL;
			}
		}
		/*else if (e->type == SDL_KEYUP) {
			switch (e->key.keysym.sym) {
			case SDLK_RIGHT:
				walk = false;
				direction = NULL;
				break;
			case SDLK_LEFT:
				walk = false;
				direction = NULL;
				break;
			case SDLK_DOWN:
				walk = false;
				direction = NULL;
				break;
			case SDLK_UP:
				walk = false;
				direction = NULL;
				break;
			case SDLK_ESCAPE:
				quit = false;
				break;
			}
		}*/
		else {
			walk = false;
			shoot = false;
			attack = false;
			direction = NULL;
		}
		process();
	}
};