#include "TextBox.h"


//TbxMover////////////////////////////////////////////////////////////////// ”–Œ¬≈‹ 3 - Œ¡–¿¡Œ“ ¿ œ≈–≈Ã≈Ÿ≈Õ»… “≈ —“¿ //////////////////////////////////////////////////////////////////////////////////
/*
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
*/

//TbxProc///////////////////////////////////////////////////////// ”–Œ¬≈Õ‹ 2 - Œ¡–¿¡Œ“ ¿ ¬«¿»ÃŒƒ≈…—“¬»… (œ≈–≈Ã≈Ÿ≈Õ»≈, ƒŒ¡¿¬À≈Õ»≈, ”ƒ¿À≈Õ»≈) ///////////////////////////////////////////////////////////

float fixInternalBounds(float internalPos, float internalWidth, float outerPos, float outerWidth)
{
	if ((internalPos + internalWidth) > (outerPos + outerWidth))
	{
		internalPos -= (internalPos + internalWidth) - (outerPos + outerWidth);
	}
	if (internalPos < outerPos)
	{
		internalPos = outerPos;
	}
	return internalPos;
}
float loadTxtBounds(float viewPos, float viewWidth, float txtPos, float txtWidth)
{
	if ((viewPos + viewWidth) > (txtPos + txtWidth) || viewPos < txtPos)
	{
		txtPos = viewPos + (viewWidth / 2.0) - (txtWidth / 2.0);
	}
	return txtPos;
}

TbxProc::TbxProc(BoundingBox _box, const String& _str) :
	str(_str),
	//first_symb(&(str.str), Point(0.0, 0.0)),
	first_hl_box(Point(0.0, 0.0), getFont().getGlyph(_str[0], 14, 0).advance, 14.0),
	second_hl_box(Point(0.0, 0.0), getFont().getGlyph(_str[0], 14, 0).advance, 14.0),
	first_hl_num(0),
	second_hl_num(0),

	strPos(0.0), txtPos(0.0), viewPos(0.0)
{
	texture.create(_box.width, _box.height);
	txt.setCharacterSize(14);
	txt.setFont(getFont());
	txt.setString(_str);
	//txt.setPosition(5.0, 0.0);
	textureUpdate();

	strWidth = str.getFromNum(str.str.getSize() - 1).getRight();
	viewWidth = _box.getWidth();
	txtWidth = viewWidth * 2.0;
	//std::cout << strWidth << " " << txt.findCharacterPos(str.str.getSize() - 1).x;
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
			str.getFromPos(md.mp.x, &first_hl_box, &first_hl_num);
			//std::cout << first_hl_num;
		}
		str.getFromPos(md.mp.x, &second_hl_box, &second_hl_num);
		if (_box.width - md.mp.x < 20.0)
		{
			moveView(0.1);
		}
		else if (md.mp.x  < 20.0)
		{
			moveView(-0.1);
		}
	}
	else
	{
	}
	textureUpdate();
}

void TbxProc::textureUpdate()
{
	float l, r, s;

	if (first_hl_box.position.x < second_hl_box.position.x)
	{
		l = first_hl_box.position.x;
		r = second_hl_box.position.x;
	}
	else
	{
		r = first_hl_box.position.x;
		l = second_hl_box.position.x;
	}
	s = r - l;


	RectangleShape hl_rect(Vector2f(s, 14.0));
	hl_rect.setPosition(Vector2f(l, 2.0));
	hl_rect.setFillColor(Color(0, 80, 160));

	RectangleShape hl_cursor_rect(Vector2f(1.0, 14.0));
	hl_cursor_rect.setPosition(Vector2f(second_hl_box.position.x, 2.0));
	hl_cursor_rect.setFillColor(Color(200, 200, 200));

	texture.clear(Color::Black);
	texture.draw(hl_rect);
	texture.draw(hl_cursor_rect);
	texture.draw(txt);
	texture.display();
}

void TbxProc::moveView(float x)
{
	viewPos += x;
	/*
	float timedTxtPos = loadTxtBounds(viewPos, viewWidth, txtPos, txtWidth);
	timedTxtPos = fixInternalBounds(txtPos, txtWidth, strPos, strWidth);
	if (timedTxtPos != 0)
	{
		std::cout << "a";
	}
	*/
	txtPos = loadTxtBounds(viewPos, viewWidth, txtPos, txtWidth);
	txtPos = fixInternalBounds(txtPos, txtWidth, strPos, strWidth);
	viewPos = fixInternalBounds(viewPos, viewWidth, txtPos, txtWidth);
	updateViews();
}

void TbxProc::setViewPos(float x)
{
}

void TbxProc::updateViews()
{
	txt.setPosition(Vector2f((int)(txtPos - viewPos), 0.0));
	int l, r;
	str.getFromPos(txtPos, NULL, &l);
	str.getFromPos(txtPos + txtWidth, NULL, &r);
	txt.setString(str.str.substring(l, r - l));
}


//TextBox//////////////////////////////////////////////////////////////////////////// ”–Œ¬≈Õ‹ 1 - »Õ“≈–‘≈…— (¬’Œƒ - ¬€’Œƒ) ////////////////////////////////////////////////////////////////////////////
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
	txt.move(0.0, 0.0);
	window.draw(txt);

	RectangleShape hl_cursor_rect(Vector2f(1.0, 14.0));
	hl_cursor_rect.setFillColor(Color(200, 64, 64));
	hl_cursor_rect.setPosition(Vector2f(proc.strWidth + proc.strPos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.viewWidth + proc.viewPos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.txtWidth + proc.txtPos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.strPos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.viewPos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.txtPos, 2.0));
	window.draw(hl_cursor_rect);
}


//       //////////////////////////////////////////////////////////////////////////// ”–Œ¬≈Õ‹ 0 - › —œ≈–≈Ã≈Õ“¿À‹Õ€… ////////////////////////////////////////////////////////////////////////////




numMark::numMark()
{
}

numMark::numMark(BoundingBox _symb_box):
	symb_box(_symb_box)
{
}

numMark::~numMark()
{
}





posMark::posMark()
{
}
posMark::posMark(BoundingBox _symb_box, int _symb_num):
	symb_box(_symb_box),
	symb_num(_symb_num)
{
}

posMark::~posMark()
{
}





StrProc::StrProc():
	period_num(10),
	period_pos(100.0)
{
}

StrProc::StrProc(const String& _str):
	str(_str),
	period_num(10),
	period_pos(100.0)
{
	updateMarks();
}

StrProc::~StrProc()
{
}

BoundingBox StrProc::getFromNum(int num)
{
	int i;
	float cur_pos;

	BoundingBox symb_box;
	int old_num = num / period_num;
	symb_box = symb_nums[old_num].symb_box;

	for
	(
		i = old_num * period_num, cur_pos = symb_box.position.x;
		i != num && i < str.getSize();
		cur_pos += getFont().getGlyph(str[i], 14, 0).advance, i++
	)
	{}

	return BoundingBox(Point(cur_pos, 0.0), getFont().getGlyph(str[i], 14, 0).advance, 14.0);
}

void StrProc::getFromPos(float pos, BoundingBox* box_write, int* num_write)
{
	int i;
	float cur_pos;

	BoundingBox symb_box;
	int old_num;
	symb_box = symb_poses[(int)(pos / period_pos)].symb_box;
	old_num = symb_poses[(int)(pos / period_pos)].symb_num;

	for
	(
		i = old_num, cur_pos = symb_box.position.x; //—ÎÂ‚‡ ÌÂÔÓ‚ÂÂÌÌÓÂ ËÒÔ‡‚ÎÂÌËÂ
		cur_pos + getFont().getGlyph(str[i], 14, 0).advance < pos && i < str.getSize();
		cur_pos += getFont().getGlyph(str[i], 14, 0).advance, i++
	)
	{
	}
	if (box_write != NULL)
	{
		*box_write = BoundingBox(Point(cur_pos, 0.0), getFont().getGlyph(str[i], 14, 0).advance, 14.0);
	}
	if(num_write != NULL)
	{
		*num_write = i;
	}
}

void StrProc::updateMarks()
{
	symb_nums.clear();
	symb_poses.clear();

	int i;
	float cur_pos;
	float target_pos;
	for
	(
		i = 0, cur_pos = 0.0, target_pos = 0.0;
		i < str.getSize();
		cur_pos += getFont().getGlyph(str[i], 14, 0).advance, i++
	)
	{
		if (i % period_num == 0)
		{
			BoundingBox nbox(Point(cur_pos, 0.0), getFont().getGlyph(str[i], 14, 0).advance, 14.0);
			symb_nums.push_back(numMark(nbox));
		}
		if (cur_pos + getFont().getGlyph(str[i], 14, 0).advance > target_pos) //‚ÓÁÏÓÊÌÓ Û·‡Ú¸ " + getFont().getGlyph(str[i], 14, 0).advance"
		{
			BoundingBox nbox(Point(cur_pos, 0.0), getFont().getGlyph(str[i], 14, 0).advance, 14.0);
			symb_poses.push_back(posMark(nbox, i));
			target_pos += period_pos;
		}
	}
}
