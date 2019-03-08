#ifndef SPLINE_COMPONENT_H
#define SPLINE_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

class SplineComponent : public BaseComponent {
public:
  SplineComponent(vector<vec2> &_controlPoints, bool _allowLoop=false);

  vector<vec2> controlPoints;
  int numPoints;

  float getTime();
  void incrementTime(float dt);

  bool allowLoop;
  bool isExpired = false;

  inline virtual int getTypeID() const { return typeID; };
  static const int typeID = ComponentType::spline;

private:
  float currTime;
};

#endif
