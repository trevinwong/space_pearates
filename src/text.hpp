#ifndef TEXT_H
#define TEXT_H

#include "utility.hpp"
#include "program.hpp"

// Taken from: https://learnopengl.com/In-Practice/Text-Rendering
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
  GLuint     TextureID;  // ID handle of the glyph texture
  glm::ivec2 Size;       // Size of glyph
  glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
  GLuint     Advance;    // Offset to advance to next glyph
};

class Text
{
public:
  Text();
  void preprocessGlyphs();
  void setProjectionSize(float width, float height);
  void render(string text, glm::vec2 position, float scale, glm::vec3 color);
  void render(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

private:
  void loadGlyphs();
  void initShaderProgram();
  void initVertexObjects();

  map<GLchar, Character> Characters;
  FT_Library ft;
  FT_Face face;

  Program *program;
  glm::mat4 projection;
  GLuint VAO, VBO;
};

#endif