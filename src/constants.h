#pragma once
#include <raylib.h>
#include "util/types.h"


#define RES "./resources/"
#define GRAPHICS_PATH "./resources/graphics/"
#define CHARACTERS_PATH "./resources/graphics/characters/"
#define ICONS_PAT "./resources/graphics/icons/"
#define BACKGROUNDS_PATH "./resources/graphics/backgrounds/"
#define MAPS_PATH "./resources/data/maps/"


namespace pk {

	constexpr bool DEBUG_MODE{ true };

	// Window
	constexpr float SCREEN_W{ 1280.0f };
	constexpr float SCREEN_H{ 720.0f };
	constexpr float SCREEN_CENTERX{ pk::SCREEN_W / 2.0f };
	constexpr float SCREEN_CENTERY{ pk::SCREEN_H / 2.0f };
	constexpr Vector2 SCREEN_SIZE{ pk::SCREEN_W, pk::SCREEN_H };
	constexpr Vector2 SCREEN_CENTER{ pk::SCREEN_CENTERX, pk::SCREEN_CENTERY };
	constexpr char WINDOW_TITLE[]{ "PokemonCPP" };
	constexpr int FPS{ 60 };

	// Maps
	constexpr float TILE_SIZE{ 64.0f };
	constexpr pk::tiled_map_info_t MAP_INFO[pk::NumScenes] = {
		pk::tiled_map_info_t{"Title Screen", "", ""},
		pk::tiled_map_info_t{"World Map", MAPS_PATH "world.txt", MAPS_PATH "world.png", 86 * pk::TILE_SIZE, 86 * pk::TILE_SIZE},
		pk::tiled_map_info_t{"Fire Arena", MAPS_PATH "fire.txt", MAPS_PATH "fire.png", 24 * pk::TILE_SIZE, 43 * pk::TILE_SIZE},
		pk::tiled_map_info_t{"Plant Arena", MAPS_PATH "plant.txt", MAPS_PATH "plant.png", 24 * pk::TILE_SIZE, 43 * pk::TILE_SIZE},
		pk::tiled_map_info_t{"Water Arena", MAPS_PATH "water.txt", MAPS_PATH "water.png", 24 * pk::TILE_SIZE, 43 * pk::TILE_SIZE},
		pk::tiled_map_info_t{"Hospital", MAPS_PATH "hospital.txt", MAPS_PATH "hospital.png", 20 * pk::TILE_SIZE, 12 * pk::TILE_SIZE},
		pk::tiled_map_info_t{"House", MAPS_PATH "house.txt", MAPS_PATH "house.png", 20 * pk::TILE_SIZE, 12 * pk::TILE_SIZE},
		pk::tiled_map_info_t{"Test Scene", "", ""}
	};

	// Game
	constexpr pk::entity_t MAX_ENTITIES{ 4096 };
	constexpr pk::SceneID MAIN_SCENE{ pk::WorldSceneID };

	// Keys
	constexpr int LEFT_KEY{ KEY_A };
	constexpr int RIGHT_KEY{ KEY_D };
	constexpr int UP_KEY{ KEY_W };
	constexpr int DOWN_KEY{ KEY_S };
	constexpr int ACTION_KEY{ KEY_F };

	// Player
	constexpr float PLAYER_SPEED{ 150.0f };
	constexpr float PLAYER_SIZE{ 128.0f };
	constexpr Vector2 PLAYER_COLLISION_BOX{ pk::TILE_SIZE * 0.7f, pk::TILE_SIZE * 0.7f };
	constexpr Vector2 PLAYER_ACTION_BOX{ pk::TILE_SIZE * 1.8f, pk::TILE_SIZE };

	// Animation
	constexpr std::uint8_t ANIMATION_SLOW{ 16 };
	constexpr std::uint8_t ANIMATION_NORMAL{ 8 };
	constexpr std::uint8_t ANIMATION_FAST{ 4 };
	constexpr std::uint8_t ANIMATION_WATER_SPEED{ pk::ANIMATION_SLOW };

	// Camera
	constexpr float CAMERA_ZOOM_MIN{ 0.5f };
	constexpr float CAMERA_ZOOM_MAX{ 2.5f };
	constexpr pk::zindex_t CAMERA_ZINDEX_MAX{ 10 };

}