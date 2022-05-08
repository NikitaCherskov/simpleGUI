#pragma once
#include <vector>
#include "simpleGUI.h"

class MyRadioGroup;
class RadioGroup;
class MyRadioButton;
class RadioButton;

class MyRadioGroup
{
public:
	virtual void resetChecks() = 0;
};

class RadioGroup: private MyRadioGroup
{
public:
	RadioGroup();
	~RadioGroup();
	void includeToGroup(RadioButton* _rbt);
	void excludeFromGroup(RadioButton* _rbt);
	//void switchCheck(RadioButton* _rbt);
private:
	void resetChecks();
	std::vector<RadioButton*> rbts;
};

class MyRadioButton
{
public:
	virtual void setCheck(bool _check) = 0;
	virtual void includeToGroup(RadioGroup* group) = 0;
};

class RadioButton :public Element, public TextElement, private MyRadioButton
{
public:
	RadioButton();
	RadioButton(BoundingBox _box);
	~RadioButton();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderTarget* target);
private:
	void includeToGroup(RadioGroup* _group);
	void setCheck(bool _check);
	MyRadioGroup* group;
	CircleShape out_circ;
	CircleShape inner_circ; //окрашивать в синий цвет
	BoundingBox check_box;
	void setColor(Color _color);
	void textUpdate();
	void modelUpdate(); //возможно переименовать в positionUpdate()
	bool is_checked;
};