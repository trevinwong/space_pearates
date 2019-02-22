#ifndef ANIMATED_COMPONENT_H
#define ANIMATED_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class AnimatedComponent : public BaseComponent
{
public:
  AnimatedComponent(glm::vec2 _spriteDims, int _numFrames, float _frameRate);
  ~AnimatedComponent();
  static const int typeID = ComponentType::animated;
  inline virtual int getTypeID() const { return typeID; };

  int getCurrFrame();
  void updateCurrFrame();

  int currFrame = 0;
  int numFrames;
  float frameRate;
  glm::vec2 spriteDims;
};

#endif