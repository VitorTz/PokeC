#pragma once
#include "types.h"
#include "../ecs/EcsManager.h"
#include "../constants.h"


namespace pk {

	typedef struct tiled_map_info {
		const char* name{};
		const char* file{};
		const char* terrain_image{};
		float width{};
		float height{};		
	} tiled_map_info_t;

	void tiledmap_init();

	const pk::tiled_map_info_t& tiledmap_get_info(pk::SceneID scene_id);

	void tiledmap_load(pk::ECS* ecs, pk::SceneID scene_id);

}