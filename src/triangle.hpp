#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Utility/utility.hpp"
#include "Utility/line.hpp"

class Triangle {
	public:
		vec2 pt1;
		vec2 pt2;
		vec2 pt3;
		Triangle(vec2 _pt1, vec2 _pt2, vec2 _pt3);
		bool isIntersectingWithLine(Line line);
		vector<vec2> getIntersectionWithLine(Line line);
};

#endif
