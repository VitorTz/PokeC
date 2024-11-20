#include "Camera.h"
#include <cassert>
#include <algorithm>
#include "../util/TiledMap.h"


pk::Camera::Camera(
	const pk::SceneID scene_id
) : max_x(pk::MAP_INFO[scene_id].width - pk::SCREEN_CENTERX),
	max_y(pk::MAP_INFO[scene_id].height - pk::SCREEN_CENTERY) { }


void pk::Camera::begin_drawing() const {
	BeginMode2D(this->camera);
}


void pk::Camera::end_drawing() {
	EndMode2D();
}


void pk::Camera::insert(const pk::entity_t e, const pk::zindex_t zindex) {
	assert(zindex <= pk::CAMERA_ZINDEX_MAX);
	if (this->on_camera[e] == false) {
		if (this->zindex_to_entities.find(zindex) == this->zindex_to_entities.end()) {
			this->zindex_to_entities[zindex].reserve(pk::MAX_ENTITIES / 4);			
		}
		this->on_camera[e] = true;
		this->zindex_to_entities[zindex].push_back({ 0.0f, e });
		this->m_size++;
	}
}


void pk::Camera::erase(const pk::entity_t e, const pk::zindex_t zindex) {
	assert(zindex <= pk::CAMERA_ZINDEX_MAX);
	if (this->on_camera[e] == true) {
		this->on_camera[e] = false;
		std::vector<std::pair<float, pk::entity_t>>& v = this->zindex_to_entities[zindex];
		for (std::size_t i = 0; i < v.size(); i++) {
			if (v[i].second == e) {
				std::swap(v[i], v.back());
				v.pop_back();
				this->m_size--;
				return;
			}
		}
	}
}


void pk::Camera::set_target(const float x, const float y) {
	this->camera.target.x = std::clamp(x, pk::SCREEN_CENTERX, this->max_x);
	this->camera.target.y = std::clamp(y, pk::SCREEN_CENTERY, this->max_y);
}


void pk::Camera::draw(pk::SystemManager* system_manager, pk::ComponentManager* component_manager) {
	this->begin_drawing();
	for (auto& pair : this->zindex_to_entities) {
		for (auto& pair1 : pair.second) {
			const pk::transform_t* transform = component_manager->at<pk::transform_t>(pair1.second);
			pair1.first = transform->rect.y + transform->rect.height / 2.0f;
		}
		std::sort(pair.second.begin(), pair.second.end());
		system_manager->draw(pair.second);
	}
	this->end_drawing();
}


const Camera2D& pk::Camera::get_camera() const {
	return this->camera;
}


void pk::Camera::clear() {
	for (auto& pair : this->zindex_to_entities)
		pair.second.clear();
	for (bool& b : this->on_camera)
		b = false;	
}


void pk::Camera::handle_zoom(const float dt) {
	this->camera.zoom = std::clamp(
		this->camera.zoom + GetMouseWheelMove() * dt * 2.0f,
		pk::CAMERA_ZOOM_MIN,
		pk::CAMERA_ZOOM_MAX
	);	
}


std::size_t pk::Camera::size() const {
	return this->m_size;
}