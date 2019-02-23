#ifndef HUD_H
#define HUD_H

#include "utility.hpp"
#include "text.hpp"

class HUD
{
public:
  HUD();
  HUD(float width, float height);
  void draw();

private:
  Text text;

};

#endif