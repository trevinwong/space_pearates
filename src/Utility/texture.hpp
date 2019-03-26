#ifndef TEXTURE_H
#define TEXTURE_H

#include "Utility/utility.hpp"

/* Utility class to load images, generate and bind textures.
 * Holds the format and the configuration of the texture as well.
 *
 * Code modified from LearnOpenGL: https://learnopengl.com/In-Practice/2D-Game/Setting-up
 */

class Texture
{
public:
  // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture.
  GLuint ID;
  // Texture image dimensions.
  GLuint width, height; // Width and height of loaded image in pixels.
  // Texture format.
  GLuint internalFormat; // Format of texture object.
  GLuint imageFormat; // Format of loaded image.
  // Texture configuration.
  GLuint wrapS; // Wrapping mode on S axis.
  GLuint wrapT; // Wrapping mode on T axis.
  GLuint filterMin; // Filtering mode if texture pixels < screen pixels.
  GLuint filterMax; // Filtering mode if texture pixels > screen pixels.
  // Constructor (generates ID, loads image and sets default texture modes).
  Texture(const GLchar *file, GLboolean alpha);
  // Constructor for placeholder texture (white 1x1 box)
  Texture();
  ~Texture();
  // Generates texture from image data.
  void generate(unsigned char* data);
  // Binds the texture as the current active GL_TEXTURE_2D texture object.
  void bind() const;
};

#endif


