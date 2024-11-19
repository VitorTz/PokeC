#pragma once
#include <cassert>
#include <raylib.h>
#include <unordered_map>
#include <typeinfo>
#include "../util/TexturePool.h"
#include "../constants.h"


namespace pk {

	constexpr std::size_t NUM_COMPONENTS{ 8 };

	typedef struct transform {
		Rectangle rect{};
		pk::zindex_t zindex{};
		transform() = default;
		explicit transform(const pk::zindex_t zindex) : zindex(zindex) { }
	} transform_t;

	typedef struct sprite {
		Texture2D texture{};
		sprite() = default;
		explicit sprite(const char* filepath) : texture(pk::texture_pool_get(filepath)) { }
	} sprite_t;

	typedef struct sprite_animation {
		Texture2D texture{};
		Rectangle rect{};
		std::uint8_t frame{};
		std::uint8_t max_frame{};
		std::uint8_t index{};
		std::uint8_t max_index{};
		sprite_animation() = default;
		sprite_animation(
			const char* filepath,
			const float width,
			const float height,
			const std::uint8_t speed
		) : texture(pk::texture_pool_get(filepath)),
			rect({0.0f, 0.0f, width, height}),
		    max_frame(speed),
		    max_index(texture.width / width) { }
	} sprite_animation_t;

	typedef struct character {
		pk::ObjectID id{};		
		bool last_is_idle{};
		bool is_idle{};
		char last_direction{'d'};
		char direction{'d'};
		character() = default;
		character(const pk::ObjectID id) : id(id) { }
	} character_t;

	typedef struct player {
		pk::entity_t player_entity{};
		pk::entity_t shadow_entity{};
		Rectangle collision_box{};
		Rectangle action_box{};
		player() = default;
		explicit player(
			const pk::entity_t player_entity, 
			const pk::entity_t shadow_entity
		) : player_entity(player_entity),
			shadow_entity(shadow_entity)  { }
	} player_t;

	typedef struct transition {
		pk::SceneID scene_id;
		bool is_hovered{};	
		transition() = default;
		explicit transition(const pk::SceneID scene_id) : scene_id(scene_id) { }
	} transition_t;

	typedef struct water {
		std::uint8_t rows{};
		std::uint8_t cols{};
	} water_t;

	typedef struct coast {
		pk::CoastType id{};
		std::uint8_t row{};
		std::uint8_t col{};
	} coast_t;

	class ComponentManager {

	private:
		std::unordered_map<pk::component_t, char*> component_map{};

	private:
		template<typename T>
		void register_component() {
			const pk::component_t h = typeid(T).hash_code();
			assert(this->component_map.find(h) == this->component_map.end());
			char* p = (char*)malloc(sizeof(T) * pk::MAX_ENTITIES);
			assert(p != NULL);
			this->component_map.emplace(h, p);
		}

	public:
		ComponentManager() {
			this->register_component<pk::transform_t>();
			this->register_component<pk::sprite_t>();
			this->register_component<pk::sprite_animation_t>();
			this->register_component<pk::character_t>();
			this->register_component<pk::player_t>();
			this->register_component<pk::transition_t>();
			this->register_component<pk::water_t>();
			this->register_component<pk::coast_t>();
			assert(this->component_map.size() == pk::NUM_COMPONENTS);
		}

		~ComponentManager() {
			for (auto& pair : this->component_map) {
				free(pair.second);
			}
		}

		template<typename T>
		T* at(const pk::entity_t e) {			
			return (T*)(this->component_map[typeid(T).hash_code()] + sizeof(T) * e);
		}

		template<typename T>
		void insert(const pk::entity_t e, const T c) {
			char* p = this->component_map[typeid(T).hash_code()];
			*((T*)(p + sizeof(T) * e)) = c;
		}		

	};
	

}