#include "math.hpp"

bool Math::isCollidingWith(vec2 pos1, vec2 size1, vec2 pos2, vec2 size2)
{	
	bool overlapX = pos1.x + size1.x >= pos2.x
		&& pos2.x + size2.x >= pos1.x;

	bool overlapY = pos1.y + size1.y >= pos2.y
	&& pos2.y + size2.y >= pos1.y;

	return overlapX && overlapY;
}

