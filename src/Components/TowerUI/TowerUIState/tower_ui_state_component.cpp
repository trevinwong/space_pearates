#include "tower_ui_state_component.hpp"

glm::vec4 TowerUiStateComponent::computeLinearInterpolation(glm::vec4 start, glm::vec4 end)
{
  if (duration >= totalTime) return end;
  if (duration <= 0) return start;

  float t = duration / totalTime;
  glm::vec4 result = t * end + (1.0f - t) * start;
  return result;
}

vec2 TowerUiStateComponent::computeCatmullRomInterpolation(vec2 p1, vec2 p2, vec2 p3)
{
  return computeCatmullRomInterpolation(p1, p2, p3, p1);
}

vec2 TowerUiStateComponent::computeCatmullRomInterpolation(vec2 p1, vec2 p2, vec2 p3, vec2 p4)
{
  if (duration >= totalTime) return p3;
  if (duration <= 0) return p2;

  glm::mat4 mh = glm::mat4(glm::vec4(-1, 2, -1, 0), glm::vec4(1, -2, 0, 1), glm::vec4(-1, 1, 1, 0), glm::vec4(1, -1, 0, 0));

  float t = duration / totalTime;
  glm::vec4 tm = glm::vec4(t*t*t, t*t, t, 1);

  vec2 result = tm * mh * glm::transpose(glm::mat4x2(p1, p2, p3, p4));
  return result;
}
