#include "System.h"
#include "../constants.h"
#include "../util/TexturePool.h"
#include "EcsManager.h"
#include <array>


static std::array<Texture2D, 4> water_texture{};
std::uint8_t frame{};
std::uint8_t index{};


pk::WaterSystem::WaterSystem() {
	water_texture[0] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/water/0.png");
	water_texture[1] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/water/1.png");
	water_texture[2] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/water/2.png");
	water_texture[3] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/water/3.png");
}


void pk::WaterSystem::update([[maybe_unused]] const float dt) {
	frame++;
	if (frame > pk::ANIMATION_WATER_SPEED) {
		frame = 0;
		index = (index + 1) % 4;
	}
}


void pk::WaterSystem::draw(const pk::entity_t e) {
	pk::ECS* ecs = pk::ecs_get();
	const pk::water_t* water = ecs->component_get<pk::water_t>(e);
	const pk::transform_t* t = ecs->get_transform(e);
	Vector2 pos{ t->rect.x, t->rect.y };
	for (std::uint8_t i = 0; i < water->rows; i++) {
		for (std::uint8_t j = 0; j < water->cols; j++) {
			DrawTextureV(water_texture[index], pos, WHITE);
			pos.x += pk::TILE_SIZE;
		}
		pos.x = t->rect.x;
		pos.y += pk::TILE_SIZE;
	}
}