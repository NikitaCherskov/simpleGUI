#include "Subwindow.h"

GrabBox::GrabBox()
{
}

GrabBox::GrabBox(BoundingBox _box):
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


SubWindow::SubWindow()
{
}

SubWindow::SubWindow(BoundingBox _box):
	box(_box),
	view_box(Point(0.0, 15.0), 0.0, 0.0)
{
	resMovUpdate();
	header_rect.setFillColor(Color(220, 220, 220));

	view_rect.setOrigin(0.0, -15.0);
	view_rect.setFillColor(Color::Black);
	view_rect.setOutlineThickness(1.0);
	view_rect.setOutlineColor(Color(220, 220, 220));
	viewUpdate();
	grabs[0].box = header_box;
	grabs[1].box = BoundingBox(Point(box.width - 2.0, box.height - 2.0), 5.0, 5.0);
	grabs[2].box = BoundingBox(Point(box.width - 2.0, 0.0), 5.0, box.height);
	grabs[3].box = BoundingBox(Point(0.0, box.height - 2.0), box.width, 5.0);
}

SubWindow::~SubWindow()
{
}

void SubWindow::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	int i;
	MouseData timed_md = wm_dat.md;
	timed_md.mp -= box.position;
	for (i = 0; i < 4; i++)
	{
		grabs[i].update(timed_md);
	}
	if (grabs[0].is_grabbed == 1)
	{
		box.position = grabs[0].moved_box.position + box.position;
		viewUpdate();
	}
	else if (grabs[1].is_grabbed == 1)
	{
		box.width = grabs[1].moved_box.position.x + 2.0;
		box.height = grabs[1].moved_box.position.y + 2.0;
		resizeUpdate();
		viewUpdate();
	}
	else if (grabs[2].is_grabbed == 1)
	{
		box.width = grabs[2].moved_box.position.x + 2.0;
		resizeUpdate();
		viewUpdate();
	}
	else if (grabs[3].is_grabbed == 1)
	{
		box.height = grabs[3].moved_box.position.y + 2.0;
		resizeUpdate();
		viewUpdate();
	}
}

void SubWindow::draw(RenderWindow& window)
{
	window.draw(header_rect);
	window.draw(view_rect);
	/*
	RectangleShape test_rect(Vector2f(grabs[2].box.width, grabs[2].box.height));
	test_rect.setPosition(grabs[2].box.position.x + box.position.x, grabs[2].box.position.y + box.position.y);
	test_rect.setFillColor(Color::Red);
	window.draw(test_rect);
	*/
}

void SubWindow::resizeUpdate()
{
	header_box.width = box.width;
	header_box.height = 15.0;
	view_box.width = box.width;
	view_box.height = box.height - 15.0;
	grabs[0].box = header_box;
	grabs[1].box = BoundingBox(Point(box.width - 2.0, box.height - 2.0), 5.0, 5.0);
	grabs[2].box = BoundingBox(Point(box.width - 2.0, 0.0), 5.0, box.height);
	grabs[3].box = BoundingBox(Point(0.0, box.height - 2.0), box.width, 5.0);
}

void SubWindow::moveUpdate()
{
}

void SubWindow::resMovUpdate()
{
	resizeUpdate();
	moveUpdate();
}

void SubWindow::viewUpdate()
{
	header_rect.setSize(Vector2f(header_box.width, header_box.height));
	view_rect.setSize(Vector2f(view_box.width - 2.0, view_box.height - 2.0));

	header_rect.setPosition(box.position.x, box.position.y);
	view_rect.setPosition(box.position.x + 1.0, box.position.y + 1.0);
}