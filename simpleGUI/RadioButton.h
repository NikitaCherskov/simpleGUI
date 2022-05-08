#pragma once
#include "simpleGUI.h"

class RadioButton :public Element, public TextElement
{
public:
	RadioButton();
	RadioButton(BoundingBox _box);
	~RadioButton();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderTarget* target);
private:
	CircleShape out_circ;
	CircleShape inner_circ;
	BoundingBox check_box;
	void setColor(Color _color);
	void textUpdate();
	void modelUpdate(); //возможно переименовать в positionUpdate()
	bool is_checked;
};