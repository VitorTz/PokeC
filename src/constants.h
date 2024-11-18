#pragma once
#include <raylib.h>
#include "util/types.h"


#define RES "./resources/"
#define CHARACTERS_PATH "./resources/graphics/"
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
	constexpr pk::SceneID MAIN_SCENE{ pk::TitleScreenID };


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