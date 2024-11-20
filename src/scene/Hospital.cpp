#include "Scene.h"
#include "../ecs/EcsManager.h"


pk::HospitalScene::HospitalScene() {
	pk::ecs_create(pk::HospitalSceneID);
}


void pk::HospitalScene::update(const float dt) {
	pk::ecs_set(pk::HospitalSceneID)->update(dt);
}


void pk::HospitalScene::draw() {
	pk::ecs_set(pk::HospitalSceneID)->draw();
}