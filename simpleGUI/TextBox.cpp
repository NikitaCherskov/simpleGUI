#include "TextBox.h"


//TbxMover////////////////////////////////////////////////////////////////// спнбеэ 3 - напюанрйю оепелеыемхи рейярю //////////////////////////////////////////////////////////////////////////////////

TbxMover::TbxMover(const String* _str, BoundingBox _symb_box, int _symb_num, Point _base_pos) :
	str(_str), symb_box(_symb_box), symb_num(_symb_num), base_pos(_base_pos)
{
}

TbxMover::TbxMover(const String* _str, Point _base_pos):
	str(_str), symb_box
	(
		BoundingBox
		(
			_base_pos,
			getFont().getGlyph((*_str)[0], 14, 0).advance,
			14.0
		)
	),
	symb_num(0), base_pos(_base_pos)
{
}

TbxMover::~TbxMover()
{
}



void TbxMover::fromPosition(float position)
{
	int i;
	float cur_pos;

	for
	(
		i = 0, cur_pos = base_pos.x + getFont().getGlyph((*str)[0], 14, 0).advance;
		cur_pos < position && i < str->getSize();
		i++, cur_pos += getFont().getGlyph((*str)[i], 14, 0).advance
	)
	{}
	float advence = getFont().getGlyph((*str)[i], 14, 0).advance;
	symb_box = BoundingBox(Point(cur_pos - advence, base_pos.y), advence, 14.0);
	symb_num = i;
}

void TbxMover::fromNum(int num)
{
	int i;
	float cur_pos;

	for
	(
		i = 0, cur_pos = base_pos.x;
		i != num && i < str->getSize();
		cur_pos += getFont().getGlyph((*str)[i], 14, 0).advance, i++
	)
	{}

	symb_box = BoundingBox(Point(cur_pos, base_pos.y), getFont().getGlyph((*str)[i], 14, 0).advance, 14.0);
	symb_num = i;
}

void TbxMover::moveNext()
{
	if (symb_num != (str->getSize() - 1))
	{
		const Glyph& g = getFont().getGlyph((*str)[symb_num + 1], 14, 0);
		symb_box.position.x += getFont().getGlyph((*str)[symb_num], 14, 0).advance;
		symb_box.width = g.advance;
		symb_box.height = 14;

		symb_num++;
	}
}

void TbxMover::movePrev()
{
	if (symb_num != 0)
	{
		const Glyph& g = getFont().getGlyph((*str)[symb_num - 1], 14, 0);
		symb_box.position.x -= g.advance;
		symb_box.width = g.advance;
		symb_box.height = 14;

		symb_num--;
	}
}

void TbxMover::moveFromNum(int amount)
{
	int cur_num = symb_num;
	if (amount < 0)
	{
		while (symb_num != (cur_num + amount) && symb_num != 0)
		{
			movePrev();
		}
	}
	else
	{
		while (symb_num != (cur_num + amount) && symb_num != (str->getSize() - 1))
		{
			moveNext();
		}
	}
}

void TbxMover::moveFromDist(float dist)
{
	float cur_pos = symb_box.getLeft();
	if (dist < 0)
	{
		while (symb_box.getLeft() > (cur_pos + dist) && symb_num != 0)
		{
			movePrev();
		}
	}
	else
	{
		while (symb_box.getRight() < (cur_pos + dist) && symb_num != (str->getSize() - 1))
		{
			moveNext();
		}
	}
}

void TbxMover::setBasePos(Point _base_pos)
{
	symb_box.position += _base_pos - base_pos;
	base_pos = _base_pos;
}

Point TbxMover::getBasePos()
{
	return base_pos;
}

void TbxMover::setStringPtr(const String* _str, BoundingBox _symb_box, int _symb_num)
{
}

void TbxMover::stringChange(BoundingBox _symb_box, int _symb_num)
{
}

int TbxMover::getSymbNum()
{
	return symb_num;
}

BoundingBox TbxMover::getSymbBox()
{
	return symb_box;
}


//TbxProc///////////////////////////////////////////////////////// спнбемэ 2 - напюанрйю бгюхлндеиярбхи (оепелеыемхе, днаюбкемхе, сдюкемхе) ///////////////////////////////////////////////////////////

TbxProc::TbxProc(BoundingBox _box, const String& _str) :
	str(_str),
	first_symb(&str, Point(0.0, 0.0)),
	first_hl(first_symb),
	second_hl(first_symb)
{
	texture.create(_box.width, _box.height);
	txt.setCharacterSize(14);
	txt.setFont(getFont());
	txt.setString(_str);
	//txt.setPosition(5.0, 0.0);

	textureUpdate();
}

TbxProc::~TbxProc()
{
}



void TbxProc::update(BoundingBox _box, MouseData md)
{
	if (md.now_lmp == 1)
	{
		if (md.prev_lmp == 0)
		{
			first_hl = first_symb;
			first_hl.fromPosition(md.mp.x + 3.0);
		}
		second_hl = first_symb;
		second_hl.fromPosition(md.mp.x + 3.0);
	}
	else
	{
	}
	textureUpdate();
}

void TbxProc::textureUpdate()
{
	float l, r, s;

	if (first_hl.getSymbNum() < second_hl.getSymbNum())
	{
		l = first_hl.getSymbBox().getLeft();
		r = second_hl.getSymbBox().getLeft();
	}
	else
	{
		r = first_hl.getSymbBox().getLeft();
		l = second_hl.getSymbBox().getLeft();
	}
	s = r - l;


	RectangleShape hl_rect(Vector2f(s, 14.0));
	hl_rect.setPosition(Vector2f(l, 2.0));
	hl_rect.setFillColor(Color(0, 80, 160));

	RectangleShape hl_cursor_rect(Vector2f(1.0, 14.0));
	hl_cursor_rect.setPosition(Vector2f(second_hl.getSymbBox().getLeft(), 2.0));
	hl_cursor_rect.setFillColor(Color(200, 200, 200));


	texture.clear(Color::Black);
	texture.draw(hl_rect);
	texture.draw(hl_cursor_rect);
	texture.draw(txt);
	texture.display();
}


//TextBox//////////////////////////////////////////////////////////////////////////// спнбемэ 1 - хмрептеия (бунд - бшунд) ////////////////////////////////////////////////////////////////////////////
/*
TextBox::TextBox():

{
}
*/
TextBox::TextBox(BoundingBox _box, const String& _str) :
	proc
	(
		BoundingBox
		(
			_box.position + Point(1.0, 1.0),
			_box.width - 2.0,
			_box.height - 2.0
		),
		_str
	),
	rect(Vector2f(_box.width - 2.0, _box.height - 2.0)),
	box(_box)
{
	Point rect_pos = _box.position + Point(1.0, 1.0);
	rect.setPosition(rect_pos.x, rect_pos.y);
	rect.setOutlineThickness(1.0);
	rect.setFillColor(Color::Black);
	rect.setOutlineColor(Color(60, 60, 60));
}

TextBox::~TextBox()
{
}



void TextBox::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	if (box.contains(Mouse::getPosition(window)))
	{
		if (wm_dat.now_lmp == 1)
		{
			if (wm_dat.prev_lmp == 0)
			{
			}
			MouseData md;
			md.mp = Point(Mouse::getPosition(window)) - box.position;
			md.now_lmp = wm_dat.now_lmp;
			md.prev_lmp = wm_dat.prev_lmp;
			proc.update(box, md);
		}
		else
		{
		}
	}
	else
	{
	}
}

void TextBox::draw(RenderWindow& window)
{
	window.draw(rect);


	Sprite sprite;
	sprite.setTexture(proc.texture.getTexture());
	sprite.setPosition(rect.getPosition());

	window.draw(sprite);


	Text txt = proc.txt;
	txt.move(300.0, 0.0);

	window.draw(txt);
}

SymbMark::SymbMark()
{
}

SymbMark::SymbMark(BoundingBox _box, int _num)
{
}

SymbMark::~SymbMark()
{
}

StrProc::StrProc()
{
}

StrProc::StrProc(const std::string& _str)
{
}

StrProc::~StrProc()
{
}

void StrProc::setString(const std::string& _str)
{
}

void StrProc::posToBox(float position, BoundingBox* _box, int* _num)
{
}

BoundingBox StrProc::numToBox(int num, BoundingBox* _box)
{
	return BoundingBox();
}
