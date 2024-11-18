#include "System.h"
#include "EcsManager.h"
#include <raymath.h>
#include "../scene/Scene.h"


void pk::PlayerSystem::update([[maybe_unused]] const float dt) {
	pk::ECS* ecs = pk::ecs_get();
	for (const pk::entity_t e : this->entities) {
		pk::player_t* player = ecs->component_get<pk::player_t>(e);
		pk::sprite_animation_t* sprite_animation = ecs->component_get<pk::sprite_animation_t>(e);
		pk::character_t* character = ecs->component_get<pk::character_t>(e);
		pk::transform_t* player_transform = ecs->get_transform(e);
		pk::transform_t* shadow_transform = ecs->get_transform(player->shadow_entity);

		// Movement
			character->last_is_idle = character->is_idle;
			character->last_direction = character->direction;
			character->is_idle = true;
			Vector2 d{ 0.0f, 0.0f };
		
			if (IsKeyDown(pk::UP_KEY)) {
				d.y = -1.0f;
				character->direction = 'u';
				character->is_idle = false;
			}
			else if (IsKeyDown(pk::DOWN_KEY)) {
				d.y = 1.0f;
				character->direction = 'd';
				character->is_idle = false;
			}

			if (IsKeyDown(pk::LEFT_KEY)) {
				d.x = -1.0f;
				character->direction = 'l';
				character->is_idle = false;
			}
			else if (IsKeyDown(pk::RIGHT_KEY)) {
				d.x = 1.0f;
				character->direction = 'r';
				character->is_idle = false;
			}

			d = Vector2Normalize(d);

			// Horizontal Movement
			player_transform->rect.x += d.x * dt * pk::PLAYER_SPEED;					
			player->collision_box = {
				player_transform->rect.x + player_transform->rect.width / 2.0f - pk::PLAYER_COLLISION_BOX.x / 2.0f,
				player_transform->rect.y + player_transform->rect.height - pk::PLAYER_COLLISION_BOX.y,
				pk::PLAYER_COLLISION_BOX.x,
				pk::PLAYER_COLLISION_BOX.y
			};
			if (ecs->check_collision(player->collision_box)) {
				player_transform->rect.x -= d.x * dt * pk::PLAYER_SPEED;
			}
			// Vertical Movement
			player_transform->rect.y += d.y * dt * pk::PLAYER_SPEED;
			player->collision_box = {
				player_transform->rect.x + player_transform->rect.width / 2.0f - pk::PLAYER_COLLISION_BOX.x / 2.0f,
				player_transform->rect.y + player_transform->rect.height - pk::PLAYER_COLLISION_BOX.y,
				pk::PLAYER_COLLISION_BOX.x,
				pk::PLAYER_COLLISION_BOX.y
			};
			if (ecs->check_collision(player->collision_box)) {
				player_transform->rect.y -= d.y * dt * pk::PLAYER_SPEED;
			}

		// Camera
			ecs->set_camera_target(
				player_transform->rect.x + player_transform->rect.width / 2.0f,
				player_transform->rect.y + player_transform->rect.height / 2.0f
			);
		
		//	Action Box
			switch (character->direction) {
				case 'd':
					player->action_box.x = player_transform->rect.x + player_transform->rect.width / 2.0f - pk::PLAYER_ACTION_BOX.y / 2.0f;
					player->action_box.y = player_transform->rect.y + pk::PLAYER_ACTION_BOX.x - 20.0f;
					player->action_box.width = pk::PLAYER_ACTION_BOX.y;
					player->action_box.height = pk::PLAYER_ACTION_BOX.x;
					break;
				case 'l':
					player->action_box.x = player_transform->rect.x + player_transform->rect.width / 2.0f - pk::PLAYER_ACTION_BOX.x;
					player->action_box.y = player_transform->rect.y + player_transform->rect.height - pk::PLAYER_ACTION_BOX.y;
					player->action_box.width = pk::PLAYER_ACTION_BOX.x;
					player->action_box.height = pk::PLAYER_ACTION_BOX.y;
;					break;
				case 'r':
					player->action_box.x = player_transform->rect.x + player_transform->rect.width / 2.0f;
					player->action_box.y = player_transform->rect.y + player_transform->rect.height - pk::PLAYER_ACTION_BOX.y;
					player->action_box.width = pk::PLAYER_ACTION_BOX.x;
					player->action_box.height = pk::PLAYER_ACTION_BOX.y;
					break;
				case 'u':
					player->action_box.x = player_transform->rect.x + player_transform->rect.width / 2.0f - pk::PLAYER_ACTION_BOX.y / 2.0f;
					player->action_box.y = player_transform->rect.y + player_transform->rect.height / 2.0f - pk::PLAYER_ACTION_BOX.x + 20.0f;
					player->action_box.width = pk::PLAYER_ACTION_BOX.y;
					player->action_box.height = pk::PLAYER_ACTION_BOX.x;
					break;
				default:
					break;
			}

		// Transition 
			for (const pk::entity_t ee : ecs->get_entities<pk::transition_t>()) {
				pk::transition_t* transition = ecs->component_get<pk::transition_t>(ee);
				pk::transform_t* transition_transform = ecs->get_transform(ee);
				transition->is_hovered = CheckCollisionRecs(player->action_box, transition_transform->rect);
				if (transition->is_hovered && IsKeyPressed(pk::ACTION_KEY)) {
					pk::scene_change(transition->scene_id);
				}
			}

		// Sprite Animation
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


void pk::PlayerSystem::draw([[maybe_unused]] const pk::entity_t e) {

}