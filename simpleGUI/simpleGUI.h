#pragma once
#include "SFML/Graphics.hpp"
#include "DLLStructure.h"
#include "line_functions.h"
#include <vector>

using namespace sf;

class Fonts;
class Interface;
class Element;
class ControlElement;
class TextElement;
class ElementsMenu;
class Button;
class BoundingBox;
class WMInterfaceData;

class Fonts
{
public:
	Fonts();
	~Fonts();
	const Font& getRobotoRegular() const;
private:
	Font roboto_reguar;
};
class BondingBox //переимнеовать в BoundingBox
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
	WMInterfaceData(); //сделать в конструкторе box зависимым от window
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

class Element //возможно сделать абстрактым этот класс (удалить определения из .cpp)
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
	ElementsMenu(BondingBox _box); //возможно удалить такого рода конструкторы
	~ElementsMenu();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window);
	virtual void draw(RenderWindow& window);
	virtual void load(ControlElement* element);
	String txt;
protected:
	WMInterfaceData wm_dat;
	std::vector<ControlElement*> elements;
};

class ControlElement :public Element //возможно убрать промежуточный класс. для этого взглянуть на равноправность контролов и меню
{
public:
	ControlElement();
	ControlElement(BondingBox _box);
	~ControlElement();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window);
	virtual void draw(RenderWindow& window);
protected:
	BondingBox box; //возможно сделать открытым
};

class TextElement
{
public:
	TextElement();
	~TextElement();
	void setText(const Text& _text);
	void setString(const String& _string);
	void setFont(const Font& _font);
	void setCharacterSize(unsigned int _size);
	virtual void textUpdate();
	Text text;
};

class Button :public ControlElement, public TextElement
{
public:
	Button();
	Button(BondingBox _box);
	~Button();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
private:
	Vertex v[5];
	RectangleShape rect;
	void setColor(Color _color);
	void textUpdate();
	void modelUpdate();
};