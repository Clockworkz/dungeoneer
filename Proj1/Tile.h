#pragma once
#include <SDL.h>
#include <string>
#include "LTexture.h"

class Tile {
private:
	const int x;
	const int y;
	const bool hasCollision;
	LTexture mTexture;
	std::string imgPath;

public:
	Tile(int xCoord,int yCoord, bool collision, std::string path, SDL_Renderer* gRenderer, Camera* camera) :
		x(xCoord), y(yCoord), hasCollision(collision), imgPath(path) {
		mTexture.loadFromFile(imgPath, gRenderer);
	};

	void render(SDL_Renderer* renderer, Camera camera) {
		mTexture.render(x, y, &camera.getRect(), renderer);
	}
};