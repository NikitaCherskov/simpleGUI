#pragma once
#include "SFML/Graphics.hpp"
#include "DLLStructure.h"
#include "line_functions.h"
#include "mouseProcessor.h"
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

class NumericLabel :public ControlElement, public NumericTextElement
{
public:
	NumericLabel();
	NumericLabel(Point _position, int _before_comma, int _after_comma, float* _tied); //������� �������� �� ���������
	~NumericLabel();
	void setTied(float* _tied);
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
private:
	float getCut();
	float getMax();
	Point position;
	int bc;
	int ac;
	float max;
	float* tied;
	float prev_tied;
};