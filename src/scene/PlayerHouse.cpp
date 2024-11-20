#include "Scene.h"
#include "../ecs/EcsManager.h"


pk::PlayerHouseScene::PlayerHouseScene() {
	pk::ecs_create(pk::PlayerHouseSceneID);
}


void pk::PlayerHouseScene::update(const float dt) {
	pk::ecs_set(pk::PlayerHouseSceneID)->update(dt);
}


void pk::PlayerHouseScene::draw() {
	pk::ecs_set(pk::PlayerHouseSceneID)->draw();
}