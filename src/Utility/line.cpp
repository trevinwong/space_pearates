#include "Utility/line.hpp"

Line::Line(vec2 Pt1, vec2 Pt2) :
	pt1(Pt1), pt2(Pt2)
{
}

bool Line::isPointWithinSegment(vec2 pt)
{
  float minX = glm::min(pt1.x, pt2.x);
  float maxX = glm::max(pt1.x, pt2.x);
  float minY = glm::min(pt1.y, pt2.y);
  float maxY = glm::max(pt1.y, pt2.y);

  float epsilon = 1e-1;
  return pt.x >= minX - epsilon && pt.x <= maxX + epsilon && pt.y >= minY - epsilon && pt.y <= maxY + epsilon;
}

vec2 Line::getLineSegsIntersection(Line other)
{
  float a1 = pt2.y - pt1.y;
  float b1 = pt1.x - pt2.x;
  float a2 = other.pt2.y - other.pt1.y;
  float b2 = other.pt1.x - other.pt2.x;

  float c1 = a1 * pt1.x + b1 * pt1.y;
  float c2 = a2 * other.pt1.x + b2 * other.pt1.y;

  float det = a1 * b2 - a2 * b1;
  float x = (b2 * c1 - b1 * c2)/det;
  float y = (a1 * c2 - a2 * c1)/det;

	vec2 invalid = {INT_MIN, INT_MIN};

  if (det == 0 && x == 0 && y == 0) return invalid;
  if (det == 0 && x != 0 && y != 0) return invalid;

	vec2 intersection = {x, y};

  if (isPointWithinSegment(intersection) && other.isPointWithinSegment(intersection)) return intersection;

  return invalid;
}
