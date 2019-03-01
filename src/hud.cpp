#include "hud.hpp"

HUD::HUD()
{
  // Pre-load font characters to be used
  text.setProjectionSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  text.preprocessGlyphs();
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
    text.render("GAME OVER", vec2(0.f, 500.f), 4.5, vec3(1.f, 1.f, 0.f));
    return;
  }
  text.render("Time:", vec2(20.0f, 60.0f));
  if (build_phase) {
		text.render("Build Phase", vec2(20.0f, 120.0f));
	} else {
		text.render("Defense Phase", vec2(20.0f, 120.0f));
	}

  double time = round(play_time* 10.0) / 10.0;
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << time;
  string strTime = stream.str();
  text.render(strTime, vec2(200.0f, 60.0f));

  text.render("Coins:", vec2(1000.0f, 60.0f));
  text.render(std::to_string(resource_count), vec2(1200.0f, 60.0f));

  text.render("Enemies left:", vec2(900.0f, 120.0f));
  text.render(std::to_string(enemy_count), vec2(1200.0f, 120.0f));

  //Tutorial
  text.render("Press arrow keys to move",           vec2(190.0f, 240.0f), 0.5f, vec3(0.5f, 0.5f, 0.5f));
  text.render("Press A or D to select tower type",  vec2(190.0f, 270.0f), 0.5f, vec3(0.5f, 0.5f, 0.5f));
  text.render("Press S or Space to build towers",   vec2(190.0f, 300.0f), 0.5f, vec3(0.5f, 0.5f, 0.5f));
  text.render("Press H for some hip-per music",     vec2(190.0f, 330.0f), 0.5f, vec3(0.5f, 0.5f, 0.5f));

	if (you_win) text.render("YOU WIN!", vec2(400.0f, 400.0f), 2.0f);
}


