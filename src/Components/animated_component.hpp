#ifndef ANIMATED_COMPONENT_H
#define ANIMATED_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class AnimatedComponent : public BaseComponent
{
public:
  AnimatedComponent(int _numFrames, float _frameRate);
  static const int typeID = ComponentType::animated;
  inline virtual int getTypeID() const { return typeID; };

  int getCurrFrame();
  void updateCurrFrame();

  int currFrame = 0;
  int numFrames;
  float frameRate;
};

#endif