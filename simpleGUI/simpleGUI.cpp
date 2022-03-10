#include "simpleGUI.h"

Fonts my_fonts;


//Fonts

Fonts::Fonts()
{
	roboto_reguar.loadFromFile("Roboto-Regular.ttf");
}
Fonts::~Fonts()
{
}

const Font& Fonts::getRobotoRegular() const
{
	return roboto_reguar;
}


//BondingBox

BondingBox::BondingBox() :
	ld(0.0, 0.0),
	ru(0.0, 0.0)
{
}

BondingBox::BondingBox(Point _ld, Point _ru) :
	ld(_ld),
	ru(_ru)
{
}

BondingBox::~BondingBox()
{}

bool BondingBox::contains(Point cnt)
{
	if (cnt.x > ld.x && cnt.x < ru.x && cnt.y > ru.y && cnt.y < ld.y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

float BondingBox::getWidth()
{
	return ru.x - ld.x;
}

float BondingBox::getHeight()
{
	return ld.y - ru.y;
}

Point BondingBox::getRu()
{
	return ru;
}

Point BondingBox::getLu()
{
	return Point(ld.x, ru.y);
}

Point BondingBox::getLd()
{
	return ld;
}

Point BondingBox::getRd()
{
	return Point(ru.x, ld.y);
}


//Interface

Interface::Interface()
{
}

Interface::~Interface() //сделать в нем и меню удаление элементов
{
}

void Interface::setWindow(RenderWindow& _window)
{
	window = &_window;
	wm_dat.box.ld.y = _window.getSize().y; //  /!!!\ возможные будущие ошибки
	wm_dat.box.ru.x = _window.getSize().x;
}

void Interface::update() //возможно сделать единовременное присвоение окна
{
	int i;
	if (wm_dat.box.contains(Mouse::getPosition(*window))) //видоизменить обновление (чтобы обновлялось в любом случае)
	{
		wm_dat.mouse_inside = 1;
	}
	else
	{
		wm_dat.mouse_inside = 0;
	}
	wm_dat.prev_lmp = Mouse::isButtonPressed(Mouse::Button::Left);
	for (i = 0; i < elements.size(); i++)
	{
		elements[i]->update(wm_dat, *window);
	}
}

void Interface::draw()
{
	int i;
	for (i = 0; i < elements.size(); i++)
	{
		elements[i]->draw(*window);
	}
}

void Interface::load(Element* element)
{
	elements.push_back(element);
}


//Element

Element::Element()
{
}

Element::Element(BondingBox _box) :
	box(_box)
{
}

Element::~Element()
{
}

void Element::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
}

void Element::draw(RenderWindow& window)
{
}


//WMInterfaceData

WMInterfaceData::WMInterfaceData() :
	prev_lmp(0),
	mouse_inside(0),
	box(Point(0.0, 0.0), Point(0.0, 0.0))
{
}

WMInterfaceData::~WMInterfaceData()
{
}


//ElementsMenu

ElementsMenu::ElementsMenu()
{
}

ElementsMenu::ElementsMenu(BondingBox _box)
{
	wm_dat.box = _box;
}

ElementsMenu::~ElementsMenu()
{
}

void ElementsMenu::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	int i;
	if (wm_dat.box.contains(Mouse::getPosition(window)))
	{
		wm_dat.mouse_inside = 1;
		for (i = 0; i < elements.size(); i++)
		{
			elements[i]->update(wm_dat, window);
		}
	}
	else
	{
		wm_dat.mouse_inside = 0;
	}
	wm_dat.prev_lmp = Mouse::isButtonPressed(Mouse::Button::Left);
}

void ElementsMenu::draw(RenderWindow& window)
{
	RectangleShape rect(Vector2f(wm_dat.box.getWidth(), wm_dat.box.getHeight()));
	rect.setFillColor(Color(200, 200, 200));
	rect.move(Vector2f(wm_dat.box.getLu().x, wm_dat.box.getLu().y));
	window.draw(rect);
	int i;
	for (i = 0; i < elements.size(); i++)
	{
		elements[i]->draw(window);
	}
}

void ElementsMenu::load(ControlElement* element)
{
	elements.push_back(element);
}


//ControlElement

ControlElement::ControlElement()
{
}

ControlElement::ControlElement(BondingBox _box) :
	box(_box)
{
}

ControlElement::~ControlElement()
{
}

void ControlElement::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
}

void ControlElement::draw(RenderWindow& window)
{
}


//TextElement

TextElement::TextElement() :
	text("button", my_fonts.getRobotoRegular(), 14)
{
}

TextElement::~TextElement()
{
}

void TextElement::setText(const Text& _text)
{
	text = _text;
	textUpdate();
}

void TextElement::setString(const String& _string)
{
	text.setString(_string);
	textUpdate();
}

void TextElement::setFont(const Font& _font)
{
	text.setFont(_font);
	textUpdate();
}

void TextElement::setCharacterSize(unsigned int _size)
{
	text.setCharacterSize(_size);
	textUpdate();
}

void TextElement::textUpdate()
{
}


//Button

Button::Button() //заполнить этот коструктор
{
}

Button::Button(BondingBox _box) :
	ControlElement(_box)
{
	textUpdate();
	modelUpdate();
	v[0].color = Color(128, 128, 128);
	v[1].color = Color(128, 128, 128);
	v[2].color = Color(128, 128, 128);
	v[3].color = Color(128, 128, 128);
	v[4].color = Color(128, 128, 128);
}

Button::~Button()
{
}

void Button::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	if (box.contains(Mouse::getPosition(window)))
	{
		if (Mouse::isButtonPressed(Mouse::Button::Left) == 1)
		{
			setColor(Color(50, 50, 50));
			if (wm_dat.prev_lmp == 0)
			{
			}
		}
		else
		{
			setColor(Color(60, 60, 60));
		}
	}
	else
	{
		setColor(Color(40, 40, 40));
	}
}

void Button::draw(RenderWindow& window)
{
	window.draw(rect);
	window.draw(v, 5, PrimitiveType::LinesStrip);
	window.draw(text);
}

void Button::setColor(Color _color)
{
	rect.setFillColor(_color);
}

void Button::textUpdate()
{
	text.setPosition(int(((box.ld.x + box.ru.x) / 2) - (text.getLocalBounds().width / 2)), int(((box.ld.y + box.ru.y) / 2) - (text.getLocalBounds().height / 1.5)));
}

void Button::modelUpdate()
{
	Point pnt;
	pnt = box.getLd();
	v[0].position.x = pnt.x;
	v[0].position.y = pnt.y;
	pnt = box.getLu();
	v[1].position.x = pnt.x;
	v[1].position.y = pnt.y;
	pnt = box.getRu();
	v[2].position.x = pnt.x;
	v[2].position.y = pnt.y;
	pnt = box.getRd();
	v[3].position.x = pnt.x;
	v[3].position.y = pnt.y;
	v[4] = v[0];
	rect.setPosition(box.getLu().x, box.getLu().y);
	rect.setSize(Vector2f(box.getWidth(), box.getHeight()));
}