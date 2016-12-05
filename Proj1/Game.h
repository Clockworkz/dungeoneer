#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#include "LTexture.h"
#include "CharacterModel.h"
#include "Camera.h"
#include "Inputs.h"

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

	void setFrames() {
		playerChar.setRunFrames(144, 150);
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
		// game loop
		int frame = 0;
		playerChar.setPosX(1000);
		playerChar.setVelocity(10, 10);
		while (quit == false) {
			//SDL_UpdateWindowSurface(window);
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT){
					quit = true;
				}
				input.handle(&e);
			}
			SDL_RenderClear(renderer);
			camera.moveCam(&playerChar, &LEVEL_WIDTH, &LEVEL_HEIGHT);


			// Create level builder class/function
			bgTexture.render(0, 0, &camera.getRect(), renderer);
			playerChar.setPosY(1000);
			playerChar.move();
			int xPos = playerChar.getPosX() - camera.getRect().x;
			std::cout << xPos << std::endl;
			int yPos = playerChar.getPosY() - camera.getRect().y;
			playerChar.idleAnim(xPos, yPos, renderer);
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderPresent(renderer);
			frame++;
		}
		close();
		return 0;
	}

private:
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;

	const int LEVEL_WIDTH = 2560;
	const int LEVEL_HEIGHT = 2560;

	const int FRAMES_PER_UPDATE = 4;

	bool quit = false;

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	Camera camera = { &SCREEN_WIDTH, &SCREEN_HEIGHT };
	CharacterModel playerChar {"Universal-LPC-spritesheet-master/body/male/orc.png", 13, 21, 27};
	Input input{ false,false,false,false,false };


	LTexture bgTexture;
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
};