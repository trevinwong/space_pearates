cmake_minimum_required(VERSION 3.1)
project(436d)

# Set c++11
# https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()
set (CMAKE_CXX_STANDARD 14)

# nice hierarchichal structure in MSVC
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#Find OS
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(IS_OS_MAC 1)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(IS_OS_LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(IS_OS_WINDOWS 1)
else()
  message(FATAL_ERROR "OS ${CMAKE_SYSTEM_NAME} was not recognized")
endif()

# Create executable target

# Generate the shader folder location to the header
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/project_path.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/project_path.hpp")

# You can switch to use the file GLOB for simplicity but at your own risk
# file(GLOB SOURCE_FILES src/*.cpp src/*.hpp)

set(SOURCE_FILES_SHADERS
	shaders/sprite.frag
	shaders/sprite.vert
	shaders/mesh.frag
	shaders/mesh.vert
)
set(SOURCE_FILES_MAIN
	src/main.cpp
)
set(SOURCE_FILES_AUTOGEN
   	src/project_path.hpp
)
set(SOURCE_FILES_CORE
	src/EntityFactories/home_factory.cpp
	src/EntityFactories/home_factory.hpp
	src/EntityFactories/tower_entity_factory.cpp
	src/EntityFactories/tower_entity_factory.hpp
	src/EntityFactories/player_factory.cpp
	src/EntityFactories/player_factory.hpp
	src/EntityFactories/background_entity_factory.cpp
	src/EntityFactories/background_entity_factory.hpp
	src/EntityFactories/enemy_factory.cpp
	src/EntityFactories/enemy_factory.hpp
	src/EntityFactories/map_entity_factory.cpp
	src/EntityFactories/map_entity_factory.hpp
	src/EntityFactories/tower_ui_entity_factory.cpp
	src/EntityFactories/tower_ui_entity_factory.hpp
  src/EntityFactories/menu_ui_factory.cpp
  src/EntityFactories/menu_ui_factory.hpp
	src/EntityFactories/tile_factory.cpp
	src/EntityFactories/tile_factory.hpp
	src/EntityFactories/resource_factory.cpp
	src/EntityFactories/resource_factory.hpp
	src/EntityFactories/waveset_manager_factory.cpp
	src/EntityFactories/waveset_manager_factory.hpp
	src/Components/base_component.hpp
	src/EntityFactories/projectile_entity_factory.cpp
	src/EntityFactories/projectile_entity_factory.hpp
  src/EntityFactories/simple_sprite_factory.cpp
	src/EntityFactories/simple_sprite_factory.hpp
	src/EntityFactories/particle_factory.cpp
	src/EntityFactories/particle_factory.hpp
	src/Utility/math.hpp
	src/Utility/math.cpp
	src/Components/collision_component.cpp
	src/Components/collision_component.hpp
	src/Components/color_component.cpp
	src/Components/color_component.hpp
	src/Components/background_component.hpp
	src/Components/health_component.cpp
	src/Components/health_component.hpp
	src/Components/sprite_component.cpp
	src/Components/sprite_component.hpp
	src/Components/transform_component.cpp
	src/Components/transform_component.hpp
	src/Components/movement_component.cpp
	src/Components/movement_component.hpp
	src/Components/spline_component.cpp
	src/Components/spline_component.hpp
	src/Components/player_component.cpp
	src/Components/player_component.hpp
	src/Components/wallet_component.cpp
	src/Components/wallet_component.hpp
	src/Components/mesh_component.hpp
	src/Components/mesh_component.cpp
	src/Components/TowerComponents/tower_meta_component.cpp
	src/Components/TowerComponents/tower_meta_component.hpp
	src/Components/TowerComponents/tower_attack_component.cpp
	src/Components/TowerComponents/tower_attack_component.hpp
	src/Components/TowerComponents/tower_range_sprite_component.hpp
	src/Components/TowerComponents/water_tower_attack_component.cpp
	src/Components/TowerComponents/water_tower_attack_component.hpp
	src/Components/TowerComponents/water_tower_factor_component.hpp
	src/Components/TowerComponents/fire_tower_attack_component.cpp
	src/Components/TowerComponents/fire_tower_attack_component.hpp
	src/Components/TowerComponents/light_tower_attack_component.cpp
	src/Components/TowerComponents/light_tower_attack_component.hpp
	src/Components/TowerComponents/star_tower_attack_component.cpp
	src/Components/TowerComponents/star_tower_attack_component.hpp
	src/Components/TowerComponents/boomerang_tower_attack_component.cpp
	src/Components/TowerComponents/boomerang_tower_attack_component.hpp
	src/Components/TowerUI/tower_ui_button_component.cpp
	src/Components/TowerUI/tower_ui_button_component.hpp
	src/Components/TowerUI/tower_ui_button_meta_component.cpp
	src/Components/TowerUI/tower_ui_button_meta_component.hpp
	src/Components/TowerUI/TowerUIState/tower_ui_state_component.cpp
	src/Components/TowerUI/TowerUIState/tower_ui_state_component.hpp
	src/Components/TowerUI/TowerUIState/tower_ui_idle_state.cpp
	src/Components/TowerUI/TowerUIState/tower_ui_idle_state.hpp
	src/Components/TowerUI/TowerUIState/tower_ui_shift_left_state.cpp
	src/Components/TowerUI/TowerUIState/tower_ui_shift_left_state.hpp
	src/Components/TowerUI/TowerUIState/tower_ui_shift_right_state.cpp
	src/Components/TowerUI/TowerUIState/tower_ui_shift_right_state.hpp
  src/Components/MenuUI/menu_ui_component.cpp
  src/Components/MenuUI/menu_ui_component.hpp
	src/Components/projectile_component.cpp
	src/Components/projectile_component.hpp
	src/Components/tile_component.cpp
	src/Components/tile_component.hpp
	src/Components/enemy_component.cpp
	src/Components/enemy_component.hpp
  src/Components/enemy_path_component.cpp
  src/Components/enemy_path_component.hpp
	src/Components/map_component.cpp
	src/Components/map_component.hpp
	src/Components/home_component.cpp
	src/Components/home_component.hpp
	src/Components/resource_component.cpp
	src/Components/resource_component.hpp
	src/Components/animated_component.cpp
	src/Components/animated_component.hpp
	src/Components/waveset_component.cpp
	src/Components/waveset_component.hpp
	src/Components/particle_component.hpp
	src/Components/damage_component.hpp
	src/Components/damage_component.cpp
	src/Components/mesh_collision_component.hpp
	src/Components/mesh_collision_component.cpp
	src/Systems/sprite_system.cpp
	src/Systems/sprite_system.hpp
	src/Systems/background_system.cpp
	src/Systems/background_system.hpp
	src/Systems/billboard_system.cpp
	src/Systems/billboard_system.hpp
	src/Systems/collision_system.cpp
	src/Systems/collision_system.hpp
	src/Systems/death_system.hpp
	src/Systems/death_system.cpp
	src/Systems/damage_system.hpp
	src/Systems/damage_system.cpp
	src/Systems/physics_system.hpp
	src/Systems/physics_system.cpp
	src/Systems/interpolation_system.cpp
	src/Systems/interpolation_system.hpp
	src/Systems/player_system.cpp
	src/Systems/player_system.hpp
	src/Systems/tile_map_system.cpp
	src/Systems/tile_map_system.hpp
	src/Systems/tower_range_display_system.cpp
	src/Systems/tower_range_display_system.hpp
	src/Systems/tower_attack_system.cpp
	src/Systems/tower_attack_system.hpp
	src/Systems/offscreen_garbage_system.cpp
	src/Systems/offscreen_garbage_system.hpp
	src/Systems/tower_ui_system.cpp
	src/Systems/tower_ui_system.hpp
	src/Systems/render_to_texture_system.cpp
	src/Systems/render_to_texture_system.hpp
	src/Utility/timer.hpp
	src/Utility/timer.cpp
	src/Utility/waveset_structs.hpp
	src/Utility/waveset_structs.cpp
	src/Systems/menu_ui_system.cpp
	src/Systems/menu_ui_system.hpp
	src/Systems/enemy_system.cpp
	src/Systems/enemy_system.hpp
	src/Systems/waveset_system.cpp
	src/Systems/waveset_system.hpp
	src/Systems/resource_system.cpp
	src/Systems/resource_system.hpp
	src/Systems/particle_system.cpp
	src/Systems/particle_system.hpp
	src/Systems/home_system.cpp
	src/Systems/home_system.hpp
  src/Systems/state_system.hpp
  src/Systems/state_system.cpp
	src/Utility/line.hpp
	src/Utility/line.cpp
	src/Systems/mesh_system.hpp
	src/Systems/mesh_system.cpp
	src/Systems/level_assets_system.hpp
	src/Systems/level_assets_system.cpp
	src/triangle.hpp
	src/triangle.cpp
	src/Utility/timer.hpp
	src/Utility/timer.cpp
	src/Utility/waveset_structs.hpp
	src/Utility/waveset_structs.cpp
	src/entity.cpp
	src/entity.hpp
	src/entity_manager.cpp
	src/entity_manager.hpp
	src/Utility/program.cpp
	src/Utility/program.hpp
	src/Utility/texture.cpp
	src/Utility/texture.hpp
	src/Utility/utility.cpp
	src/Utility/utility.hpp
	src/Utility/text.cpp
	src/Utility/text.hpp
	src/hud.cpp
	src/hud.hpp
	src/DataLoaders/data_loading_utility.cpp
	src/DataLoaders/data_loading_utility.hpp
	src/DataLoaders/tower_data_loader.cpp
	src/DataLoaders/tower_data_loader.hpp
	src/DataLoaders/tower_structs.cpp
	src/DataLoaders/tower_structs.hpp
  src/DataLoaders/player_data_loader.cpp
  src/DataLoaders/player_data_loader.hpp
  src/DataLoaders/player_structs.cpp
  src/DataLoaders/player_structs.hpp
	src/Utility/audio_loader.cpp
	src/Utility/audio_loader.hpp
	src/help_menu.hpp
	src/help_menu.cpp
	src/game_over_menu.hpp
	src/game_over_menu.cpp
	src/Scenes/scene_manager.hpp
	src/Scenes/scene_manager.cpp
	src/Scenes/abstract_scene.hpp
	src/Scenes/main_menu_scene.cpp
	src/Scenes/main_menu_scene.hpp
  src/Scenes/level_selection_scene.cpp
	src/Scenes/level_selection_scene.hpp
  src/Scenes/tutorial_scene.cpp
	src/Scenes/tutorial_scene.hpp
	src/Scenes/how_to_play_scene.cpp
	src/Scenes/how_to_play_scene.hpp
	src/world.cpp
	src/world.hpp
  src/Scenes/loading_scene.cpp
	src/Scenes/loading_scene.hpp
)

set(SOURCE_FILES
${SOURCE_FILES_SHADERS}
${SOURCE_FILES_MAIN}
${SOURCE_FILES_AUTOGEN}
${SOURCE_FILES_CORE}
)


# Add the exectuable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC src/)

# Now add filter for files for VS
source_group(src FILES ${SOURCE_FILES_CORE})
source_group(shaders FILES ${SOURCE_FILES_SHADERS})
source_group(autogen FILES ${SOURCE_FILES_AUTOGEN})
source_group("" FILES ${SOURCE_FILES_MAIN})

# Added this so policy CMP0065 doesn't scream
set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS 0)


# External header-only libraries in the ext/
target_include_directories(${PROJECT_NAME} PUBLIC ext/stb_image/)
target_include_directories(${PROJECT_NAME} PUBLIC ext/gl3w)
target_include_directories(${PROJECT_NAME} PUBLIC ext/glm/)

# Find OpenGL
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
   target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
   target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_gl_LIBRARY})
endif()

# glfw, sdl and freetype could be precompiled (on windows) or installed by a package manager (on OSX and Linux)
set(FREETYPE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/include")


if (IS_OS_LINUX OR IS_OS_MAC)
    # Try to find packages rather than to use the precompiled ones
    # Since we're on OSX or Linux, we can just use pkgconfig.
    find_package(PkgConfig REQUIRED)
		find_package(Freetype REQUIRED)
		include_directories($(FREETYPE_INCLUDE_DIRS))
    pkg_search_module(GLFW REQURIED glfw3)
    pkg_search_module(SDL2 REQURIED sdl2)
    pkg_search_module(SDL2MIXER REQURIED SDL2_mixer)

    # Link Frameworks on OSX
    if (IS_OS_MAC)
       find_library(COCOA_LIBRARY Cocoa)
       find_library(CF_LIBRARY CoreFoundation)
       target_link_libraries(${PROJECT_NAME} PUBLIC ${COCOA_LIBRARY} ${CF_LIBRARY})
    endif()
elseif (IS_OS_WINDOWS)
# https://stackoverflow.com/questions/17126860/cmake-link-precompiled-library-depending-on-os-and-architecture
    set(GLFW_FOUND TRUE)
    set(SDL2_FOUND TRUE)
    set(FREETYPE_FOUND TRUE)

    set(GLFW_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/include")
    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/include/SDL")

    if (${CMAKE_SIZEOF_VOID_P} MATCHES "8")
        set(FREETYPE_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/win64/freetype.lib")
        set(GLFW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/lib/glfw3dll-x64.lib")
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x64.lib")
		set(SDL2MIXER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x64.lib")

		set(FREETYPE_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/win64/freetype.dll")
		set(GLFW_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/lib/glfw3-x64.dll")
		set(SDL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x64.dll")
		set(SDLMIXER_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x64.dll")
    else()
        set(FREETYPE_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/win32/freetype.lib")
        set(GLFW_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/lib/glfw3dll-x86.lib")
        set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x86.lib")
		set(SDL2MIXER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x86.lib")

		set(FREETYPE_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/freetype/win32/freetype.dll")
		set(GLFW_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/glfw/lib/glfw3-x86.dll")
		set(SDL_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2-x86.dll")
		set(SDLMIXER_DLL "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/SDL2_mixer-x86.dll")
    endif()

    # Copy and rename dlls
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${FREETYPE_DLL}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/freetype.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLFW_DLL}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/glfw3.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL_DLL}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL2.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDLMIXER_DLL}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/SDL2_mixer.dll")

	# create a list of files to copy
	set( THIRD_PARTY_DLLS
	   "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/libFLAC-8.dll"
	   "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/libmodplug-1.dll"
	   "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/libmpg123-0.dll"
	   "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/libogg-0.dll"
	   "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/libopus-0.dll"
	   "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/libopusfile-0.dll"
	   "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/libvorbis-0.dll"
	   "${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl/lib/libvorbisfile-3.dll"
	)

	# do the copying
	foreach( file_i ${THIRD_PARTY_DLLS})
		add_custom_command(
		TARGET ${PROJECT_NAME}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		ARGS -E copy ${file_i} "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
	)
	endforeach( file_i )

	# Finally get rid of msvc warnings for printf, scanf, ...
	# Also try to keep stuff from Windows.h to a minimum
    add_definitions("-DNOMINMAX")
    add_definitions("-DWIN32_LEAN_AND_MEAN")
    add_definitions("-D_SCL_SECURE_NO_WARNINGS")
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")

endif()

# Can't find the include and lib. Quit.
if (NOT GLFW_FOUND OR NOT SDL2_FOUND OR NOT FREETYPE_FOUND)
   if (NOT GLFW_FOUND)
      message(FATAL_ERROR "Can't find GLFW." )
   elseif (NOT SDL2_FOUND)
      message(FATAL_ERROR "Can't find SDL." )
   endif()
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC ${FREETYPE_LIBRARIES} ${GLFW_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2MIXER_LIBRARIES})

# Needed to add this
if(IS_OS_LINUX)
  target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_DL_LIBS})
endif()
