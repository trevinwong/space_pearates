#include "hud.hpp"

HUD::HUD()
{
  reset();
}

void HUD::reset()
{
  play_time = 0.0;
  resource_count = 0;
  enemy_count = 0;
  you_win = false; // TODO: Change this later.
  game_over = false;
  build_phase = true;
}

void HUD::update(float dt)
{
  play_time += dt;
}

void HUD::draw()
{
  if (game_over) {
    //Text::getInstance().render("GAME OVER", vec2(0.f, 500.f), 4.5, vec3(1.f, 1.f, 0.f));
    return;
  }

  Text::getInstance().render("Time:", vec2(20.0f, 60.0f));
  if (build_phase) {
    Text::getInstance().render("Build Phase", vec2(20.0f, 120.0f));
  }
  else {
    Text::getInstance().render("Defense Phase", vec2(20.0f, 120.0f));
  }

  int time = round(play_time* 10.0) / 10.0;
  //std::stringstream stream;
  //stream << std::fixed << std::setprecision(2) << time;
  //string strTime = stream.str();
  Text::getInstance().render(std::to_string(time), vec2(200.0f, 60.0f));

  Text::getInstance().render("Coins:", vec2(1000.0f, 60.0f));
  Text::getInstance().render(std::to_string(resource_count), vec2(1200.0f, 60.0f));

  Text::getInstance().render("Enemies left:", vec2(900.0f, 120.0f));
  Text::getInstance().render(std::to_string(enemy_count), vec2(1200.0f, 120.0f));

  Text::getInstance().render("Press H for help", vec2(20.f, 154.0f), 0.5f, vec3(0.5f, 0.5f, 0.5f));

  if (you_win) Text::getInstance().render("YOU WIN!", vec2(400.0f, 420.0f), 3.0f);
}


