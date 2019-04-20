#include "animated_component.hpp"

AnimatedComponent::AnimatedComponent(int _numFrames, float _frameRate)
  : numFrames(_numFrames), frameRate(_frameRate)
{
}

int AnimatedComponent::getCurrFrame() {
  return currFrame;
}

void AnimatedComponent::updateCurrFrame() {
    currFrame = (currFrame + 1) % numFrames;
}
