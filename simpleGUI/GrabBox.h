#pragma once
#include "BoundingBox.h"
class GrabBox
{
public:
	GrabBox();
	GrabBox(BoundingBox _box);
	~GrabBox();
	void update(MouseData md);
	bool is_grabbed;
	Point grab_point;
	BoundingBox box;
	BoundingBox moved_box;
};