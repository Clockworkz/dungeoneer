#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <rapidjson\rapidjson.h>

#include "LTexture.h"
#include "CharacterModel.h"
#include "Camera.h"
#include "Inputs.h"
#include "AnimationHandler.h"
#include "Map.h"

/* TO DO 
- Level/Map generator
- EnemyCharacterModel class
- NPC Model class
- Enemy generator - tie in to map generator

*/

class Game {
public:
	Game() {
		// initialise sdl
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		}
		else { // create window
			window = SDL_CreateWindow("Test window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (window == nullptr) {
				std::cout << "Failed to initialise window." << std::endl;
			}
			else {
				//Create renderer for window
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (renderer == nullptr)
				{
					std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					// initialise png loader
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						std::cout << "Coudlnt initialise SDL_image" << IMG_GetError() << imgFlags << std::endl;
					}
					// create surface
					else {
						screenSurface = SDL_GetWindowSurface(window);
						if (screenSurface == nullptr) {
							std::cout << "Failed to initialise surface." << std::endl;
						}
					}
				}
			}
		}
	}

	void close() {
		SDL_FreeSurface(screenSurface);
		screenSurface = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		//mTexture.free();

		SDL_Quit();
		IMG_Quit();
	}

	int run() {
		SDL_Event e;
		playerChar.loadMedia(renderer);
		bgMap.set_tiles(renderer, &camera);
		// game loop
		setFrames();
		int frame = 0;
		playerChar.setPosX(LEVEL_WIDTH/2);
		playerChar.setPosY(LEVEL_HEIGHT/2);
		while (quit == false) {
			/*while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT){
					quit = true;
				}
				input.handle(&e, quit);
			}*/
			input.processInput();
			quit = input.quit;
			SDL_RenderClear(renderer);
			// Create level builder
			bgMap.render_tiles(renderer);
			animHandler.handle(&input, &playerChar, FRAMES_PER_UPDATE, renderer, &camera);
			playerChar.move();
			camera.moveCam(&playerChar, &LEVEL_WIDTH, &LEVEL_HEIGHT);
			
			SDL_RenderPresent(renderer);
			playerChar.incrementFrame();
		}
		close();
		return 0;
	}

private:
	void setFrames() {
		playerChar.setRunRightFrames(144, 150);
		playerChar.setRunLeftFrames(118, 124);
		playerChar.setRunDownFrames(131, 137);
		playerChar.setRunUpFrames(105, 111);
	}

	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 768;

	const int LEVEL_WIDTH = 1280;
	const int LEVEL_HEIGHT = 768;

	const int FRAMES_PER_UPDATE = 4;

	bool quit = false;

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	Camera camera = { &SCREEN_WIDTH, &SCREEN_HEIGHT };
	CharacterModel playerChar {"Universal-LPC-spritesheet-master/body/male/orc.png", 13, 21, 27};
	Input input{ false,false,false,false,false };
	AnimationHandler animHandler;
	Map bgMap = { LEVEL_WIDTH, LEVEL_HEIGHT };
	LTexture bgTexture;
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
};