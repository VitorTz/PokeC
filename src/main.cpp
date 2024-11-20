#include "scene/Scene.h"
#include "constants.h"
#include "util/TiledMap.h"
#include "util/TexturePool.h"


#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif


static void update_frame() {
    pk::scene_update(GetFrameTime());
    BeginDrawing();
    ClearBackground(BLACK);
    pk::scene_draw();
    EndDrawing();
}


int main(int* argc, char** argv) {
    InitWindow(static_cast<int>(pk::SCREEN_W), static_cast<int>(pk::SCREEN_H), pk::WINDOW_TITLE);
        
    pk::scene_init();

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(update_frame, 60, 1);
    #else
        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            update_frame();
        }
    #endif

    pk::texture_pool_clear();
    CloseWindow();
	return 0;
}