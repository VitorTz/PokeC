#include "Scene.h"
#include "../ecs/EcsManager.h"


pk::PlantArenaScene::PlantArenaScene() {
	pk::ecs_create(pk::PlantArenaSceneID);
}


void pk::PlantArenaScene::update(const float dt) {
	pk::ecs_set(pk::PlantArenaSceneID)->update(dt);
}


void pk::PlantArenaScene::draw() {
	pk::ecs_set(pk::PlantArenaSceneID)->draw();
}