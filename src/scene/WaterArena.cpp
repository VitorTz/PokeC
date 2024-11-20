#include "Scene.h"
#include "../ecs/EcsManager.h"

pk::WaterArenaScene::WaterArenaScene() {
	pk::ecs_create(pk::WaterArenaSceneID);
}


void pk::WaterArenaScene::update(const float dt) {
	pk::ecs_set(pk::WaterArenaSceneID)->update(dt);
}


void pk::WaterArenaScene::draw() {
	pk::ecs_set(pk::WaterArenaSceneID)->draw();
}