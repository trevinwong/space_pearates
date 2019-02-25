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

  void draw();
  int resource_count = 0;
  int enemy_count = 0;

private:
  HUD();
  Text text;
};

#endif