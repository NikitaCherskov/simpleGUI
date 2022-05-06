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

class ScrolDat
{
public:
	//ScrolDat();
	//~ScrolDat();
	Sprite* sprite;
	RenderTexture* texture;
	BoundingBox box;
	GrabBox scrol_box;
	RectangleShape scrol_rect;

};
class ScrollerUpdates
{
public:
	//ScrollerUpdates();
	//~ScrollerUpdates();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window, ScrolDat* dat) = 0;
	virtual void modelUpdate(ScrolDat* dat) = 0;
};

class VScrollerUpdates : public ScrollerUpdates
{
public:
	VScrollerUpdates();
	~VScrollerUpdates();
	void update(WMInterfaceData& wm_dat, RenderWindow& window, ScrolDat* dat);
	void modelUpdate(ScrolDat* dat);;
};

class HScrollerUpdates : public ScrollerUpdates
{
public:
	HScrollerUpdates();
	~HScrollerUpdates();
	void update(WMInterfaceData& wm_dat, RenderWindow& window, ScrolDat* dat);
	void modelUpdate(ScrolDat* dat);
};

class Scroller
{
public:
	Scroller(bool h_orient);
	//Scroller(BoundingBox _box, Sprite* _sprite = NULL, RenderTexture* _texture = NULL);
	~Scroller();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderTarget* target);

	void setSize(Point _size);
	void setPosition(Point _position);
	Point getSize();
	Point getPosition();
	ScrolDat scrol_dat;
private:
	void modelUpdate();
	ScrollerUpdates* updates;
	RectangleShape rect;
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
	RectangleShape v_rect; //÷≈À‹_”¡–¿“¸
	Scroller h_scrol;
	Scroller v_scrol;
	RectangleShape inter_hv_rect;

	std::vector<Element*> elements;
	RenderTexture texture;
	Point max_pos;
	bool h_slider;
	bool v_slider;
};
