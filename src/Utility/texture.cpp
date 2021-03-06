#include "Utility/texture.hpp"

Texture::Texture(const GLchar *file, GLboolean alpha)
  : width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
  glGenTextures(1, &this->ID);
  if (alpha)
  {
    internalFormat = GL_RGBA;
    imageFormat = GL_RGBA;
  }
  int _width, _height, nrChannels;
  unsigned char* image = stbi_load(file, &_width, &_height, &nrChannels, 0);
  width = _width;
  height = _height;
  generate(image);
  stbi_image_free(image);
}

// Constructs a placeholder texture (white 1x1 box)
Texture::Texture()
{
  glGenTextures(1, &this->ID);
  GLubyte data[] = { 255, 255, 255, 255 };
  glBindTexture(GL_TEXTURE_2D, ID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // Unbind texture (for safety).
  glBindTexture(GL_TEXTURE_2D, 0);
}

// Generates the texture and its configurations for our current texture object.
void Texture::generate(unsigned char* data)
{
  // Bind texture operations to our current ID.
  glBindTexture(GL_TEXTURE_2D, ID);
  // Generate a texture using the given image data.
  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
  // Set texture wrap and filter modes for the currently bound texture object.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
  // Unbind texture (for safety).
  glBindTexture(GL_TEXTURE_2D, 0);
}

// Binds the current texture object, which will then be automatically assigned to a fragment shader's sampler.
void Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::~Texture()
{
  if (ID) glDeleteTextures(1, &ID);
}


