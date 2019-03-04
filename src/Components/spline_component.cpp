#include "spline_component.hpp"

SplineComponent::SplineComponent(vector<vec2>& _controlPoints, bool _allowLoop) 
  : controlPoints(_controlPoints), allowLoop(_allowLoop), currTime(0.0f)
{
  numPoints = controlPoints.size() - 1;

  // Repeat first and last points, total 3 each
  //controlPoints = { _controlPoints[0], _controlPoints[0] };
  //for (vec2 pt : _controlPoints) {
  //  controlPoints.push_back(pt);
  //}
  //int lastIndex = _controlPoints.size()-1;
  //controlPoints.push_back(_controlPoints[lastIndex]);
  //controlPoints.push_back(_controlPoints[lastIndex]);
}

float SplineComponent::getTime()
{
  return currTime;
}

void SplineComponent::incrementTime(float dt)
{
  currTime += dt;

  if (allowLoop) {
    float remainder = currTime - numPoints;
    while (remainder > 0) {
      currTime = remainder;
      remainder = currTime - numPoints;
    }
  }
  else if(currTime > numPoints) {
    isExpired = true;
  }
}
