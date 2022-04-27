#include "simpleGUI.h"
#include <Windows.h> //заменить на обработку клавиш sfml

Fonts my_fonts;

float round(float r, int after_comma)
{
	int i;
	int rank;
	for (i = 0, rank = 1; i < after_comma; i++) //оптимизировать (заменить на while(after_comma > 0)
	{
		rank *= 10;
	}
	return float(int(r * rank)) / rank;
}
std::string ftos(float convering, int before_comma, int after_comma) //переименовать в автоматический, добавить отдельно для int и float
{
	int i;
	std::string converted;
	if (after_comma == 0)
	{
		converted = std::to_string(int(convering));
		if (converted.size() > before_comma)
		{
			for (i = 0; i < converted.size(); i++)
			{
				converted[i] = '9';
			}
		}
		return converted;
	}
	else
	{
		int j;
		converted = std::to_string(convering);
		for (i = 0; i < converted.size() && converted[i] != '.'; i++)
		{}
		if (i > before_comma)
		{
			int sft;
			for (j = 0; j < converted.size(); j++)
			{
				if (converted[j] != '.')
				{
					converted[j] = '9';
				}
			}
			return converted.substr(i - before_comma, after_comma + before_comma + 1);
		}
		return converted.substr(0, i + after_comma + 1);
	}
}
const Font& getFont()
{
	return my_fonts.getRobotoRegular();
}
float boundVal(float b, float lb, float rb) //переменовать b в bound
{
	if (b < lb)
	{
		return lb;
	}
	else if(b > rb)
	{
		return rb;
	}
	else
	{
		return b;
	}
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
	wm_dat.box.width = _window.getSize().y; //  /!!!\ возможные будущие ошибки
	wm_dat.box.height = _window.getSize().x;
	wm_dat.metronomes.push_back(Metronome(30));
}

void Interface::update(const std::vector<Event>& events) //возможно сделать единовременное присвоение окна
{
	int i;
	wm_dat.events = events;
	if (wm_dat.box.contains(Mouse::getPosition(*window))) //видоизменить обновление (чтобы обновлялось в любом случае)
	{
		wm_dat.mouse_inside = 1;
	}
	else
	{
		wm_dat.mouse_inside = 0;
	}
	wm_dat.prev_lmp = wm_dat.now_lmp;
	wm_dat.now_lmp = Mouse::isButtonPressed(Mouse::Button::Left);
	for (i = 0; i < wm_dat.metronomes.size(); i++)
	{
		wm_dat.metronomes[i].update();
	}
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

Element::Element(BoundingBox _box) :
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
	now_lmp(0),
	prev_lmp(0),
	mouse_inside(0),
	box(Point(0.0, 0.0), 0.0, 0.0)
{
}

WMInterfaceData::~WMInterfaceData()
{
}


//ElementsMenu

ElementsMenu::ElementsMenu()
{
}

ElementsMenu::ElementsMenu(BoundingBox _box)
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

ControlElement::ControlElement(BoundingBox _box) :
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

const Text& TextElement::getText(const Text& _text) const
{
	return text;
}

void TextElement::textUpdate()
{
}


//NumericTextElement

NumericTextElement::NumericTextElement() :
	text("button", my_fonts.getRobotoRegular(), 14) //убрать тестовый button
{
}

NumericTextElement::~NumericTextElement()
{
}

void NumericTextElement::setFont(const Font& _font)
{
	text.setFont(_font);
}

void NumericTextElement::setCharacterSize(unsigned int _size)
{
	text.setCharacterSize(_size);
}

const Text& NumericTextElement::getText(const Text& _text) const
{
	return text;
}



//Button

Button::Button() //заполнить этот коструктор
{
}

Button::Button(BoundingBox _box) :
	ControlElement(_box)
{
	textUpdate();
	modelUpdate();
	rect.setOutlineThickness(1.0);
	rect.setOutlineColor(Color(128, 128, 128));
}

Button::~Button()
{
}

void Button::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	if (box.contains(Mouse::getPosition(window)))
	{
		if (wm_dat.now_lmp == 1)
		{
			setColor(Color(50, 50, 50));
			if (wm_dat.prev_lmp == 0)
			{
				std::cout << 1;
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
	window.draw(text);
}

void Button::setColor(Color _color)
{
	rect.setFillColor(_color);
}

void Button::textUpdate()
{
	text.setPosition(int(((box.getLd().x + box.getRu().x) / 2) - (text.getLocalBounds().width / 2)), int(((box.getLd().y + box.getRu().y) / 2) - (text.getLocalBounds().height / 1.5)));
}

void Button::modelUpdate()
{
	rect.setPosition(box.getLu().x + 1.0, box.getLu().y + 1.0);
	rect.setSize(Vector2f(box.getWidth() - 2.0, box.getHeight() - 2.0));
}

Label::Label() //заполнить конструктор
{}

Label::Label(Point _position, int _symbol_max):
	position(_position),
	symbol_max(_symbol_max)
{
	textUpdate();
}

Label::~Label()
{}

void Label::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
}

void Label::draw(RenderWindow& window)
{
	window.draw(text);
}

void Label::textUpdate()
{
	text.setString(text.getString().substring(0, symbol_max));
	text.setPosition(position.x, position.y);
}


//NumericLabel

NumericLabel::NumericLabel()
{
}

NumericLabel::NumericLabel(Point _position, int _before_comma, int _after_comma, float* _tied):
	position(_position),
	bc(_before_comma),
	ac(_after_comma),
	tied(_tied),
	prev_tied(0.0)
{
	text.setString(ftos(*tied, bc, ac));
	prev_tied = *tied;
	text.setPosition(Vector2f(position.x, position.y));
	max = getMax(); //возможно преобразовать в maxUpdate()
}

NumericLabel::~NumericLabel()
{
}

void NumericLabel::setTied(float* _tied)
{
	tied = _tied;
}

void NumericLabel::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
}

void NumericLabel::draw(RenderWindow& window)
{
	if (prev_tied != *tied)
	{
		text.setString(ftos(*tied, bc, ac));
		prev_tied = *tied;
		window.draw(text);
	}
	else
	{
		window.draw(text);
	}
}

void NumericLabel::textUpdate()
{
	text.setPosition(Vector2f(position.x, position.y));
}

float NumericLabel::getCut() //заменть round на RoundTo()
{
	float cuting = *tied;
	if (cuting > max)
	{
		return max;
	}
	return round(cuting, ac);
}

float NumericLabel::getMax()
{
	float _max;
	int i, j, rank;
	for (i = 0, _max = 0.0; i < (bc + ac); i++)
	{
		for (j = 0, rank = 1; j < i; j++)
		{
			rank *= 10;
		}
		_max += 9.0 * rank;
	}
	for (j = 0, rank = 1; j < ac; j++)
	{
		rank *= 10;
	}
	_max /= rank;
	return _max;
}


//Slider

Slider::Slider()
{
}

Slider::Slider(BoundingBox _box) :
	ControlElement(_box),
	sub_box(box.position + Point(0.0, 0.0), 10.0, box.height),
	is_grabed(0),
	grab_pnt(0.0),
	val(0.0)
{
	int i;
	rect.setPosition(sub_box.position.x + 1.0, sub_box.position.y + 1.0);
	rect.setSize(Vector2f(sub_box.width - 2.0, sub_box.height - 2.0));
	rect.setFillColor(Color(40, 40, 40));
	rect.setOutlineThickness(1.0);
	rect.setOutlineColor(Color(128, 128, 128));
	vline[0].color = Color(32, 128, 255);
	vline[1].color = Color(32, 128, 255);
	vline[2].color = Color(128, 128, 128);
	vline[3].color = Color(128, 128, 128);
	for (i = 0; i < 4; i++)
	{
		vline[i].position.y = (sub_box.getUp() + sub_box.getDown()) / 2;
	}
	vline[0].position.x = box.getLeft();
	vline[1].position.x = sub_box.getLeft();
	vline[2].position.x = sub_box.getRight();
	vline[3].position.x = box.getRight();
}

Slider::~Slider()
{
}

void Slider::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	Point mp = Mouse::getPosition(window);
	if (sub_box.contains(mp))
	{
		if (wm_dat.now_lmp == 1)
		{
			if (wm_dat.prev_lmp == 0)
			{
				is_grabed = 1;
				grab_pnt = mp.x;
				grab_pnt -= sub_box.position.x;
				last_position = sub_box.position.x;
			}
		}
		else
		{
			setColor(Color(60, 60, 60)); //возможно заменить на прямое изменение цвета
			is_grabed = 0;
		}
	}
	else
	{
		if (wm_dat.now_lmp == 0)
		{
			is_grabed = 0;
		}
		setColor(Color(40, 40, 40));
	}
	if (is_grabed == 1)
	{
		setColor(Color(50, 50, 50));
		float processed_position = mp.x - grab_pnt;
		if ((mp.y - sub_box.getDown()) > 200.0 || (sub_box.getUp() - mp.y) > 200.0) //возможно поместить это в нужное место для оптимизации
		{
			processed_position = last_position;
		}
		if (processed_position < box.position.x)
		{
			processed_position = box.position.x;
			val = 0.0;
		}
		else if (processed_position > (box.getRight() - sub_box.width))
		{
			processed_position = box.getRight() - sub_box.width;
			val = 1.0;
		}
		else
		{
			val = (processed_position - box.position.x) / (box.width - sub_box.width);
		}
		rect.setPosition(processed_position + 1.0, rect.getPosition().y);
		sub_box.setPosition(Point(processed_position, sub_box.position.y));
		vline[1].position.x = sub_box.getLeft();
		vline[2].position.x = sub_box.getRight();
	}
}

void Slider::draw(RenderWindow& window)
{
	window.draw(vline, 2, PrimitiveType::LinesStrip);
	window.draw(&vline[2], 2, PrimitiveType::LinesStrip);
	window.draw(rect);
}

float Slider::getValue()
{
	return val;
}

void Slider::setColor(Color _color)
{
	rect.setFillColor(_color);
}