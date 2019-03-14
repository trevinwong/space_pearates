#ifndef TEXT_H
#define TEXT_H

#include "Utility/utility.hpp"
#include "Utility/program.hpp"

// Taken from: https://learnopengl.com/In-Practice/Text-Rendering
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
  GLuint     TextureID;  // ID handle of the glyph texture
  glm::ivec2 Size;       // Size of glyph
  glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
  GLuint     Advance;    // Offset to advance to next glyph
};

// Add new fonts here and in constructor Text()

// Singleton https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class Text
{
public:
  Text(Text const&) = delete; //C++11 delete unwanted methods
  void operator=(Text const&) = delete;
  static Text& getInstance()
  {
    static Text instance;
    return instance;
  }

  void render(string text, vec2 position, float scale=1.0f, vec3 color=vec3(1.0f, 1.0f, 1.0f), int font=0);
  void render(string text, GLfloat x, GLfloat y, GLfloat scale=1.0f, vec3 color=vec3(1.0f, 1.0f, 1.0f), int font=0);
	enum Font {
		munro,
		munro_small,
		count
	};

private:
  Text();
  ~Text();

  void loadFont(string fontName, int index);
  void setProjectionSize(float width=SCREEN_WIDTH, float height=SCREEN_HEIGHT);
  void preprocessGlyphs(); // should be called once per new font load

  void loadGlyphs(int index);
  void initShaderProgram();
  void initVertexObjects();

  vector<map<GLchar, Character>> FontCharacters;
  FT_Library ft;
  FT_Face face;

  shared_ptr<Program> program;
  glm::mat4 projection;

  GLuint texture;
  GLuint VAO, VBO;
};

#endif
