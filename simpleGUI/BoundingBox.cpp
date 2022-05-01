#include "BoundingBox.h"

BoundingBox::BoundingBox() :
	position(0.0, 0.0)
{
}

BoundingBox::BoundingBox(Point _position, float _width, float _height) :
	position(_position),
	width(_width),
	height(_height)
{}

BoundingBox::~BoundingBox()
{}

void BoundingBox::move(Point _offset)
{
	position += _offset;
}

void BoundingBox::setPosition(Point _position)
{
	position = _position;
}

void BoundingBox::setCenterPosition(Point _position)
{
	position.x = _position.x - (width / 2.0);
	position.y = _position.y - (height / 2.0);
}

bool BoundingBox::contains(Point cnt)
{
	if (cnt.x >= getLeft() && cnt.x <= getRight() && cnt.y >= getUp() && cnt.y <= getDown())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

float BoundingBox::getLeft()
{
	return position.x;
}

float BoundingBox::getRight()
{
	return position.x + width;
}

float BoundingBox::getUp()
{
	return position.y;
}

float BoundingBox::getDown()
{
	return position.y + height;
}

float BoundingBox::getWidth()
{
	return width;
}

float BoundingBox::getHeight()
{
	return height;
}

Point BoundingBox::getRu()
{
	return Point(position.x + width, position.y);
}

Point BoundingBox::getLu()
{
	return position;
}

Point BoundingBox::getLd()
{
	return Point(position.x, position.y + height);
}

Point BoundingBox::getRd()
{
	return Point(position.x + width, position.y + height);
}