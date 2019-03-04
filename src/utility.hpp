#ifndef UTILITY_H
#define UTILITY_H

/*
 * This is a general utility header/class. Include this in other header files.
 * It includes all relevant libraries we need for OpenGL and useful functions.
 */

// stdlib
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <bitset>
#include <utility>
#include <climits>
#include <iomanip>

using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::cout;
using std::endl;
using std::make_unique;
using std::make_shared;
using std::unique_ptr;
using std::shared_ptr;
using std::bitset;
using std::pair;
using std::make_pair;

// libraries
// gl3w-single-file: https://github.com/gingerBill/gl3w-Single-File
#include <gl3w.h> // function pointers
#include <GLFW/glfw3.h> // windowing and input
#include <glm/glm.hpp> // math
#include <glm/gtc/type_ptr.hpp>	// get addresses from glm vectors or matrices
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL // allow printing out of glm
#include "glm/gtx/string_cast.hpp" // use glm::to_string() to print out vectors/matrices

using glm::vec2;
using glm::vec3;
using glm::to_string;
using glm::distance;
using glm::sqrt;
using glm::exp;
using glm::abs;
using glm::pow;

// printing functions
template <typename T>
void printScalar(string name, T scalar)
{
	cout << name << ": " << scalar << endl;
}

void printVec2(string name, vec2 vec);
void printVec3(string name, vec3 vec);

#define SDL_MAIN_HANDLED // otherwise windows system cannot find entry point
#include <SDL.h>
#include <SDL_mixer.h> // audio
#include <stb_image.h> // loading images

// To avoid conflicts with Windows.
#define NOMINMAX

// Utility macro, allows us to write "audiopath("audio.ogg")" instead of "data/audio/audio.ogg" for example
// This allows code to compile cleanly on all machines because each machine will have their own project directory structure.
#include "project_path.hpp" // defines PROJECT_SOURCE_DIR
#define shader_path(name) PROJECT_SOURCE_DIR "shaders/" name
#define data_path PROJECT_SOURCE_DIR "data/"
#define texture_path(name)  data_path "textures/" name
#define audio_path(name) data_path  "audio/" name
#define mesh_path(name) data_path  "meshes/" name
#define map_path(name) data_path  "map/" name
#define font_path(name) data_path  "fonts/" name
#define waveset_path(name) data_path  "waveSet/" name
#define wave_path(name) data_path  "waveSet/wave/" name
#define cluster_path(name) data_path  "waveSet/wave/cluster/" name

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#define MAP_EMPTY_BLOCK '0'
#define MAP_PLATFORM_TILE 'B'   // B -> Block
#define MAP_TOWER_POSITION 'T'  // T -> Tower build position
#define MAP_BASE_POSITION 'H'   // H -> Home
#define MAP_PLAYER_SPAWN 'P'   // P -> Player (should only have 1)


// tower types
#define TOWER_ID int
#define NO_TOWER_BUILD_HERE -1
#define FIRE_TOWER 'F'
#define LIGHT_TOWER 'L'

// build tower ui interface types
#define BUILD_TOWER_UI_BUTTON_TYPE char
#define BUILD_FIRE_TOWER 'F'
#define BUILD_LIGHT_TOWER 'L'
#define BUILD_STAR_TOWER 'R'
#define SELL_TOWER_OPERATION 'S'
#define UPGRADE_TOWER_OPERATION 'U'
#define FIX_TOWER_OPERATION 'X'

#endif
