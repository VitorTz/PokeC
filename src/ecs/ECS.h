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
				system(std::make_unique<pk::SystemManager>()) { }

		pk::entity_t entity_create(const pk::zindex_t zindex, const bool add_to_camera) {
			const pk::entity_t e = this->entity->entity_create();
			this->component->insert<pk::transform_t>(e, pk::transform_t{ zindex });
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
			pk::sprite_t* s = this->component_get<pk::sprite_t>(e);
			pk::transform_t* t = this->get_transform(e);
			t->rect.width = s->texture.width;
			t->rect.height = s->texture.height;
			return e;
		}

		pk::entity_t sprite_create(const pk::zindex_t zindex, const char* filepath, const float x, const float y) {
			const pk::entity_t e = this->entity_create(zindex, true);
			this->component_insert<pk::sprite_t>(e, pk::sprite_t{ filepath });
			pk::sprite_t* s = this->component_get<pk::sprite_t>(e);
			this->get_transform(e)->rect = { x, y, static_cast<float>(s->texture.width), static_cast<float>(s->texture.height) };			
			return e;
		}

		pk::transform_t* get_transform(const pk::entity_t e) {
			return this->component->at<pk::transform_t>(e);
		}

		void add_collision(const float x, const float y, const float width, const float height) {
			this->collisions.emplace_back(x, y, width, height)3;
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
		}

		void draw() {
			this->camera->draw(this->system.get(), this->component.get());
		}		

	};

}