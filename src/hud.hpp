#ifndef HUD_H
#define HUD_H

#include "utility.hpp"
#include "text.hpp"

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
	bool you_win;
  bool game_over;
	bool build_phase;

  void reset();
  void update(float dt);
  void draw();

private:
  HUD();
  Text text;
};

#endif
