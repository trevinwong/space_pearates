#include "animated_component.hpp"
  
AnimatedComponent::AnimatedComponent(glm::vec2 _spriteDims, int _numFrames, float _frameRate) 
: spriteDims(_spriteDims), numFrames(_numFrames), frameRate(_frameRate) 
{ 
}

int AnimatedComponent::getCurrFrame() {
    return currFrame;
}

void AnimatedComponent::updateCurrFrame() {
    currFrame++;
}
