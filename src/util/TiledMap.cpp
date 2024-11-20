#include <cassert>
#include <stdio.h>
#include <fstream>
#include "TiledMap.h"
#include "util.h"
#include "../ecs/EcsManager.h"
#include "../constants.h"


static void load_entity(pk::ECS* ecs, const pk::tile_t& tile) {
	const pk::entity_t e = ecs->entity_create(tile.zindex, true);
	ecs->get_transform(e)->rect = { tile.x - pk::PLAYER_SIZE / 2.0f, tile.y - pk::PLAYER_SIZE / 2.0f, pk::PLAYER_SIZE, pk::PLAYER_SIZE };
	ecs->component_insert<pk::character_t>(e, pk::character_t{ tile.objid, (char)(tile.direction - '0') });
	switch (tile.objid) {
		case pk::PlayerID:
			ecs->component_insert<pk::sprite_animation_t>(e, pk::sprite_animation_t{ CHARACTERS_PATH "player.png" });
			ecs->component_insert<pk::player_t>(e, pk::player_t{ e, ecs->sprite_create(tile.zindex - 1, GRAPHICS_PATH "other/shadow.png") });
			break;
		case pk::NurseID:
			ecs->component_insert<pk::sprite_animation_t>(e, pk::sprite_animation_t{ CHARACTERS_PATH "purple_girl.png" });
			break;
		default:
			break;
	}
}


static void load_collision(pk::ECS* ecs, const pk::tile_t& tile) {
	ecs->add_collision(tile.x, tile.y, tile.width, tile.height);
}


static void load_transition(pk::ECS* ecs, const pk::tile_t& tile) {
	ecs->add_transition(
		static_cast<pk::SceneID>(tile.objid),
		Rectangle{tile.x, tile.y, tile.width, tile.height}
	);
}


static void load_coast(pk::ECS* ecs, const pk::tile_t& tile) {
	const pk::entity_t e = ecs->entity_create(tile.zindex, true, tile.x, tile.y);
	ecs->component_insert<pk::coast_t>(
		e, 
		pk::coast_t{
			static_cast<pk::ObjectID>(tile.objid),
			static_cast<std::uint8_t>(tile.n / 3),
			static_cast<std::uint8_t>(tile.n % e)
		}
	);
}


static void load_monster(pk::ECS* ecs, const pk::tile_t& tile, char* imagepath) {

}


static void load_gameobj(pk::ECS* ecs, const pk::tile_t& tile, char* imagepath) {
	const pk::entity_t e = ecs->sprite_create(tile.zindex, imagepath, tile.x, tile.y);	
	float w, h;
	switch (tile.objid) {
		case pk::BuildingID:
			w = tile.width * 0.8f;
			h = tile.height * 0.8f;
			ecs->add_collision(
				tile.x + tile.width / 2.0f - w / 2.0f,
				tile.y + tile.height - h,
				w,
				h
			);
			break;
		case pk::TileCollisionID:
			ecs->add_collision(
				tile.x + tile.width / 2.0f - pk::TILE_SIZE * 0.4f,
				tile.y + tile.height - pk::TILE_SIZE * 0.8f,
				pk::TILE_SIZE * 0.6f,
				pk::TILE_SIZE * 0.6f
			);
			break;
		default:
			break;
	}
}


static void load_water(pk::ECS* ecs, const pk::tile_t& tile) {
	const pk::entity_t e = ecs->entity_create(tile.zindex, true);
	ecs->get_transform(e)->rect = { tile.x, tile.y, tile.width, tile.height };
	ecs->component_insert<pk::water_t>(
		e, 
		pk::water_t{ 
			static_cast<std::uint8_t>(tile.height / pk::TILE_SIZE),
			static_cast<std::uint8_t>(tile.width / pk::TILE_SIZE)
		}
	);
}


void pk::tiledmap_load(const pk::SceneID scene_id) {
	assert(ecs_has_instance(scene_id));
	pk::ECS* ecs = pk::ecs_get(scene_id);
	std::ifstream file(pk::MAP_INFO[scene_id].file);

	if (file.is_open() == false) {
		printf("[ERROR] [FILE OPEN] [scene -> %s\n]", pk::MAP_INFO[scene_id].name);
		return;
	}

	ecs->sprite_create(0, pk::MAP_INFO[scene_id].terrain_image);

	pk::tile_t tile{};
	int groupid, n;
	char imagepath[256];	
	while (!file.eof()) {
		file >> groupid >> n;
		for (int i = 0; i < n; i++) {
			file >> tile.x >> tile.y >> tile.width >> tile.height >> tile.objid >> tile.zindex >> tile.terrain >> tile.n >> tile.direction;
			file >> imagepath;						
			switch (groupid) {
				case EntitiesGroupID:
					load_entity(ecs, tile);
					break;
				case CollisionGroupID:
					load_collision(ecs, tile);
					break;
				case TransitionGroupID:
					load_transition(ecs, tile);
					break;
				case CoastGroupID:
					load_coast(ecs, tile);
					break;
				case MonsterGroupID:
					load_monster(ecs, tile, imagepath);
					break;
				case GameObjsID:
					load_gameobj(ecs, tile, imagepath);
					break;
				case WaterGroupID:
					load_water(ecs, tile);
					break;
				default:
					break;
			}
		}
	}	

	file.close();
}