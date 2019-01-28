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

// libraries
// gl3w-single-file: https://github.com/gingerBill/gl3w-Single-File
#include <gl3w.h> // function pointers
#include <GLFW/glfw3.h> // windowing and input
#include <glm/glm.hpp> // math
#include <glm/gtc/type_ptr.hpp>	// get addresses from glm vectors or matrices	
#include <glm/gtc/matrix_transform.hpp>                                     
#define GLM_ENABLE_EXPERIMENTAL // allow printing out of glm
#include "glm/gtx/string_cast.hpp" // use glm::to_string() to print out vectors/matrices

#define SDL_MAIN_HANDLED // otherwise windows system cannot find entry point
#include <SDL.h>
#include <SDL_mixer.h> // audio
#include <stb_image.h> // loading images 

// To avoid conflicts with Windows.
#define NOMINMAX
#if defined(_WIN32) || defined(_WIN64)
  #undef RGB
#endif

// Utility macro, allows us to write "audiopath("audio.ogg")" instead of "data/audio/audio.ogg" for example
// This allows code to compile cleanly on all machines because each machine will have their own project directory structure.
#include "project_path.hpp" // defines PROJECT_SOURCE_DIR
#define shader_path(name) PROJECT_SOURCE_DIR "./shaders/" name
#define data_path PROJECT_SOURCE_DIR "./data"
#define texture_path(name)  data_path "/textures/" name
#define audio_path(name) data_path  "/audio/" name
#define mesh_path(name) data_path  "/meshes/" name

#endif
