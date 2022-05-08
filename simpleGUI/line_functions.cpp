#include "line_functions.h"

//Point
Point::Point() :
	x(0),
	y(0)
{}

Point::Point(const Point& pnt) :
	x(pnt.x),
	y(pnt.y)
{

}

Point::Point(const float nx, const float ny) :
	x(nx),
	y(ny)
{

}

Point::Point(const Vector2f vec) :
	x(vec.x),
	y(vec.y)
{

}

Point::Point(const Vector2i vec) :
	x(vec.x),
	y(vec.y)
{
}

Point::~Point()
{}

Point Point::operator=(const Point rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Point Point::operator=(const Vector2f rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Point Point::operator+(const Point rhs)
{
	Point tmp(x + rhs.x, y + rhs.y);
	return tmp;
}

Point Point::operator-(const Point rhs)
{
	Point tmp(x - rhs.x, y - rhs.y);
	return tmp;
}

Point Point::operator/(const float rhs)
{
	Point tmp(x / rhs, y / rhs);
	return tmp;
}

Point Point::operator*(const float rhs)
{
	Point tmp(x * rhs, y * rhs);
	return tmp;
}

Point Point::operator+=(const Point rhs)
{
	Point tmp(x += rhs.x, y += rhs.y);
	return tmp;
}

Point Point::operator-=(const Point rhs)
{
	Point tmp(x -= rhs.x, y -= rhs.y);
	return tmp;
}

Point Point::operator/=(const float rhs)
{
	Point tmp(x /= rhs, y /= rhs);
	return tmp;
}

Point Point::operator*=(const float rhs)
{
	Point tmp(x *= rhs, y *= rhs);
	return tmp;
}

float getLenth(Point first, Point second)
{
	double lenx, leny;
	lenx = first.x - second.x;
	leny = first.y - second.y;
	return sqrt(lenx * lenx + leny * leny);
}
float getLenth(Point relative_point)
{
	double lenx, leny;
	lenx = relative_point.x;
	leny = relative_point.y;
	return sqrt(lenx * lenx + leny * leny);
}
float getAngle(Point relative_point)
{
	const float pi = 3.14159265;
	return 90.0 - atan2(relative_point.x, relative_point.y) * 180.0 / pi;
}
void drawLine(Point first, Point second, Color colorizing, RenderTarget* target)
{
	/*
	const float pi = 3.14159265;
	float lenth;
	lenth = getLenth(first, second);
	RectangleShape drawing(Vector2f(lenth, 1.0));
	drawing.move(first.x, first.y);
	second.x -= first.x;
	second.y -= first.y;
	drawing.rotate(90.0 - atan2(second.x, second.y) * 180.0 / pi);
	drawing.setFillColor(colorizing);
	window.draw(drawing);
	*/
	Vertex v[2];
	v[0].color = colorizing;
	v[0].position.x = first.x;
	v[0].position.y = first.y;
	v[1].color = colorizing;
	v[1].position.x = second.x;
	v[1].position.y = second.y;
	target->draw(v, 2, Lines);
	return;
}