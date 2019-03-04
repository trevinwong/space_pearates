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
  Text(string fontName);
  void preprocessGlyphs();
  void setProjectionSize(float width, float height);
  void render(string text, vec2 position, float scale=1.0f, vec3 color=vec3(1.0f, 1.0f, 1.0f));
  void render(string text, GLfloat x, GLfloat y, GLfloat scale=1.0f, vec3 color=vec3(1.0f, 1.0f, 1.0f));

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