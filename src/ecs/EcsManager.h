#pragma once
#include "ECS.h"
#include "../util/types.h"

namespace pk {

	pk::ECS* ecs_create(pk::SceneID scene_id);

	void ecs_destroy(pk::SceneID scene_id);

	void ecs_destroy_all();

	pk::ECS* ecs_set(pk::SceneID scene_id);

	pk::ECS* ecs_get();

	pk::ECS* ecs_get(pk::SceneID scene_id);

	bool ecs_has_instance(pk::SceneID scene_id);

}