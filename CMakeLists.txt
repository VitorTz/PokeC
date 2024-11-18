cmake_minimum_required(VERSION 3.22...3.30)
project(PokemonCPP)


include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

# Our Project
add_executable(${PROJECT_NAME} "src/main.cpp" "src/util/TexturePool.h" "src/util/TexturePool.cpp" "src/util/util.h" "src/util/util.cpp" "src/constants.h" "src/util/types.h" "src/scene/Scene.h" "src/scene/Scene.cpp" "src/scene/TitleScreen.cpp" "src/scene/World.cpp" "src/scene/FireArena.cpp" "src/scene/PlantArena.cpp" "src/scene/WaterArena.cpp" "src/scene/Hospital.cpp" "src/scene/PlayerHouse.cpp" "src/scene/TestScene.cpp" "src/ecs/Entity.h" "src/ecs/Entity.cpp" "src/ecs/Component.h" "src/ecs/System.h" "src/ecs/SystemTransform.cpp" "src/ecs/SystemSprite.cpp" "src/ecs/SystemSpriteAnimation.cpp" "src/ecs/ECS.h" "src/ecs/Camera.h" "src/ecs/Camera.cpp" "src/ecs/EcsManager.h" "src/ecs/EcsManager.cpp" "src/util/TiledMap.h" "src/util/TiledMap.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if ("${PLATFORM}" STREQUAL "Web")
    add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/../resources
    )
    #DEPENDS ${PROJECT_NAME}
else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    )
    #DEPENDS ${PROJECT_NAME}
endif()

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file resources)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()