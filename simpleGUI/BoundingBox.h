#pragma once
#include "line_functions.h"
class BoundingBox //������������� � BoundingBox
{
public:
	BoundingBox();
	BoundingBox(Point _position, float _width, float _height); //�������� �������� �� _lu � _rd ��������������
	~BoundingBox();
	void move(Point _offset);
	void setPosition(Point _position);
	void setCenterPosition(Point _position);
	bool contains(Point cnt);
	float getLeft();
	float getRight();
	float getUp();
	float getDown();
	float getWidth();
	float getHeight();
	Point getRu();
	Point getLu();
	Point getLd();
	Point getRd();
	Point position;
	float width;
	float height;
};
class MouseData //������� � ��������� ���� .h
{
public:
	Point mp;
	Point prev_mp;
	bool lmp;
	bool prev_lmp;
};