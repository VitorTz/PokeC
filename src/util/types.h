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

}
