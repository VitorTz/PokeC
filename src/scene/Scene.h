#pragma once
#include "../util/types.h"


namespace pk {


	class Scene {
	public:
		virtual ~Scene() = default;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
	};

	class TitleScreen : public pk::Scene {
	public:
		TitleScreen();
		void update(float dt) override;
		void draw() override;
	};

	class WorldScene : public pk::Scene {
	public:
		WorldScene();
		void update(float dt) override;
		void draw() override;
	};

	class FireArenaScene : public pk::Scene {
	public:
		FireArenaScene();
		void update(float dt) override;
		void draw() override;
	};

	class PlantArenaScene : public pk::Scene {
	public:
		PlantArenaScene();
		void update(float dt) override;
		void draw() override;
	};

	class WaterArenaScene : public pk::Scene {
	public:
		WaterArenaScene();
		void update(float dt) override;
		void draw() override;
	};

	class HospitalScene : public pk::Scene {
	public:
		HospitalScene();
		void update(float dt) override;
		void draw() override;
	};

	class PlayerHouseScene : public pk::Scene {
	public:
		PlayerHouseScene();
		void update(float dt) override;
		void draw() override;
	};

	class TestScene : public pk::Scene {
	public:
		TestScene();
		void update(float dt) override;
		void draw() override;
	};

	void scene_init();
	void scene_change(pk::SceneID scene_d);
	void scene_update(float dt);
	void scene_draw();

}