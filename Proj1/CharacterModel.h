#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include <set>

#include "LTexture.h"
#include "KeyMap.h"

class CharacterModel {
public:
	CharacterModel(std::string path, int cols, int rows, int still) : TEX_COLS(cols), TEX_ROWS(rows), STILL_FRAME(still), TEX_PATH(path) {};

	bool loadMedia(SDL_Renderer* gRenderer) {
		//Loading success flag
		bool success = true;

		if (!mTexture.loadFromFile(TEX_PATH, gRenderer)) {
			std::cout << "Failed to load texture image!" << std::endl;
			success = false;
		}
		else {
			bounds.w = mTexture.getWidth() / TEX_COLS;
			bounds.h = mTexture.getHeight() / TEX_ROWS;
			mTexture.setClipRects(bounds.w, bounds.h, TEX_ROWS, TEX_COLS);
		}
		return success;
	}

	int processFrame(const int& FPU) {
		if (velocX == 0 && velocY == 0) {
			frame = STILL_FRAME;
			return frame / FPU;
		}

		if (velocX > 0) {
			if (frame > RUN_RIGHT_END*FPU) {
				frame = RUN_RIGHT_START * FPU;
			}
			if (frame < RUN_RIGHT_START*FPU) {
				frame = RUN_RIGHT_START * FPU;
			}
			return frame / FPU;
		}
		if (velocX < 0) {
			if (frame > RUN_LEFT_END*FPU) {
				frame = RUN_LEFT_START * FPU;
			}
			if (frame < RUN_LEFT_START*FPU) {
				frame = RUN_LEFT_START * FPU;
			}
			return frame / FPU;
		}

		if (velocY > 0) {
			if (frame > RUN_DOWN_END*FPU) {
				frame = RUN_DOWN_START * FPU;
			}
			if (frame < RUN_DOWN_START*FPU) {
				frame = RUN_DOWN_START * FPU;
			}
			return frame / FPU;
		}
		if (velocY < 0) {
			if (frame > RUN_UP_END*FPU) {
				frame = RUN_UP_START * FPU;
			}
			if (frame < RUN_UP_START*FPU) {
				frame = RUN_UP_START * FPU;
			}
			return frame / FPU;
		}
	}

	// Need to process array of directions. Currently can only handle one at a time - if multiple are pressed only the last pressed is handled
	void runAnim(int x, int y, const int& FPU, SDL_Renderer* gRenderer, std::set<KeyMap::direction> directions) {
		velocX = 0;
		velocY = 0;

		if (directions.find(KeyMap::direction::right) != directions.end()) {
			velocX += 5;			
		}

		if (directions.find(KeyMap::direction::left) != directions.end()) {
			velocX += -5;
		}

		if (directions.find(KeyMap::direction::up) != directions.end()) {
			velocY += -5;
		}

		if (directions.find(KeyMap::direction::down) != directions.end()) {
			velocY += 5;
		}

		mTexture.renderAnim(x, y, processFrame(FPU), gRenderer, 0.0, NULL, flip);
	}

	bool attackAnim(int x, int y, const int& FPU, SDL_Renderer* gRenderer) {
		if (frame > ATTACK_END*FPU) {
			frame = ATTACK_START*FPU;
		}
		if (frame < ATTACK_START*FPU) {
			frame = ATTACK_START*FPU;
		}
		if (frame < ATTACK_END*FPU) {
			mTexture.renderAnim(x, y, frame / FPU, gRenderer, 0.0, NULL, flip);
			attacking = true;
		}
		else {
			attacking = false;
		}
		return attacking;
	}

	bool shootAnim(int x, int y, const int& FPU, SDL_Renderer* gRenderer) {
		if (frame > SHOOT_END*FPU) {
			frame = SHOOT_START*FPU;
		}
		if (frame < SHOOT_START*FPU) {
			frame = SHOOT_START*FPU;
		}
		if (frame < SHOOT_END*FPU) {
			mTexture.renderAnim(x, y, frame / FPU, gRenderer, 0.0, NULL, flip);
			shooting = true;
		}
		else {
			shooting = false;
		}
		return shooting;
	}

	void idleAnim(int x, int y, SDL_Renderer* gRenderer) {
		mTexture.renderAnim(x, y, STILL_FRAME, gRenderer, 0.0, NULL, flip);
	}

	void setRunRightFrames(int startFrame, int endFrame) {
		RUN_RIGHT_START = startFrame;
		RUN_RIGHT_END = endFrame;
	}

	void setRunLeftFrames(int startFrame, int endFrame) {
		RUN_LEFT_START = startFrame;
		RUN_LEFT_END = endFrame;
	}

	void setRunDownFrames(int startFrame, int endFrame) {
		RUN_DOWN_START = startFrame;
		RUN_DOWN_END = endFrame;
	}

	void setRunUpFrames(int startFrame, int endFrame) {
		RUN_UP_START = startFrame;
		RUN_UP_END = endFrame;
	}

	void setAttackFrames(int startFrame, int endFrame) {
		ATTACK_START = startFrame;
		ATTACK_END = endFrame;
	}

	void setShootFrames(int startFrame, int endFrame) {
		SHOOT_START = startFrame;
		SHOOT_END = endFrame;
	}

	void move() {
		//accelerate();
		bounds.x = bounds.x + velocX;
		bounds.y = bounds.y + velocY;
		if ((bounds.y + bounds.h) > yMax) {
			bounds.y = yMax - bounds.h - velocY;
		}

		if ((bounds.y) < 0) {
			bounds.y = 0;
		}

		if ((bounds.x + bounds.w) > xMax) {
			bounds.x = xMax - bounds.w - velocX;
		}

		if ((bounds.x) < 0) {
			bounds.x = 0;
		}
	}

	SDL_Rect* getBounds() {
		return &bounds;
	}

	void setVelocity(int x, int y) {
		velocX = x;
		velocY = y;
	}

	std::vector<int> getVelocVec() {
		return std::vector<int> {velocX, velocY};
	}

	//void accelerate() {
	//	velocX += accelX;
	//	if (bounds.y < yMax + bounds.h) {
	//		velocY += accelY;
	//	}
	//}

	void setAcceleration(int x, int y) {
		accelX = x;
		accelY = y;
	}

	int getPosX() {
		return bounds.x;
	}

	int getPosY() {
		return bounds.y;
	}

	void setPosX(int x) {
		bounds.x = x;
	}

	void setPosY(int y) {
		if (y == 0) {
			bounds.y = Y_BASE;
		}
		else {
			bounds.y = y;
		}
	}

	void setYMax(int y) {
		if (y == -1) {
			yMax = Y_BASE;
		}
		else {
			yMax = y;
		}
	}

	void incrementFrame() {
		frame++;
	}

private:
	KeyMap keyMap = KeyMap();
	const int TEX_ROWS;
	const int TEX_COLS;
	const int STILL_FRAME;
	const std::string TEX_PATH;
	int Y_BASE = 768;
	int X_BASE = 1280;

	LTexture mTexture;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int RUN_RIGHT_START = NULL;
	int RUN_RIGHT_END = NULL;
	int RUN_DOWN_START = NULL;
	int RUN_DOWN_END = NULL;
	int RUN_LEFT_START = NULL;
	int RUN_LEFT_END = NULL;
	int RUN_UP_START = NULL;
	int RUN_UP_END = NULL;

	int ATTACK_START = NULL;
	int ATTACK_END = NULL;
	int SHOOT_START = NULL;
	int SHOOT_END = NULL;

	int yMax = 768;
	int yMin = 0;
	int xMax = 1280;
	int xMin = 0;

	int accelX;
	int velocX;
	int accelY;
	int velocY;

	SDL_Rect bounds = { 0,0 };


	bool attacking = NULL;
	bool jumping = NULL;
	bool shooting = NULL;
	bool falling = NULL;
	int frame = 0;
};