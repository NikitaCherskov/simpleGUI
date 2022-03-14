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
class Label;
class NumericLabel;
class Slider;

float round(float r, int after_comma);
std::string ftos(float convering, int before_comma, int after_comma);

class Fonts
{
public:
	Fonts();
	~Fonts();
	const Font& getRobotoRegular() const;
private:
	Font roboto_reguar;
};
class BoundingBox //переимнеовать в BoundingBox
{
public:
	BoundingBox();
	BoundingBox(Point _position, float _width, float _height); //возможно поменять на _lu и _rd соответственно
	~BoundingBox();
	void move(Point _offset);
	void setPosition(Point _position);
	void setCenterPosition(Point _position);
	bool contains(Point cnt);
	float getLeft();
	float getRight();
	float getUp();
	float getDown();
	float getWidth();
	float getHeight();
	Point getRu();
	Point getLu();
	Point getLd();
	Point getRd();
	Point position;
	float width;
	float height;
};

class WMInterfaceData
{
public:
	WMInterfaceData(); //сделать в конструкторе box зависимым от window
	~WMInterfaceData();
	BoundingBox box;
	bool now_lmp;
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
	Element(BoundingBox _box);
	~Element();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window);
	virtual void draw(RenderWindow& window);
	BoundingBox box;
};

class ElementsMenu :public Element
{
public:
	ElementsMenu();
	ElementsMenu(BoundingBox _box); //возможно удалить такого рода конструкторы
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
	ControlElement(BoundingBox _box);
	~ControlElement();
	virtual void update(WMInterfaceData& wm_dat, RenderWindow& window);
	virtual void draw(RenderWindow& window);
protected:
	BoundingBox box; //возможно сделать открытым
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
	const Text& getText(const Text& _text) const;
protected:
	virtual void textUpdate();
	Text text;
};
class NumericTextElement
{
public:
	NumericTextElement();
	~NumericTextElement();
	void setFont(const Font& _font);
	void setCharacterSize(unsigned int _size);
	const Text& getText(const Text& _text) const;
protected:
	Text text;
};

class Button :public ControlElement, public TextElement
{
public:
	Button();
	Button(BoundingBox _box);
	~Button();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
private:
	RectangleShape rect;
	void setColor(Color _color);
	void textUpdate();
	void modelUpdate(); //возможно переименовать в positionUpdate()
};

class Label :public ControlElement, public TextElement
{
public:
	Label();
	Label(Point _position, int _symbol_max);
	~Label();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
private:
	void textUpdate();
	Point position;
	int symbol_max;
};

class NumericLabel :public ControlElement, public NumericTextElement //тут не должно быть _box
{
public:
	NumericLabel();
	NumericLabel(Point _position, int _before_comma, int _after_comma, float* _tied); //сделать значения по умолчанию
	~NumericLabel();
	void setTied(float* _tied);
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
private:
	void textUpdate();
	float getCut();
	float getMax();
	Point position;
	int bc;
	int ac;
	float max;
	float* tied;
	float prev_tied;
};

class Slider: public ControlElement
{
public:
	Slider();
	Slider(BoundingBox _box);
	~Slider();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
	float getValue();
private:
	void setColor(Color _color);
	float last_position;
	float val;
	float grab_pnt;
	bool is_grabed;
	BoundingBox sub_box;
	RectangleShape rect;
	Vertex vline[4];
};