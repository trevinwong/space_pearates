#include "text.hpp"

Text::Text()
{
  if (FT_Init_FreeType(&ft))
    cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;

  if (FT_New_Face(ft, font_path("arial.ttf"), 0, &face))
    cout << "ERROR::FREETYPE: Failed to load font" << endl;

  // Arbitrary size init. Note: set width to 0 to autoscale according to height.
  FT_Set_Pixel_Sizes(face, 0, 48);
  // Arbitrary screen size for rendering the font glyphs, not sure if changing it helps much..
  projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f); // top-left, but flipped
}

void Text::preprocessGlyphs()
{
  loadGlyphs();         // load 128 ASCII chars
  initShaderProgram();  // attach glyph shaders
  initVertexObjects();  // setup glyph VAO, VBO
}

void Text::setProjectionSize(float width, float height) {
  //projection = glm::ortho(0.0f, width, 0.0f, height);
  projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
}

void Text::initShaderProgram()
{
  program = new Program(shader_path("glyph.vert"), shader_path("glyph.frag"));
}

void Text::loadGlyphs()
{
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph 
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
      continue;
    }
    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Now store character for later use
    Character character = {
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      face->glyph->advance.x
    };
    Characters.insert(std::pair<GLchar, Character>(c, character));
  }
  //cout << "Loaded all character glyphs" << endl;
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void Text::initVertexObjects()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  // layout (location = 0)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  // layout (location = 1)
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Text::render(string text, glm::vec2 position, float scale, glm::vec3 color)
{
  render(text, GLfloat(position.x), GLfloat(position.y), GLfloat(scale), color);
}

void Text::render(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
  // Activate corresponding render state	
  program->use();
  program->setVec3("textColor", color);
  program->setMat4("projection", projection);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  // Iterate through all characters
  string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = Characters[*c];

    GLfloat xpos = x + ch.Bearing.x * scale;
    GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale * -1;

    GLfloat w = ch.Size.x * scale;
    GLfloat h = ch.Size.y * scale * -1;
    // Update VBO for each character
    GLfloat vertices[6][4] = {
      { xpos,     ypos + h,   0.0, 0.0 },
      { xpos,     ypos,       0.0, 1.0 },
      { xpos + w, ypos,       1.0, 1.0 },

      { xpos,     ypos + h,   0.0, 0.0 },
      { xpos + w, ypos,       1.0, 1.0 },
      { xpos + w, ypos + h,   1.0, 0.0 }
    };
    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}