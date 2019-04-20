#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "Utility/utility.hpp"
#include "Utility/program.hpp"
#include "Utility/texture.hpp"
#include "Utility/audio_loader.hpp"
#include "hud.hpp"

// Singleton design pattern from https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class GameOverMenu {
public:
  GameOverMenu(GameOverMenu const&) = delete;
  void operator=(GameOverMenu const&) = delete;
  static GameOverMenu& getInstance()
  {
    static GameOverMenu instance;
    return instance;
  }

  void init();
  void reset();
  void draw(glm::mat4 projection);
  
private:
  GameOverMenu();
  ~GameOverMenu();

  GLuint VAO, VBO;
  shared_ptr<Program> program;
  glm::vec2 position = vec2(265.f, 115.f);
  glm::vec2 scale = vec2(730.f, 570.f);
  shared_ptr<Texture> lose;
  shared_ptr<Texture> win;
  bool audio_played = false;
};

#endif