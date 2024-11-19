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

	// Window
	constexpr float SCREEN_W{ 1280.0f };
	constexpr float SCREEN_H{ 720.0f };
	constexpr float SCREEN_CENTERX{ pk::SCREEN_W / 2.0f };
	constexpr float SCREEN_CENTERY{ pk::SCREEN_H / 2.0f };
	constexpr Vector2 SCREEN_SIZE{ pk::SCREEN_W, pk::SCREEN_H };
	constexpr Vector2 SCREEN_CENTER{ pk::SCREEN_CENTERX, pk::SCREEN_CENTERY };
	constexpr char WINDOW_TITLE[]{ "PokemonCPP" };
	constexpr int FPS{ 60 };

	// Game
	constexpr pk::entity_t MAX_ENTITIES{ 4096 };
	constexpr pk::SceneID MAIN_SCENE{ pk::WorldSceneID };
	constexpr float TILE_SIZE{ 64.0f };
	constexpr bool DEBUG_MODE{ true };

	// Keys
	constexpr int LEFT_KEY{ KEY_A };
	constexpr int RIGHT_KEY{ KEY_D };
	constexpr int UP_KEY{ KEY_W };
	constexpr int DOWN_KEY{ KEY_S };
	constexpr int ACTION_KEY{ KEY_F };

	// Player
	constexpr float PLAYER_SPEED{ 150.0f };
	constexpr float PLAYER_SIZE{ 128.0f };
	constexpr Vector2 PLAYER_COLLISION_BOX{pk::TILE_SIZE * 0.7f, pk::TILE_SIZE * 0.7f };
	constexpr Vector2 PLAYER_ACTION_BOX{ pk::TILE_SIZE * 1.8f, pk::TILE_SIZE};

	// Animation
	constexpr std::uint8_t ANIMATION_SLOW{ 16 };
	constexpr std::uint8_t ANIMATION_NORMAL{ 8 };
	constexpr std::uint8_t ANIMATION_FAST{ 4 };
	constexpr std::uint8_t ANIMATION_WATER_SPEED{ pk::ANIMATION_SLOW };

	// Camera
	constexpr pk::zindex_t CAMERA_ZINDEX_MIN{ 0 };
	constexpr pk::zindex_t CAMERA_ZINDEX_TERRAIN{ 0 };
	constexpr pk::zindex_t CAMERA_ZINDEX_WATER{ 1 };
	constexpr pk::zindex_t CAMERA_ZINDEX_SHADOW{ 2 };
	constexpr pk::zindex_t CAMERA_ZINDEX_OBJECTS{ 3 };
	constexpr pk::zindex_t CAMERA_ZINDEX_TOP{ 4 };
	constexpr pk::zindex_t CAMERA_ZINDEX_SKY{ 5 };
	constexpr pk::zindex_t CAMERA_ZINDEX_MAX{ 5 };



}