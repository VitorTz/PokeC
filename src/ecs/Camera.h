#pragma once
#include <raylib.h>
#include <algorithm>
#include <map>
#include <array>
#include <vector>
#include "System.h"
#include "Component.h"
#include "../util/types.h"
#include "../constants.h"


namespace pk {

	class Camera {

	private:
		std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> zindex_to_entities{};
		std::array<bool, pk::MAX_ENTITIES> on_camera{};
		std::size_t m_size{};
		Camera2D camera{
			pk::SCREEN_CENTER,
			pk::SCREEN_CENTER,
			0.0f,
			1.0f
		};
		float max_x{};
		float max_y{};

	public:
		explicit Camera(pk::SceneID scene_id);

		void begin_drawing() const;

		void end_drawing();
		
		void set_target(float x, float y);

		void insert(pk::entity_t e, pk::zindex_t zindex);

		void erase(pk::entity_t e, pk::zindex_t zindex);

		void draw(pk::SystemManager* system, pk::ComponentManager* component);

		void handle_zoom(const float dt);

		void clear();

		const Camera2D& get_camera() const;
	
		std::size_t size() const;
	
	};

}