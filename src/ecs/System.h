#pragma once
#include "Component.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <typeinfo>
#include <memory>
#include "../constants.h"


namespace pk {

	class System {
	public:		
		std::unordered_set<pk::entity_t> entities{};

	public:
		virtual void update(const float dt) = 0;
		virtual void draw(const pk::entity_t e) = 0;
	};

	class TransformSystem : public pk::System {
	public:
		TransformSystem();
		void update(const float dt) override;
		void draw(const pk::entity_t e) override;
	};

	class SpriteSystem: public pk::System {
	public:
		SpriteSystem();
		void update(const float dt) override;
		void draw(const pk::entity_t e) override;
	};

	class SpriteAnimationSystem : public pk::System {
	public:
		SpriteAnimationSystem();
		void update(const float dt) override;
		void draw(const pk::entity_t e) override;
	};

	class SystemManager {

	private:
		std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> system_map{};
		std::unordered_map<pk::entity_t, std::unordered_set<pk::component_t>> entity_to_drawable_components{};
		std::unordered_set<pk::component_t> drawable_components{};
		std::vector<pk::component_t> update_order{};

	private:
		template<typename T, typename S>
		void register_component(const bool is_drawable) {
			const pk::component_t h = typeid(T).hash_code();
			assert(this->system_map.find(h) == this->system_map.end());
			this->system_map.emplace(h, std::make_unique<S>());
			if (is_drawable)
				this->drawable_components.insert(h);
		}

	public:
		SystemManager() {
			// Register Components
			this->register_component<pk::transform_t, pk::TransformSystem>(false);
			this->register_component<pk::sprite_t, pk::SpriteSystem>(true);
			this->register_component<pk::sprite_animation_t, pk::SpriteAnimationSystem>(true);
			assert(this->system_map.size() == pk::NUM_COMPONENTS);

			// Update Order
			this->update_order.push_back(typeid(pk::sprite_animation_t).hash_code());

			this->entity_to_drawable_components.reserve(pk::MAX_ENTITIES);
			for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++)
				this->entity_to_drawable_components[e].reserve(pk::NUM_COMPONENTS);
		}

		template<typename T>
		void insert(const pk::entity_t e) {
			const std::size_t h = typeid(T).hash_code();
			this->system_map[h]->entities.insert(e);
			if (this->drawable_components.find(h) != this->drawable_components.end())
				this->entity_to_drawable_components[e].insert(h);
		}
		
		void entity_destroy(const pk::entity_t e) {
			for (auto& pair : this->system_map)
				pair.second->entities.erase(e);
			this->entity_to_drawable_components[e].clear();
		}

		void update(const float dt) {
			for (const pk::component_t c : this->update_order)
				this->system_map[c]->update(dt);
		}

		void draw(const std::vector<std::pair<float, pk::entity_t>>& entities) {
			for (const auto& pair : entities)
				for (const pk::component_t c : this->entity_to_drawable_components[pair.second])
					this->system_map[c]->draw(pair.second);
		}

		void clear() {
			for (auto& pair : this->system_map)
				pair.second->entities.clear();			
			for (auto& pair : this->entity_to_drawable_components)
				pair.second.clear();
		}

		

	};

}