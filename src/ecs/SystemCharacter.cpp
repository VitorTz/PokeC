#include "System.h"
#include "EcsManager.h"


void pk::CharacterSystem::update([[maybe_unused]] const float dt) {
	pk::ECS* ecs = pk::ecs_get();
	for (const pk::entity_t e : this->entities) {
		pk::character_t* character = ecs->component_get<character_t>(e);
		pk::sprite_animation_t* sprite_animation = ecs->component_get<pk::sprite_animation_t>(e);
		if (
			character->last_is_idle != character->is_idle ||
			character->last_direction != character->direction
			) {
			sprite_animation->index = 1;
			sprite_animation->frame = 0;
			sprite_animation->rect.x = pk::PLAYER_SIZE;
		}
		if (character->is_idle) {
			sprite_animation->rect.x = 0;
		}
		switch (character->direction) {
			case 'd':
				sprite_animation->rect.y = 0.0f;
				break;
			case 'l':
				sprite_animation->rect.y = pk::PLAYER_SIZE;
				break;
			case 'r':
				sprite_animation->rect.y = pk::PLAYER_SIZE * 2.0f;
				break;
			case 'u':
				sprite_animation->rect.y = pk::PLAYER_SIZE * 3.0f;
				break;
			default:
				break;
		}
	}
}


void pk::CharacterSystem::draw([[maybe_unused]] const pk::entity_t e) {

}