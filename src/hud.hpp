#ifndef HUD_H
#define HUD_H

#include "Utility/utility.hpp"
#include "Utility/text.hpp"
#include "Utility/timer.hpp"

// Singleton https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
class HUD
{
public:
  HUD(HUD const&) = delete;
  void operator=(HUD const&) = delete;
  static HUD& getInstance()
  {
    static HUD instance;
    return instance;
  }

  double play_time;
  int resource_count;
  int enemy_count;
  int wave_count;
  bool you_win;
  bool game_over;
  bool build_phase;

  string current_music_name;
  Timer current_music_fade;

  void setMusicName(string musicName);
  void reset();
  void update(float dt);
  void draw();

private:
  HUD();
};

#endif
