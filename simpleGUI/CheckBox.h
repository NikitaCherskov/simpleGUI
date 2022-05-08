#pragma once
#include "simpleGUI.h"

class CheckBox :public Element, public TextElement
{
public:
	CheckBox();
	CheckBox(BoundingBox _box);
	~CheckBox();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderTarget* target);
private:
	RectangleShape rect;
	BoundingBox check_box;
	void setColor(Color _color);
	void textUpdate();
	void modelUpdate(); //возможно переименовать в positionUpdate()
	bool is_checked;
};