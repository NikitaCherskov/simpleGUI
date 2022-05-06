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
class Scroller
{
public:
	Scroller();
	Scroller(BoundingBox _box, Sprite* _sprite = NULL, RenderTexture* _texture = NULL);
	~Scroller();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderTarget* target);

	void setSize(Point _size);
	void setPosition(Point _position);
	Point getSize();
	Point getPosition();
	Sprite* sprite;
	RenderTexture* texture;
private:
	void modelUpdate();
	BoundingBox box;
	GrabBox scrol_box;
	RectangleShape rect;
	RectangleShape scrol_rect;
};
class SubWindow :public Element
{
public:
	SubWindow();
	SubWindow(BoundingBox _box);
	~SubWindow();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderTarget* target);
	void load(Element* element);
private:
	void resizeUpdate();
	void moveUpdate();
	void resMovUpdate();
	void viewUpdate();
	void slideUpdate();
	void spriteCorrection();
	Sprite sprite;

	GrabBox grabs[4];

	BoundingBox box;
	BoundingBox header_box;
	BoundingBox view_box;

	RectangleShape header_rect;
	RectangleShape view_rect;
	RectangleShape h_rect;
	RectangleShape v_rect; //����_������
	Scroller h_scrol;
	RectangleShape inter_hv_rect;

	std::vector<Element*> elements;
	RenderTexture texture;
	Point max_pos;
	bool h_slider;
	bool v_slider;
};
