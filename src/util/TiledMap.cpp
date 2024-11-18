#include <cassert>
#include <stdio.h>
#include <array>
#include "TiledMap.h"
#include "../constants.h"


static std::array<pk::tiled_map_info_t, pk::NumScenes> maps{
	pk::tiled_map_info_t{"", ""},
	pk::tiled_map_info_t{MAPS_PATH "world.bin", MAPS_PATH "world.png"},
	pk::tiled_map_info_t{MAPS_PATH "fire.bin", MAPS_PATH "fire.png"},
	pk::tiled_map_info_t{MAPS_PATH "plant.bin", MAPS_PATH "plant.png"},
	pk::tiled_map_info_t{MAPS_PATH "water.bin", MAPS_PATH "water.png"},
	pk::tiled_map_info_t{MAPS_PATH "hospital.bin", MAPS_PATH "hospital.png"},
	pk::tiled_map_info_t{MAPS_PATH "house.bin", MAPS_PATH "house.png"},
	pk::tiled_map_info_t{"", ""},
};


void pk::tiledmap_init() {
	int width, height;
	for (pk::tiled_map_info_t& info : maps) {
		FILE* file;
		file = fopen(info.file, "rb");
		assert(file != NULL);
		fread(&width, sizeof(int), 1, file);
		fread(&height, sizeof(int), 1, file);
		info.width = static_cast<float>(width);
		info.height = static_cast<float>(height);
		fclose(file);
	}
}


const pk::tiled_map_info_t& tiledmap_get_info(const pk::SceneID scene_id) {
	return maps[scene_id];
}


void pk::tiledmap_load(pk::ECS* ecs, const pk::SceneID scene_id) {
	const pk::tiled_map_info_t& info = maps[scene_id];
	FILE* file;
	file = fopen(info.file, "rb");
	fseek(file, sizeof(int) * 2, SEEK_SET);

	// Terrain Image
	ecs->sprite_create(pk::CAMERA_ZINDEX_TERRAIN, info.terrain_image);

	while (!feof(file)) {
		int groupid, objid, n;
		int x, y, width, height;		
		char imagepath[128];
		fread(&groupid, sizeof(int), 1, file);
		fread(&n, sizeof(int), 1, file);
		for (int i = 0; i < n; i++) {
			fread(&x, sizeof(float), 1, file);
			fread(&y, sizeof(float), 1, file);
			fread(&width, sizeof(float), 1, file);
			fread(&height, sizeof(float), 1, file);
			fread(&objid, sizeof(int), 1, file);
		}
	}

	//
	fclose(file);
}
