#ifndef LINE_H
#define LINE_H

#include "Utility/utility.hpp"

class Line {
	public:
		vec2 pt1;
		vec2 pt2;
		Line(vec2 Pt1, vec2 Pt2);	
		bool isPointWithinSegment(vec2 pt);
		vec2 getLineSegsIntersection(Line other);
};

#endif
