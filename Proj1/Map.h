#pragma once

#include <vector>
#include "Tile.h"

class Map {
private:
	SDL_Renderer** renderer;

	std::vector<std::vector<Tile*>> tileset;
	int tileWidth = 32;
	int tileHeight = 32;
	int mapSizeX;
	int mapSizeY;
	Camera* cam;

public:
	Map(int width, int height) : mapSizeX(width), mapSizeY(height) {};

	void set_tiles(SDL_Renderer* renderer, Camera* camera) {
		for (int i = 0; i < mapSizeX; i+= tileWidth) {
			std::vector<Tile*> row;
			for (int j = 0; j < mapSizeY; j+=tileHeight) {
				row.push_back(new Tile(i, j, false, "Test Assets/grass.png", renderer));
				std::cout << "i: " << i << ", j:" << j << std::endl;
			};
			tileset.push_back(row);
		};
	}

	void test_render(SDL_Renderer* gRenderer) {
		tileset[0][0]->render(gRenderer);
	}

	void render_tiles(SDL_Renderer* gRenderer) {
		for (auto vec : tileset) {
			for (auto tile : vec) {
				tile->render(gRenderer);
			}
		}
	}
};