#include "EcsManager.h"


static std::unordered_map<pk::SceneID, std::unique_ptr<pk::ECS>> ecs_map{};
pk::ECS* ecs{ nullptr };


pk::ECS* pk::ecs_create(const pk::SceneID scene_id) {
	if (ecs_map.find(scene_id) != ecs_map.end()) {
		return;
	}
	ecs_map.emplace(scene_id, std::make_unique<pk::ECS>());	
	return ecs_map[scene_id].get();
}


void pk::ecs_destroy(const pk::SceneID scene_id) {
	ecs_map.erase(scene_id);
}


void pk::ecs_destroy_all() {
	ecs_map.clear();
}


pk::ECS* pk::ecs_set(const pk::SceneID scene_id) {
	assert(ecs_map.find(scene_id) != ecs_map.end());
	ecs = ecs_map[scene_id].get();
	return ecs;
}


pk::ECS* pk::ecs_get() {
	assert(ecs != NULL);
	return ecs;
}


pk::ECS* pk::ecs_get(const pk::SceneID scene_id) {
	assert(ecs_map.find(scene_id) != ecs_map.end());
	return ecs_map[scene_id].get();
}