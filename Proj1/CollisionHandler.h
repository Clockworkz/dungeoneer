#pragma once
#include <SDL.h>
#include <vector>
#include "Camera.h"

bool checkCollision2(SDL_Rect* A, std::vector<SDL_Rect*> rects) {
	SDL_Rect* B;
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	bool collision = true;
	for (auto n : rects) {
		B = n;
		leftA = A->x;
		rightA = A->x + A->w;
		topA = A->y;
		bottomA = A->y + A->h;

		//Calculate the sides of rect B
		leftB = B->x;
		rightB = B->x + B->w;
		topB = B->y;
		bottomB = B->y + B->h;

		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			collision = false;
		}

		if (topA >= bottomB)
		{
			collision = false;
		}

		if (rightA <= leftB)
		{
			collision = false;
		}

		if (leftA >= rightB)
		{
			collision = false;
		}
	}
	return collision;
}

bool checkCollision(SDL_Rect* rect1, std::vector<int> velocVec1, SDL_Rect* rect2, std::vector<int> velocVec2) {

	// Be able to determine which axis the collision is on, if on Y, stop Y movement, if on X stop X movement etc.
	SDL_Rect collision;
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	SDL_Rect A = *rect1;
	A.x += velocVec1[0];
	A.y += velocVec1[1];
	SDL_Rect B = *rect2;
	B.x += velocVec2[0];
	B.y += velocVec2[1];

	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;


	//if (SDL_IntersectRect(&rectA, &rectB, &collision) == SDL_TRUE) {
	//	std::cout << collision.x <<" "<< collision.y << std::endl;
	//	return true;
	//}
	//return false;
}

void processCollision(CharacterModel model1, CharacterModel model2, Camera camera1) {
	// use if platform
	if (model1.getBounds()->y + model1.getBounds()->h <= model2.getBounds()->y + model2.getBounds()->h) {
		model1.setVelocity(model1.getVelocVec()[0], 0);
		model1.setAcceleration(0, 0);
		model1.setPosY(model2.getBounds()->y - model1.getBounds()->h - camera1.getRect().y);
		model1.setYMax(model2.getBounds()->y - model1.getBounds()->h - camera1.getRect().y);
	}
	// use if wall
	else if (model1.getBounds()->x + model1.getBounds()->w >= model2.getBounds()->x) {
		model1.setVelocity(0, model1.getVelocVec()[1]);
		model1.setPosX(model2.getBounds()->x - camera1.getRect().y - model1.getBounds()->w);
		model1.setAcceleration(0, 0);
	}
}

void processCollision(CharacterModel model1, SDL_Rect rect1, Camera camera1) {
	// use if platform
	if (model1.getBounds()->y + model1.getBounds()->h <= rect1.y + rect1.h) {
		model1.setVelocity(model1.getVelocVec()[0], 0);
		model1.setAcceleration(0, 0);
		model1.setPosY(rect1.y - model1.getBounds()->h - camera1.getRect().y);
		model1.setYMax(rect1.y - model1.getBounds()->h - camera1.getRect().y);
		// use if wall
		/*	else if (playerChar.getBounds()->x + playerChar.getBounds()->w >= testRect.x) {
		playerChar.setVelocity(0,playerChar.getVelocVec()[1]);
		playerChar.setPosX(testRect.x - camera.getRect().y - playerChar.getBounds()->w);
		playerChar.setAcceleration(0, 0);
		}*/
	}
}


//// Move collision checks to a handler, maintain a vector of collision objects
//if (checkCollision2(playerChar.getBounds(), std::vector<SDL_Rect*>{skeleChar.getBounds(), &testRect}) == false) {
//	std::cout << "no collision" << std::endl;
//	playerChar.setYMax(baseLine.y - playerChar.getBounds()->h);
//}
//
//if (checkCollision(playerChar.getBounds(), playerChar.getVelocVec(), skeleChar.getBounds(), std::vector<int> {0, 0})) {
//	playerChar.setVelocity(0, 0);
//	playerChar.setAcceleration(0, 0);
//	skeleChar.setVelocity(0, 0);
//	playerChar.setPosY(skeleChar.getBounds()->y - playerChar.getBounds()->h - camera.getRect().y - 2);
//	playerChar.setYMax(skeleChar.getBounds()->y - playerChar.getBounds()->h - camera.getRect().y - 2);
//}
//
//if (checkCollision(playerChar.getBounds(), playerChar.getVelocVec(), &testRect, std::vector<int> {0, 0})) {
//	std::cout << "Collision on platform" << std::endl;
//	std::cout << "Base Y: " << playerChar.getPosY() << std::endl;
//	// use if platform
//	if (playerChar.getBounds()->y + playerChar.getBounds()->h <= testRect.y + testRect.h) {
//		playerChar.setVelocity(playerChar.getVelocVec()[0], 0);
//		playerChar.setAcceleration(NULL, 0);
//		playerChar.setPosY(testRect.y - playerChar.getBounds()->h - camera.getRect().y);
//		playerChar.setYMax(testRect.y - playerChar.getBounds()->h - camera.getRect().y);
//	}
//	// use if wall
//	/*	else if (playerChar.getBounds()->x + playerChar.getBounds()->w >= testRect.x) {
//	playerChar.setVelocity(0,playerChar.getVelocVec()[1]);
//	playerChar.setPosX(testRect.x - camera.getRect().y - playerChar.getBounds()->w);
//	playerChar.setAcceleration(0, 0);
//	}*/
//
//}
//if (checkCollision(playerChar.getBounds(), playerChar.getVelocVec(), &baseLine, std::vector<int> {0, 0})) {
//	std::cout << "Collision on base" << std::endl;
//	std::cout << "Base Y: " << baseLine.y << std::endl;
//	playerChar.setVelocity(0, 0);
//	playerChar.setAcceleration(0, 0);
//	playerChar.setPosY(baseLine.y - playerChar.getBounds()->h - camera.getRect().y);
//	playerChar.setYMax(baseLine.y - playerChar.getBounds()->h - camera.getRect().y);
//}
//if (checkCollision(skeleChar.getBounds(), skeleChar.getVelocVec(), &baseLine, std::vector<int> {0, 0})) {
//	std::cout << "Collision on base" << std::endl;
//	std::cout << "Base Y: " << baseLine.y << std::endl;
//	skeleChar.setVelocity(0, 0);
//	skeleChar.setAcceleration(0, 0);
//	skeleChar.setPosY(baseLine.y - skeleChar.getBounds()->h - camera.getRect().y);
//	skeleChar.setYMax(baseLine.y - skeleChar.getBounds()->h - camera.getRect().y);
//}