#pragma once
#include <cstdint>
#include <cstddef>


namespace pk {

	typedef std::uint32_t entity_t;
	typedef std::uint8_t zindex_t;
	typedef std::size_t component_t;

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

	enum ObjectID {
		FireArenaID,
		WaterArenaID,
		PlantArenaID,
		TreeID,
		RockID,
		PalmID,
		PillarID,
		PillarTopID,
		HouseID,
		HospitalID,
		PlayerID,
		NurseID		
	};

	enum CoastType {		
		Sand0,
		Sand1,
		Forest0,
		Forest1
	};

}
