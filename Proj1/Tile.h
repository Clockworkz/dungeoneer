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
	SDL_Rect clip;

public:
	bool inCollision(int posX, int posY) {
		if (!hasCollision) {
			return false;
		}
		if ((x < posX  && posX < x + mTexture.getWidth()) || (y < posY && posY < y + mTexture.getHeight())) {
			return true;
		}
		return false;
	};

	Tile(int xCoord,int yCoord, bool collision, std::string path, SDL_Renderer* gRenderer) :
		x(xCoord), y(yCoord), hasCollision(collision), imgPath(path) {
		if (!mTexture.loadFromFile(imgPath, gRenderer)) {
			std::cout << "load failed" << std::endl;
		}
	};

	void render(SDL_Renderer* gRenderer) {
		clip.w = mTexture.getWidth();
		clip.h = mTexture.getHeight();
		clip.x = 0;
		clip.y = 0;
		mTexture.render(x, y, &clip, gRenderer);
	}
};