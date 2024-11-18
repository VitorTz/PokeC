#include "System.h"
#include "EcsManager.h"


void pk::SpriteAnimationSystem::update([[maybe_unused]] const float dt) {
	pk::ECS* ecs = pk::ecs_get();
	for (const pk::entity_t e : this->entities) {
		pk::sprite_animation_t* s = ecs->component_get<pk::sprite_animation_t>(e);
		s->frame++;
		if (s->frame > s->max_frame) {
			s->frame = 0;
			s->index = (s->index + 1) % s->max_index;
			s->rect.x = s->rect.width * s->index;
		}
	}
}


void pk::SpriteAnimationSystem::draw(const pk::entity_t e) {
	pk::ECS* ecs = pk::ecs_get();
	const pk::sprite_animation_t* s = ecs->component_get<pk::sprite_animation_t>(e);
	const pk::transform_t* t = ecs->get_transform(e);
	DrawTextureRec(s->texture, s->rect, { t->rect.x, t->rect.y }, WHITE);
}