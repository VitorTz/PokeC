#include "Scene.h"
#include "../ecs/EcsManager.h"
#include "../util/TiledMap.h"


pk::FireArenaScene::FireArenaScene() {
	pk::ecs_create(pk::FireArenaSceneID);	
}


void pk::FireArenaScene::update(const float dt) {
	pk::ecs_set(pk::FireArenaSceneID)->update(dt);
}


void pk::FireArenaScene::draw() {
	pk::ecs_set(pk::FireArenaSceneID)->draw();
}