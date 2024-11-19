#pragma once
#include "Entity.h"
#include "Component.h"
#include "System.h"
#include "Camera.h"


namespace pk {

	class ECS {
	
	private:
		std::unique_ptr<pk::EntityManager> entity{};
		std::unique_ptr<pk::ComponentManager> component{};
		std::unique_ptr<pk::SystemManager> system{};
		std::unique_ptr<pk::Camera> camera{};		
		std::vector<Rectangle> collisions{};
		std::queue<pk::entity_t> entities_to_destroy{};
		bool should_destroy_all_entities{};

	public:
		ECS() : entity(std::make_unique<pk::EntityManager>()),
				component(std::make_unique<pk::ComponentManager>()),
				system(std::make_unique<pk::SystemManager>()),
				camera(std::make_unique<pk::Camera>()) { }

		pk::entity_t entity_create(const pk::zindex_t zindex, const bool add_to_camera) {
			const pk::entity_t e = this->entity->entity_create();
			this->component->insert<pk::transform_t>(e, pk::transform_t{ zindex });
			if (add_to_camera) {
				this->camera->insert(e, zindex);
			}
			return e;
		}

		pk::entity_t entity_create(const pk::zindex_t zindex, const bool add_to_camera, const float x, const float y) {
			const pk::entity_t e = this->entity->entity_create();
			this->component->insert<pk::transform_t>(e, pk::transform_t{ zindex });
			this->get_transform(e)->rect = { x, y, 0.0f, 0.0f };
			if (add_to_camera) {
				this->camera->insert(e, zindex);
			}
			return e;
		}
		
		void entity_destroy(const pk::entity_t e) {
			this->entities_to_destroy.push(e);
		}

		void entity_destroy_all() {
			this->should_destroy_all_entities = true;
		}

		pk::entity_t sprite_create(const pk::zindex_t zindex, const char* filepath) {
			const pk::entity_t e = this->entity_create(zindex, true);
			this->component_insert<pk::sprite_t>(e, pk::sprite_t{ filepath });
			const pk::sprite_t* s = this->component_get<pk::sprite_t>(e);
			this->get_transform(e)->rect = { 
				0.0f, 
				0.0f, 
				static_cast<float>(s->texture.width), 
				static_cast<float>(s->texture.height) 
			};
			return e;
		}

		pk::entity_t sprite_create(const pk::zindex_t zindex, const char* filepath, const float x, const float y) {
			const pk::entity_t e = this->entity_create(zindex, true);
			this->component_insert<pk::sprite_t>(e, pk::sprite_t{ filepath });
			pk::sprite_t* s = this->component_get<pk::sprite_t>(e);
			this->get_transform(e)->rect = { x, y, static_cast<float>(s->texture.width), static_cast<float>(s->texture.height) };			
			return e;
		}

		pk::entity_t player_create(const float x, const float y) {
			const pk::entity_t e = this->entity_create(pk::CAMERA_ZINDEX_OBJECTS, true);
			const pk::entity_t shadow_entity = this->sprite_create(pk::CAMERA_ZINDEX_SHADOW, GRAPHICS_PATH "other/shadow.png");
			this->component_insert<pk::player_t>(e, pk::player_t{ e, shadow_entity });
			this->component_insert<pk::sprite_animation>(e, pk::sprite_animation_t{CHARACTERS_PATH "player.png", pk::PLAYER_SIZE, pk::PLAYER_SIZE, pk::ANIMATION_NORMAL});
			this->component_insert<pk::character_t>(e, pk::character_t{ pk::PlayerID });
			this->get_transform(e)->rect = { x, y, pk::PLAYER_SIZE, pk::PLAYER_SIZE };
			return e;
		}

		pk::transform_t* get_transform(const pk::entity_t e) {
			return this->component->at<pk::transform_t>(e);
		}

		void add_collision(const float x, const float y, const float width, const float height) {
			this->collisions.push_back(Rectangle{ x, y, width, height });
		}

		void add_collision_to_entity(const pk::entity_t e, const float width, const float height) {
			pk::transform_t* t = this->get_transform(e);
			this->collisions.push_back(
				Rectangle{
					t->rect.x + t->rect.width / 2.0f - width / 2.0f,
					t->rect.y + t->rect.height - height,
					width,
					height
				}
			);
		}

		bool check_collision(const Rectangle& rect) {
			return std::any_of(
				this->collisions.begin(),
				this->collisions.end(),
				[rect](const Rectangle& other) {
					return CheckCollisionRecs(rect, other);
				}
			);
		}

		void add_transition(const pk::SceneID scene_id, const Rectangle& box) {
			const pk::entity_t e = this->entity_create(pk::CAMERA_ZINDEX_MAX, true);
			this->component_insert<pk::transition_t>(e, pk::transition_t{ scene_id });
			this->get_transform(e)->rect = box;
		}

		template<typename T>
		void component_insert(const pk::entity_t e, const T c) {
			this->component->insert<T>(e, std::move(c));
			this->system->insert<T>(e);
		}

		template<typename T>
		T* component_get(const pk::entity_t e) {
			return this->component->at<T>(e);
		}

		void update(const float dt) {
			this->system->update(dt);

			if (this->should_destroy_all_entities) {
				this->should_destroy_all_entities = false;
				this->entity->clear();
				this->system->clear();
				this->camera->clear();
				this->entities_to_destroy = std::queue<pk::entity_t>();
			}

			while (this->entities_to_destroy.empty() == false) {
				const pk::entity_t e = this->entities_to_destroy.front();
				this->camera->erase(e, this->get_transform(e)->zindex);
				this->entities_to_destroy.pop();
				this->entity->entity_destroy(e);
				this->system->entity_destroy(e);
			}

			if (pk::DEBUG_MODE) {				
				this->camera->handle_zoom(dt);
			}
		}

		void draw() {
			this->camera->draw(this->system.get(), this->component.get());

			if (pk::DEBUG_MODE) {
				this->camera->begin_drawing();
					for (const Rectangle& rect : this->collisions) {
						DrawRectangleLinesEx(rect, 2.0f, BLUE);
					}
					for (const pk::entity_t e : this->system->get_entities<pk::player_t>()) {
						const pk::player_t* player = this->component_get<pk::player_t>(e);
						DrawRectangleLinesEx(player->collision_box, 2.0f, RED);
						DrawRectangleLinesEx(player->action_box, 2.0f, GREEN);
					}
				this->camera->end_drawing();
				DrawFPS(20, 20);
			}
		}		
	
		template<typename T>
		const std::unordered_set<pk::entity_t>& get_entities() {
			return this->system->get_entities<T>();
		}

		const Camera2D& get_camera() const {
			return this->camera->get_camera();
		}

		void set_camera_target(const float x, const float y) {
			this->camera->set_target(x, y);
		}

	};

}