#include "Scene.h"
#include "../ecs/EcsManager.h"


pk::WorldScene::WorldScene() {
	pk::ECS* ecs = pk::ecs_create(pk::WorldSceneID);
}


void pk::WorldScene::update(const float dt) {
	pk::ecs_set(pk::WorldSceneID)->update(dt);	
}


void pk::WorldScene::draw() {
	pk::ecs_set(pk::WorldSceneID)->draw();
}