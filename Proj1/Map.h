#pragma once

#include <vector>
#include "Tile.h"

class Map {
private:
	SDL_Renderer** renderer;

	std::vector<std::vector<Tile>> tileset;
	int tileWidth = 32;
	int tileHeight = 32;
	int mapSizeX;
	int mapSizeY;
	Camera* cam;

public:
	Map(int width, int height) : mapSizeX(width), mapSizeY(height) {};

	void set_tiles(SDL_Renderer* renderer, Camera* camera) {
		for (int i = 0; i < mapSizeX / tileWidth; i++) {
			std::vector<Tile> row;
			for (int j = 0; j < mapSizeY / tileHeight; j++) {
				row.push_back(Tile(i, j, false, "Test Assets/grass.png", renderer, camera));
				std::cout << "i: " << i << ", j:" << j << std::endl;
			};
			tileset.push_back(row);
		};
	}

	void render_tiles(SDL_Renderer* renderer, Camera camera) {
		for (auto vec : tileset) {
			for (auto tile : vec) {
				tile.render(renderer, camera);
			}
		}
	}
};