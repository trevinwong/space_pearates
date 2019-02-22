#include "hud.hpp"

HUD::HUD()
{
}

HUD::HUD(float width, float height)
{
  // Pre-load font characters to be used
  text.setProjectionSize(width, height);
  text.preprocessGlyphs();
}

void HUD::draw()
{
  text.render("Time:", glm::vec2(20.0f, 60.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

  double time = round(glfwGetTime()* 10.0) / 10.0;
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << time;
  string strTime = stream.str();
  text.render(strTime, glm::vec2(200.0f, 60.0f), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}
