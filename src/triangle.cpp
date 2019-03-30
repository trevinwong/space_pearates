#include "triangle.hpp"

Triangle::Triangle(vec2 _pt1, vec2 _pt2, vec2 _pt3) 
	: pt1(_pt1), pt2(_pt2), pt3(_pt3)
{
}

bool Triangle::isIntersectingWithLine(Line line)
{
	Line edge1(pt1, pt2);
	Line edge2(pt1, pt3);
	Line edge3(pt2, pt3);

	return (line.isLineSegsIntersecting(edge1) ||
					line.isLineSegsIntersecting(edge2) ||
					line.isLineSegsIntersecting(edge3));
}

vector<vec2> Triangle::getIntersectionWithLine(Line line)
{
	Line edge1(pt1, pt2);
	Line edge2(pt1, pt3);
	Line edge3(pt2, pt3);

	return vector<vec2>{pt1, pt2, pt3};

	/*
	if (line.isLineSegsIntersecting(edge1)) return line.getLineSegsIntersection(edge1);
	if (line.isLineSegsIntersecting(edge2)) return line.getLineSegsIntersection(edge2);
	if (line.isLineSegsIntersecting(edge3)) return line.getLineSegsIntersection(edge3);
	*/
}
