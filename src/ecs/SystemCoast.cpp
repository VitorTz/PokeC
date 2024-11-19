#include "System.h"
#include "../util/TexturePool.h"
#include "EcsManager.h"


static Texture2D COAST_FOREST[2][4];
static Texture2D COAST_SAND[2][4];
static Rectangle rect{0.0f, 0.0f, pk::TILE_SIZE, pk::TILE_SIZE};
static std::uint8_t frame{};
static std::uint8_t index{};


pk::CoastSystem::CoastSystem() {
	// Forest
	COAST_FOREST[0][0] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-0.png");
	COAST_FOREST[0][1] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-1.png");
	COAST_FOREST[0][2] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-2.png");
	COAST_FOREST[0][3] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-3.png");
	
	COAST_FOREST[1][0] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-4.png");
	COAST_FOREST[1][1] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-5.png");
	COAST_FOREST[1][2] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-6.png");
	COAST_FOREST[1][3] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/forest-7.png");

	// Coast
	COAST_SAND[0][0] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-0.png");
	COAST_SAND[0][1] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-1.png");
	COAST_SAND[0][2] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-2.png");
	COAST_SAND[0][3] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-3.png");

	COAST_SAND[1][0] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-4.png");
	COAST_SAND[1][1] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-5.png");
	COAST_SAND[1][2] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-6.png");
	COAST_SAND[1][3] = pk::texture_pool_get(GRAPHICS_PATH "tilesets/coast/sand-7.png");
}


void pk::CoastSystem::update([[maybe_unused]] const float dt) {
	frame++;
	if (frame > pk::ANIMATION_WATER_SPEED) {
		frame = 0;
		index = (index + 1) % 4;
	}
}


void pk::CoastSystem::draw(const pk::entity_t e) {
	pk::ECS* ecs = pk::ecs_get();
	const pk::coast_t* coast = ecs->component_get<pk::coast_t>(e);
	pk::transform_t* transform = ecs->get_transform(e);
	Texture t = coast->id == pk::Forest0 || coast->id == pk::Forest1 ? COAST_FOREST[coast->id - 2][index] : COAST_SAND[coast->id][index];
	rect.x = coast->col * pk::TILE_SIZE;
	rect.y = coast->row * pk::TILE_SIZE;
	DrawTextureRec(t, rect, Vector2{ transform->rect.x, transform->rect.y }, WHITE);
}