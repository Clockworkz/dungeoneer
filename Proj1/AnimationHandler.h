#pragma once
#include <SDL_render.h>

#include "CharacterModel.h"
#include "Inputs.h"

class AnimationHandler {
public:
	void handle(Input* input, CharacterModel playerChar, SDL_Renderer* renderer) {
		// abstract these to function
		int xPos = playerChar.getPosX() - camera.getRect().x;
		int yPos = playerChar.getPosY() - camera.getRect().y;
		if (dying == true) {
			jump = false;
			attack = false;
			shoot = false;
			dying = playerChar.deathAnim(xPos, yPos, *frame, FRAMES_PER_UPDATE, renderer);
		}
		else if (shoot == true) {
			jump = false;
			attack = false;
			shoot = playerChar.shootAnim(xPos, yPos, *frame, FRAMES_PER_UPDATE, renderer);
		}
		else if (attack == true) {
			jump = false;
			attack = playerChar.attackAnim(xPos, yPos, *frame, FRAMES_PER_UPDATE, renderer);
		}
		else if (fall == true) {
			fall = playerChar.fallingAnim(xPos, yPos, renderer);
		}
		else if (jump == true) {
			temp = playerChar.jumpAnim(xPos, yPos, *frame, FRAMES_PER_UPDATE, renderer);
			jump = temp[0];
			fall = temp[1];
		}
		else if (walk == true) {
			if (flip == SDL_FLIP_HORIZONTAL) {
				playerChar.setVelocity(-5, playerChar.getVelocVec()[1]);
			}
			else {
				playerChar.setVelocity(5, playerChar.getVelocVec()[1]);
			}
			playerChar.runAnim(xPos, yPos, *frame, FRAMES_PER_UPDATE, renderer);
		}
		else { //(jump == false && walk == false && attack == false) {
			playerChar.setVelocity(0, playerChar.getVelocVec()[1]);
			playerChar.idleAnim(xPos, yPos, renderer);
		}
	}
};