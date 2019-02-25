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

  //text.render("Enemies left:", vec2(900.0f, 120.0f));
  //text.render(std::to_string(enemy_count), vec2(1200.0f, 60.0f));

  //Tutorial
  text.render("Press arrow keys to move",           vec2(190.0f, 240.0f), 0.6f, vec3(0.5f, 0.5f, 0.5f));
  text.render("Press A or D to select tower type",  vec2(190.0f, 280.0f), 0.6f, vec3(0.5f, 0.5f, 0.5f));
  text.render("Press S or Space to build towers",   vec2(190.0f, 320.0f), 0.6f, vec3(0.5f, 0.5f, 0.5f));

	if (you_win) text.render("YOU WIN!", vec2(500.0f, 500.0f));
}


