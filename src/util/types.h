#pragma once
#include <cstdint>
#include <cstddef>


namespace pk {

	typedef std::uint32_t entity_t;
	typedef std::int8_t zindex_t;
	typedef std::size_t component_t;

	typedef struct tiled_map_info {
		const char* name{};
		const char* file{};
		const char* terrain_image{};
		float width{};
		float height{};
	} tiled_map_info_t;

	typedef struct tile {
		float x{};
		float y{};
		float width{};
		float height{};
		int objid{};
		int zindex{};
		int terrain;
		int n;
		char direction{};
	} tile_t;

	enum SceneID {
		TitleScreenID,
		WorldSceneID,
		FireArenaSceneID,
		PlantArenaSceneID,
		WaterArenaSceneID,
		HospitalSceneID,
		PlayerHouseSceneID,
		TestSceneID,
		NumScenes
	};

	enum ObjectGroupID {
		EntitiesGroupID,
		CollisionGroupID,
		TransitionGroupID,
		CoastGroupID,
		MonsterGroupID,
		GameObjsID,
		WaterGroupID
	};

	enum CharacterID {
		PlayerID,
		NurseID
	};

	enum ObjectID {		
		SpriteID,
		BuildingID,
		TileCollisionID,
		CoastSand0,
		CoastSand1,
		CoastForest0,
		CoastForest1
	};	

}
