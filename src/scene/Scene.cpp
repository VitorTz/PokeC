#include "Scene.h"
#include <memory>
#include "../constants.h"


static std::unique_ptr<pk::Scene> scene{};
static pk::SceneID current_scene_id{ pk::MAIN_SCENE };
static pk::SceneID next_scene_id{ pk::MAIN_SCENE };
static bool should_change_scene{};

static void scene_load_next_scene();


void pk::scene_init() {
	scene_load_next_scene();
}


void scene_load_next_scene() {
	switch (next_scene_id) {
	case pk::TitleScreenID:
		scene = std::make_unique<pk::TitleScreen>();
		break;
	case pk::WorldSceneID:
		scene = std::make_unique<pk::WorldScene>();
		break;
	case pk::FireArenaSceneID:
		scene = std::make_unique<pk::FireArenaScene>();
		break;
	case pk::PlantArenaSceneID:
		scene = std::make_unique<pk::PlantArenaScene>();
		break;
	case pk::WaterArenaSceneID:
		scene = std::make_unique<pk::WaterArenaScene>();
		break;
	case pk::HospitalSceneID:
		scene = std::make_unique<pk::HospitalScene>();
		break;
	case pk::PlayerHouseSceneID:
		scene = std::make_unique<pk::PlayerHouseScene>();
		break;
	case pk::TestSceneID:
		scene = std::make_unique<pk::TestScene>();
		break;
	default:
		break;
	}
	current_scene_id = next_scene_id;
}


void pk::scene_change(const pk::SceneID scene_id) {
	should_change_scene = true;
	next_scene_id = scene_id;
}


void pk::scene_update(const float dt) {
	scene->update(dt);
	if (should_change_scene) {
		should_change_scene = false;
		scene_load_next_scene();
	}
}


void pk::scene_draw() {
	scene->draw();
}