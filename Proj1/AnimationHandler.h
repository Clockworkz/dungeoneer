#pragma once
#include <SDL_render.h>

#include "CharacterModel.h"
#include "Inputs.h"

class AnimationHandler {
public:
	void handle(Input* input, CharacterModel* playerChar, const int& FPU, SDL_Renderer* renderer, Camera* camera) {
		int xPos = playerChar->getPosX() - camera->getRect().x;
		int yPos = playerChar->getPosY() - camera->getRect().y;
		// abstract these to function
		if (input->dying == true) { // move dying flag to character model
			input->attack = false;
			input->shoot = false;
			//input.dying = playerChar.deathAnim(xPos, yPos, *frame, FRAMES_PER_UPDATE, renderer);
		}
		else if (input->shoot == true) {
			input->attack = false;
			input->shoot = playerChar->shootAnim(xPos, yPos, FPU, renderer);
		}
		else if (input->attack == true) {
			input->attack = playerChar->attackAnim(xPos, yPos, FPU, renderer);
		}
		else if (input->walk == true) {
			playerChar->runAnim(xPos, yPos, FPU, renderer, input->directions);
		}
		else { //(jump == false && walk == false && attack == false) {
			playerChar->setVelocity(0, 0);
			playerChar->idleAnim(xPos, yPos, renderer);
		}
	}
};