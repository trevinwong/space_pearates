#include "resource_component.hpp"

ResourceComponent::ResourceComponent(float _maxTime) :
elapsedTime(0.0), maxTime(_maxTime)
{
}

ResourceComponent::~ResourceComponent()
{
}

void ResourceComponent::updateTimer(float dt) {
    this->elapsedTime += dt;
    //std::cout << this->elapsedTime << std::endl;
}

float ResourceComponent::checkTimer() {
    return (this->maxTime - this->elapsedTime);
}

