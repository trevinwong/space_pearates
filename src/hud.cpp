#include "hud.hpp"

HUD::HUD()
{
  // Pre-load font characters to be used
  text.setProjectionSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  text.preprocessGlyphs();
}

void HUD::draw()
{
  text.render("Time:", vec2(20.0f, 60.0f));

  double time = round(glfwGetTime()* 10.0) / 10.0;
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << time;
  string strTime = stream.str();
  text.render(strTime, vec2(200.0f, 60.0f));

  text.render("Coins:", vec2(1000.0f, 60.0f));
  text.render(std::to_string(resource_count), vec2(1200.0f, 60.0f));
}
