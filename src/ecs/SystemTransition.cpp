#include "System.h"
#include "EcsManager.h"
#include "../util/TiledMap.h"


void pk::TransitionSystem::update([[maybe_unused]] const float dt) {

}


void pk::TransitionSystem::draw(const pk::entity_t e) {
	pk::ECS* ecs = pk::ecs_get();
	const pk::transition_t* transition = ecs->component_get<pk::transition_t>(e);
	const pk::transform_t* transform = ecs->get_transform(e);
	if (transition->is_hovered) {
		Vector2 anchor = GetScreenToWorld2D(Vector2{ pk::SCREEN_CENTERX, pk::SCREEN_H - 50.0f }, ecs->get_camera());
		const char* txt = TextFormat("Press F to enter %s", pk::MAP_INFO[transition->scene_id].name);
		float txt_size = static_cast<float>(MeasureText(txt, 20));
		float padding = 10.0f;
		float width = padding * 3.0f + txt_size;
		float height = 64.0f;
		Rectangle background{
			anchor.x - width / 2.0f,
			anchor.y - height / 2.0f,
			width,
			height
		};
		DrawRectangleRec(background, Color{ 0, 0, 0, 180 });
		DrawText(txt, anchor.x - txt_size / 2, anchor.y - 8, 20, WHITE);
	}
}