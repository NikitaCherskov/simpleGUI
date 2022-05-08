#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Point;
float getLenth(Point first, Point second);
float getLenth(Point relative_point);
float getAngle(Point relative_point);
void drawLine(Point first, Point second, Color colorizing, RenderTarget* target);


class Point
{
public:
	Point();
	Point(const Point& pnt);
	Point(const float nx, const float ny);
	Point(const Vector2f vec);
	Point(const Vector2i vec);
	~Point();
	Point operator=(const Point rhs);
	Point operator=(const Vector2f rhs);
	Point operator+(const Point rhs);
	Point operator-(const Point rhs);
	Point operator/(const float rhs);
	Point operator*(const float rhs);
	Point operator+=(const Point rhs);
	Point operator-=(const Point rhs);
	Point operator/=(const float rhs);
	Point operator*=(const float rhs);
	float x;
	float y;
};