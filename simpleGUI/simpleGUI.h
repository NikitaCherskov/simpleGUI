#pragma once
#include "SFML/Graphics.hpp"
#include "DLLStructure.h"
#include "line_functions.h"
#include <vector>

using namespace sf;

class Interface;
class Element;
class ControlElement;
class ElementsMenu;
class Button;
class BoundingBox;
class WMInterfaceData;


class BondingBox //������������� � BoundingBox
{
public:
	BondingBox();
	BondingBox(Point _ld, Point _ru);
	~BondingBox();
	bool contains(Point cnt);
	float getWidth();
	float getHeight();
	Point getRu();
	Point getLu();
	Point getLd();
	Point getRd();
	Point ru;
	Point ld;
};

class WMInterfaceData
{
public:
	WMInterfaceData(); //������� � ������������ box ��������� �� window
	~WMInterfaceData();
	BondingBox box;
	bool prev_lmp;
	bool mouse_inside;
};

class Interface
{
public:
	Interface();
	//Interface(BondingBox _box);
	~Interface();
	void setWindow(RenderWindow& _window);
	void update();
	void draw();
	void load(Element* element);
private:
	std::vector<Element*> elements;
	WMInterfaceData wm_dat;
	RenderWindow* window;
};

class Element //�������� ������� ���������� ���� ����� (������� ����������� �� .cpp)
{
public:
	Element();
	Element(BondingBox _box);
	~Element();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window);
	virtual void draw(RenderWindow& window);
	BondingBox box;
};

class ElementsMenu :public Element
{
public:
	ElementsMenu();
	ElementsMenu(BondingBox _box); //�������� ������� ������ ���� ������������
	~ElementsMenu();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window);
	virtual void draw(RenderWindow& window);
	virtual void load(ControlElement* element);
	String txt;
protected:
	WMInterfaceData wm_dat;
	std::vector<ControlElement*> elements;
};

class ControlElement :public Element //�������� ������ ������������� �����. ��� ����� ��������� �� �������������� ��������� � ����
{
public:
	ControlElement();
	ControlElement(BondingBox _box);
	~ControlElement();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window);
	virtual void draw(RenderWindow& window);
protected:
	BondingBox box; //�������� ������� ��������
};

class Button :public ControlElement
{
public:
	Button();
	Button(BondingBox _box);
	~Button();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window);
	virtual void draw(RenderWindow& window);
	Text text;
	Color color;
};