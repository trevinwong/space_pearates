#include "hud.hpp"

HUD::HUD()
{
  current_music_fade = Timer(3);
  reset();
}

void HUD::reset()
{
  play_time = 0.0;
  resource_count = 0;
  enemy_count = 0;
  wave_count = 1;
  you_win = false;
  game_over = false;
  build_phase = true;
}

void HUD::update(float dt)
{
  current_music_fade.update(dt);
  play_time += dt;
}

void HUD::setMusicName(string musicName)
{
  current_music_name = musicName;
  current_music_fade.reset();
}

void HUD::draw()
{
  if (game_over) {
    //Text::getInstance().render("GAME OVER", vec2(0.f, 500.f), 4.5, vec3(1.f, 1.f, 0.f));
    return;
  }

  Text::getInstance().render("Wave:", vec2(20.0f, 60.0f));
  if (build_phase) {
    Text::getInstance().render("Build Phase", vec2(20.0f, 120.0f), 1.0f, vec4(0.0, 0.7, 0.3, 1.0));
  }
  else {
    Text::getInstance().render("Defense Phase", vec2(20.0f, 120.0f), 1.0f, vec4(0.8, 0.2, 0.0, 1.0));
  }

  //int time = round(play_time* 10.0) / 10.0;
  //std::stringstream stream;
  //stream << std::fixed << std::setprecision(2) << time;
  //string strTime = stream.str();
  Text::getInstance().render(std::to_string(wave_count), vec2(200.0f, 60.0f));

  Text::getInstance().render("Coins:", vec2(1000.0f, 60.0f));
  Text::getInstance().render(std::to_string(resource_count), vec2(1200.0f, 60.0f));

  Text::getInstance().render("Enemies left:", vec2(900.0f, 120.0f));
  Text::getInstance().render(std::to_string(enemy_count), vec2(1200.0f, 120.0f));

  Text::getInstance().render("Press H for help", vec2(1070.0f, 160.0f), 0.5f, vec4(0.5f, 0.5f, 0.5f, 1.0f));

  if (current_music_fade.getTimeLeft() > 0) {
    float t = 1.3 * (1.0f - current_music_fade.getParameterQuadratic());
    float p = 1.1 * (1.0f - current_music_fade.getParameterQuadratic());
    p = glm::clamp(p, 0.0f, 1.0f);
    vec2 pos = vec2(((p * 72) + ((1 - p) * 300)), 180.0f);
    vec4 color = vec4(0.9f, 0.9f, 0.3f, t);
    // Text::getInstance().render(string(1, (char) 162), pos - 50.0f, 1.0f, color, Text::Font::mod_pixel_dingbats);
    Text::getInstance().render(string("A"), vec2(pos.x - 50.f, pos.y), 0.8f, color, Text::Font::mod_pixel_dingbats);
    Text::getInstance().render(current_music_name, pos, 0.7f, color);
  }

  //if (you_win) Text::getInstance().render("YOU WIN!", vec2(400.0f, 420.0f), 3.0f);
}


