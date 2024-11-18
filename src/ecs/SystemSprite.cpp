#include "System.h"
#include "EcsManager.h"


void pk::SpriteSystem::update([[maybe_unused]] const float dt) {

}


void pk::SpriteSystem::draw([[maybe_unused]] const pk::entity_t e) {
	pk::ECS* ecs = pk::ecs_get();
	const pk::sprite_t* s = ecs->component_get<pk::sprite_t>(e);
	const pk::transform_t* t = ecs->get_transform(e);
	DrawTextureV(s->texture, { t->rect.x, t->rect.y }, WHITE);
}