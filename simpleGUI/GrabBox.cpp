#include "GrabBox.h"
GrabBox::GrabBox()
{
}

GrabBox::GrabBox(BoundingBox _box) :
	box(_box),
	moved_box(_box),
	is_grabbed(0)
{
}

GrabBox::~GrabBox()
{
}

void GrabBox::update(MouseData md)
{
	if (box.contains(md.mp))
	{
		if (md.lmp == 1)
		{
			if (md.prev_lmp == 0)
			{
				is_grabbed = 1;
				grab_point = md.mp - box.position;
			}
		}
	}
	if (md.lmp == 0)
	{
		if (is_grabbed == 1)
		{
			moved_box = box;
		}
		is_grabbed = 0;
	}
	if (is_grabbed == 1)
	{
		moved_box.position = md.mp - grab_point;
	}
}