#include <cassert>
#include <stdio.h>
#include <array>
#include "TiledMap.h"
#include "util.h"
#include "../constants.h"

typedef struct tile {
	float x{};
	float y{};
	float width{};
	float height{};
	int id{};
	char imagepath[256]{};
} tile_t;


static std::array<pk::tiled_map_info_t, pk::NumScenes> maps{
	pk::tiled_map_info_t{"", "", ""},
	pk::tiled_map_info_t{"World", MAPS_PATH "world.bin", MAPS_PATH "world.png"},
	pk::tiled_map_info_t{"Fire Arena", MAPS_PATH "fire.bin", MAPS_PATH "fire.png"},
	pk::tiled_map_info_t{"Plant Arena", MAPS_PATH "plant.bin", MAPS_PATH "plant.png"},
	pk::tiled_map_info_t{"Water Arena", MAPS_PATH "water.bin", MAPS_PATH "water.png"},
	pk::tiled_map_info_t{"Hospital", MAPS_PATH "hospital.bin", MAPS_PATH "hospital.png"},
	pk::tiled_map_info_t{"House", MAPS_PATH "house.bin", MAPS_PATH "house.png"},
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


const pk::tiled_map_info_t& pk::tiledmap_get_info(const pk::SceneID scene_id) {
	return maps[scene_id];
}


static void load_gameobj(pk::ECS* ecs, const tile_t& tile, FILE* file) {
	switch (tile.id) {
		case pk::FireArenaID:			
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				tile.width * 0.7f,
				tile.height * 0.6f
			);
			break;
		case pk::WaterArenaID:
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				tile.width * 0.7f,
				tile.height * 0.6f
			);
			break;
		case pk::PlantArenaID:
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				tile.width * 0.7f,
				tile.height * 0.6f
			);
			break;
		case pk::HospitalID:
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				tile.width * 0.8f,
				tile.height * 0.6f
			);
			break;
		case pk::HouseID:
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				tile.width * 0.8f,
				tile.height * 0.6f
			);
			break;
		case pk::TreeID:
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				pk::TILE_SIZE * 0.8f,
				pk::TILE_SIZE * 0.8f
			);
			break;
		case pk::RockID:
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				pk::TILE_SIZE * 0.6f,
				pk::TILE_SIZE * 0.6f
			);
			break;
		case pk::PalmID:
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				pk::TILE_SIZE * 0.6f,
				pk::TILE_SIZE * 0.6f
			);
			break;
		case pk::PillarID:
			ecs->add_collision_to_entity(
				ecs->sprite_create(pk::CAMERA_ZINDEX_OBJECTS, tile.imagepath, tile.x, tile.y),
				pk::TILE_SIZE * 0.8f,
				pk::TILE_SIZE * 0.8f
			);
			break;
		case pk::PillarTopID:
			ecs->sprite_create(pk::CAMERA_ZINDEX_TOP, tile.imagepath, tile.x, tile.y);
			break;
		default:
			break;
	}
}

static void load_entity(pk::ECS* ecs, const tile_t& tile) {
	switch (tile.id) {
		case pk::PlayerID:
			ecs->player_create(tile.x, tile.y);
			break;
		case pk::NurseID:
			break;
		default:
			break;
	}
}


void pk::tiledmap_load(pk::ECS* ecs, const pk::SceneID scene_id) {
	const pk::tiled_map_info_t& info = maps[scene_id];
	FILE* file;
	file = fopen(info.file, "rb");
	fseek(file, sizeof(int) * 2, SEEK_SET);

	// Terrain Image
	ecs->sprite_create(pk::CAMERA_ZINDEX_TERRAIN, info.terrain_image);

	while (!feof(file)) {
		int groupid, n;		
		tile_t tile{};
		fread(&groupid, sizeof(int), 1, file);
		fread(&n, sizeof(int), 1, file);
		for (int i = 0; i < n; i++) {
			fread(&tile, sizeof(tile_t) - sizeof(tile.imagepath), 1, file);
			switch (groupid) {
				case pk::EntitiesGroupID:
					load_entity(ecs, tile);
					break;
				case pk::CollisionGroupID:
					ecs->add_collision(tile.x, tile.y, tile.width, tile.height);
					break;
				case pk::TransitionGroupID:
					ecs->add_transition((pk::SceneID) tile.id, Rectangle{ tile.x, tile.y, tile.width, tile.height });
					break;
				case pk::CoastGroupID:
					break;
				case pk::MonsterGroupID:
					pk::readstr(tile.imagepath, file);
					break;
				case pk::GameObjsID:
					pk::readstr(tile.imagepath, file);
					load_gameobj(ecs, tile, file);
					break;
				case pk::WaterGroupID:
					ecs->component_insert(
						ecs->entity_create(pk::CAMERA_ZINDEX_WATER, true, tile.x, tile.y),
						pk::water_t{ 
							static_cast<std::uint8_t>(tile.height / pk::TILE_SIZE), 
							static_cast<std::uint8_t>(tile.width / pk::TILE_SIZE) 
						}
					);
					break;
				default:
					break;
			}

		}
	}
	fclose(file);
}
