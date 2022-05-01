#pragma once
#include "simpleGUI.h"
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

class SubWindow :public Element
{
public:
	SubWindow();
	SubWindow(BoundingBox _box);
	~SubWindow();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
private:
	void resizeUpdate();
	void moveUpdate();
	void resMovUpdate();
	void viewUpdate();

	GrabBox grabs[4];

	BoundingBox box;
	BoundingBox header_box;
	BoundingBox view_box;

	RectangleShape header_rect;
	RectangleShape view_rect;
};
