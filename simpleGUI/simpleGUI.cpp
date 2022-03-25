#include "simpleGUI.h"

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


//TextBox

TextBox::TextBox()
{
}

TextBox::TextBox(BoundingBox _box, RenderWindow& window) :
	ControlElement(BoundingBox(Point(500, 100), 200, 20)),
	str("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtYuVvWwXxYyZzzzq"),
	front_loaded_symbol(0),
	metr(500),
	cursor_hl(0),
	crsr_blnd(0)
{
	txt.text.setFont(my_fonts.getRobotoRegular());
	txt.text.setCharacterSize(14);
	float sum_lenth, i;
	rect.setPosition(box.getLu().x + 1.0, box.getLu().y + 1.0); //возможно добавить textUpdate()
	rect.setSize(Vector2f(box.getWidth() - 2.0, box.getHeight() - 2.0));
	rect.setOutlineThickness(1.0);
	rect.setOutlineColor(Color(128, 128, 128));
	/*
	//with kerning:
	for (sum_lenth = 0.0, i = 0; sum_lenth < (box.getWidth() * 1.5) || i < str.size(); sum_lenth += (my_fonts.getRobotoRegular().getGlyph(str[i], txt.getCharacterSize(), 0, 0.0).bounds.width - my_fonts.getRobotoRegular().getKerning(str[i], str[i + 1], txt.getCharacterSize())), i++)
	{
		std::cout << my_fonts.getRobotoRegular().getKerning(str[i], str[i + 1], txt.getCharacterSize());
	}
	*/
	for (sum_lenth = 0.0, i = 0; sum_lenth < (box.getWidth() * 1.5) && i < str.size(); sum_lenth += my_fonts.getRobotoRegular().getGlyph(str[i], txt.text.getCharacterSize(), 0, 0.0).bounds.width, i++)
	{}
	txt.text.setString(str.substr(0, i));
	txt.text.setPosition(5.0, int((box.height / 2.0) - (txt.text.getLocalBounds().height / 1.5)));
	rend_txt.create(rect.getSize().x, rect.getSize().y);
	textUpdate();
	rend_txt.setRepeated(1);
	rect.setTexture(&rend_txt.getTexture());
}

TextBox::~TextBox()
{
}

void TextBox::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	if (box.contains(Mouse::getPosition(window)))
	{
		//Cursor cursor;
		//cursor.loadFromSystem(Cursor::Text);
		//window.setMouseCursor(cursor);
		if (wm_dat.now_lmp == 1)
		{
			if (wm_dat.prev_lmp == 0)
			{
			}
			txt.update(wm_dat, window, Vector2f(Mouse::getPosition(window)) - rect.getPosition());
			if (wm_dat.metronomes[0].getIsPassed() == 1)
			{
				textMovingUpdate(window);
			}
		}
		else
		{
		}
	}
	else
	{
		//Cursor cursor;
		//cursor.loadFromSystem(Cursor::Arrow);
		//window.setMouseCursor(cursor);
	}
}

void TextBox::draw(RenderWindow& window)
{
	window.draw(rect);
	window.draw(txt.text);
	metr.update();
	if (metr.getIsPassed() == 1)
	{
		if (crsr_blnd == 1)
		{
			crsr_blnd = 0;
		}
		else
		{
			crsr_blnd = 1;
		}
	}
	if (crsr_blnd == 1)
	{
		RectangleShape crsr;
		crsr.setPosition(Vector2f(cursor_hl, txt.text.getPosition().y) + rect.getPosition());
		crsr.setSize(Vector2f(1, 14));
		crsr.setFillColor(Color(230, 230, 230, 230));
		window.draw(crsr);
	}
}

void TextBox::fullMoveLeft()
{
	int i, i2;
	float mov = 0.0;
	float symbol_width;
	for (i = front_loaded_symbol - 1, i2 = 0; i >= 0 && mov < 30.0; i--, i2++)
	{
		symbol_width = txt.text.getFont()->getGlyph(txt.text.getString()[i], txt.text.getCharacterSize(), 0).bounds.width;
		mov += symbol_width;
	}
	txt.first_hlcursor += i2;
	txt.second_hlcursor += i2;
	//txt.first_hlposition += mov;
	front_loaded_symbol = i + 1;
	txt.move(Point(-mov, 0.0));
	txt.text.setString(str.substr(front_loaded_symbol, txt.text.getString().getSize())); //вынести size в класс
	textUpdate();
}

void TextBox::fullMoveRight()
{
	int i;
	float mov = 0.0;
	float symbol_width;
	for (i = 0; i < (str.size() - (txt.text.getString().getSize() + front_loaded_symbol)) && mov < 30.0; i++)
	{
		symbol_width = txt.text.getFont()->getGlyph(txt.text.getString()[i], txt.text.getCharacterSize(), 0).bounds.width;
		mov += symbol_width;
	}
	txt.first_hlcursor -= i;
	txt.second_hlcursor -= i;
	//txt.first_hlposition -= mov;
	front_loaded_symbol += i;
	txt.move(Point(mov, 0.0));
	txt.text.setString(str.substr(front_loaded_symbol, txt.text.getString().getSize())); //вынести size в класс
	textUpdate();
}

void TextBox::moveRect(float dist)
{
	dist = boundVal(dist, (rect.getGlobalBounds().width - 5.0) - (txt.text.getPosition().x + txt.text.getGlobalBounds().width), 5.0 - txt.text.getPosition().x);
	txt.move(Point(dist, 0.0));
}

void TextBox::textUpdate()
{
	float l, r;
	//std::cout << txt.first_hlcursor << ":" << txt.second_hlcursor << "\n";
	txt.getHlBounds(&l, &r, &cursor_hl);
	RectangleShape hightlight;
	hightlight.setPosition(Vector2f(l, txt.text.getPosition().y));
	hightlight.setSize(Vector2f(r - l, txt.text.getCharacterSize()));
	hightlight.setFillColor(Color(10, 30, 128));
	txt.textUpdate();
	rend_txt.clear(); //вынести в отдельную функцию
	rend_txt.draw(hightlight);
	rend_txt.draw(txt.text);
	rend_txt.display();
}

void TextBox::textMovingUpdate(RenderWindow& window)
{
	float moving_dist;
	float mouse_position = Mouse::getPosition(window).x - rect.getPosition().x;
	if ((mouse_position + 25.0) > rect.getGlobalBounds().width)
	{
		moving_dist = ((mouse_position + 25.0) - rect.getGlobalBounds().width) / 7.0;
		moveRect(-moving_dist); //переименовать, т.к. двигается не совсем rect
		if (txt.text.getPosition().x < -80.0)
		{
			fullMoveRight();
		}
	}
	else if (mouse_position < 25.0)
	{
		moving_dist = (25.0 - mouse_position) / 7.0;
		moveRect(moving_dist); //переименовать, т.к. двигается не совсем rect
		if (txt.text.getPosition().x > -20.0)
		{
			fullMoveLeft();
		}
	}
	textUpdate();
	//std::cout << (char)txt.text.getString()[txt.hlcursor] << ":" << txt.hlcursor << ":" << txt.text.getString().getSize() << "\n";
}
