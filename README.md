# CPSC 436D Team 6 Project

## Current state of the project
* Basic ECS architecture implemented. An entity is simply an ID and a collection of components. Components are simply bags of data which define the entity's attributes. Systems are the heavy lifters which have all the functionality and logic placed inside of them, who read the components of entities and determine what to do with them. Please see the existing examples as a reference.
* There is a turtle being rendered. 


## List of things to be aware of
* If you create a new file, you MUST list it explicitly in CMakeLists.txt, otherwise CMake will not re-run itself to create a new and up-to-date Make file. (i.e If you create a new shader, list it underneath SOURCE_FILES_SHADER as shaders/myshader.fs.glsl or something similar, otherwise add it to CORE_FILES)
* glm added as a new library, use it for any mathematical operations you may need. This includes using vectors or matrices, i.e glm::vec2, or glm::mat2. You can initialize them easily simply by going glm::vec2(x, y).
* We can access glm vectors/matrices by using my_vec.x or by using my_vec[0].
* Do not use absolute paths to refer to textures/shaders. Use the macros defined in utility.hpp, i.e texture_path("my_texture.png").
* On the note of textures, be wary that png's have an alpha channel. So you must specify alpha to be true when creating a texture.
* When creating a new component please update the typeID in component.hpp and number of max components.
* Include "utility.hpp" everywhere, it has all the relevant headers you need, if you need to include more headers place it in there.
* If you want to print out glm vectors/matrices, using glm::to_string(my_vec), it will automatically do the conversion for you.
* When debugging, make heavy use of glmGetError(), read here: https://learnopengl.com/In-Practice/Debugging. I will hopefully make debugging easier with a helper function. I am also using some third party debuggers, namely RenderDoc. I would highly highly recommend using a third party debugging tool.
* If getUniformLocation returns -1, this means your uniform variable is not being used, which means the compiler could have optimized it away, or you ar e referencing an invalid program ID, or you have misspelt the name of your uniform variable.


## To-do
* Re-factor world into a state.
* Investigate clockwise vs counterclockwise vertices, and culling.
* Key/error/debug callback.
* Make components easier to include, place them in their own folder to avoid bloating.
* Use smart pointers for sprite_component + entity.
* Change screen size.
* Handle removing components.



