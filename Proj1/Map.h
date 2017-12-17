#pragma once

#include <vector>
#include <string>
#include <random>
#include <time.h>

#include "Tile.h"

class Map {
private:
	std::vector<std::vector<Tile*>> tileSet;
	std::vector<std::vector<Tile*>> decorationSet;
	int tileWidth = 32;
	int tileHeight = 32;
	int mapSizeX;
	int mapSizeY;

public:
	Map(int width, int height) : mapSizeX(width), mapSizeY(height) {};

	void SetTiles(SDL_Renderer* renderer) {
		for (int i = 0; i < mapSizeX; i+= tileWidth) {
			std::vector<Tile*> row;
			for (int j = 0; j < mapSizeY; j+=tileHeight) {
				//std::srand(time(NULL));
				auto randNum = std::rand() % 10;
				if (randNum < 5) {
					row.push_back(new Tile(i, j, false, "Test Assets/dirt3.png", renderer));
				}
				else if (randNum < 8) {
					row.push_back(new Tile(i, j, false, "Test Assets/dirt.png", renderer));
				}
				else {
					row.push_back(new Tile(i, j, false, "Test Assets/dirt2.png", renderer));
				}
			};
			tileSet.push_back(row);
		};
	}

	void SetDecorations(SDL_Renderer* renderer) {
		for (int i = 0; i < mapSizeX; i += tileWidth) {
			std::vector<Tile*> row;
			for (int j = 0; j < mapSizeY; j += tileHeight) {
				//std::srand(time(NULL));
				auto randNum = std::rand() % 100;
				if (randNum <= 5) {
					row.push_back(new Tile(i, j, false, "Test Assets/rock.png", renderer));
				}
				else if (randNum <= 10) {
					row.push_back(new Tile(i, j, false, "Test Assets/grass2.png", renderer));
				}
				else if (randNum <= 11) {
					row.push_back(new Tile(i, j, true, "Test Assets/rock2.png", renderer));
				}
			};
			decorationSet.push_back(row);
		};
	}

	bool CheckCollisions(int posX, int posY) {
		int x = posX;
		int y = posY;
		//if (tileSet[x][y]->inCollision(posX, posY)) {
		//	return true;
		//};

		/*for (auto vec : tileSet) {
			for (auto tile : vec) {
				if (tile->inCollision(posX, posY)) {
					return true;
				}
			}
		}*/

		/*for (auto vec : decorationSet) {
			for (auto tile : vec) {
				if (tile->inCollision(posX, posY)) {
					return true;
				}
			}
		}*/
		return false;
	}

	void RenderTiles(SDL_Renderer* gRenderer) {
		for (auto vec : tileSet) {
			for (auto tile : vec) {
				tile->render(gRenderer);
			}
		}
		for (auto vec : decorationSet) {
			for (auto tile : vec) {
				tile->render(gRenderer);
			}
		}
	}
};