#include "TextBox.h"


//NumMarkm/PosMark/StrProc////////////////////////////////////////////////////////////////// ÓÐÎÂÅÜ 3 - ÎÁÐÀÁÎÒÊÀ ÏÅÐÅÌÅÙÅÍÈÉ ÒÅÊÑÒÀ //////////////////////////////////////////////////////////////////////////////////
NumMark::NumMark()
{
}

NumMark::NumMark(BoundingBox _symb_box) :
	symb_box(_symb_box)
{
}

NumMark::~NumMark()
{
}





PosMark::PosMark()
{
}
PosMark::PosMark(BoundingBox _symb_box, int _symb_num) :
	symb_box(_symb_box),
	symb_num(_symb_num)
{
}

PosMark::~PosMark()
{
}





StrProc::StrProc() :
	period_num(10),
	period_pos(100.0)
{
}

StrProc::StrProc(const String& _str) :
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

	if (symb_nums.size() == 0)
	{
		return BoundingBox(Point(0.0, 0.0), 0.0, 14.0);
	}
	else
	{
		BoundingBox symb_box;
		int old_num = num / period_num;
		if (old_num > symb_nums.size() - 1)
		{
			old_num = symb_nums.size() - 1;
		}
		else if (old_num < 0) //âîçìîæíî ýòî íå ïîíàäîáèòñÿ
		{
			old_num = 0;
		}
		symb_box = symb_nums[old_num].symb_box;

		for
			(
				i = old_num * period_num, cur_pos = symb_box.position.x;
				i != num && i < str.getSize();
				cur_pos += getFont().getGlyph(str[i], 14, 0).advance, i++
				)
		{
		}

		return BoundingBox(Point(cur_pos, 0.0), getFont().getGlyph(str[i], 14, 0).advance, 14.0);
	}
}

void StrProc::getFromPos(float pos, BoundingBox* box_write, int* num_write)
{
	int i;
	float cur_pos;
	if (symb_poses.size() == 0)
	{
		if (box_write != NULL)
		{
			*box_write = BoundingBox(Point(0.0, 0.0), 0.0, 14.0);
		}
		if (num_write != NULL)
		{
			*num_write = 0;
		}
	}
	else
	{
		BoundingBox symb_box;
		int old_num;
		int pos_ind = (int)(pos / period_pos);
		if (pos_ind > symb_poses.size() - 1)
		{
			pos_ind = symb_poses.size() - 1;
		}
		if (pos_ind < 0)
		{
			pos_ind = 0;
		}
		symb_box = symb_poses[pos_ind].symb_box;
		old_num = symb_poses[pos_ind].symb_num;

		for
			(
				i = old_num, cur_pos = symb_box.position.x; //Ñëåâà íåïðîâåðåííîå èñïðàâëåíèå
				cur_pos + getFont().getGlyph(str[i], 14, 0).advance < pos && i < str.getSize();
				cur_pos += getFont().getGlyph(str[i], 14, 0).advance, i++
				)
		{
		}
		if (box_write != NULL)
		{
			*box_write = BoundingBox(Point(cur_pos, 0.0), getFont().getGlyph(str[i], 14, 0).advance, 14.0);
		}
		if (num_write != NULL)
		{
			*num_write = i;
		}
	}
}

void StrProc::deleteSymbols(int _pos, int _size)
{
	str.erase(_pos, _size);
	updateMarks();
	//std::cout << str.getSize() << ":" << symb_nums.size() << ":" << symb_poses.size() << "\n";
}

void StrProc::addSymbol(int _pos, wchar_t c)
{
	str.insert(_pos, c);
	updateMarks();
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
			symb_nums.push_back(NumMark(nbox));
		}
		if (cur_pos + getFont().getGlyph(str[i], 14, 0).advance > target_pos) //âîçìîæíî óáðàòü " + getFont().getGlyph(str[i], 14, 0).advance"
		{
			BoundingBox nbox(Point(cur_pos, 0.0), getFont().getGlyph(str[i], 14, 0).advance, 14.0);
			symb_poses.push_back(PosMark(nbox, i));
			target_pos += period_pos;
		}
	}
}

//TbxProc///////////////////////////////////////////////////////// ÓÐÎÂÅÍÜ 2 - ÎÁÐÀÁÎÒÊÀ ÂÇÀÈÌÎÄÅÉÑÒÂÈÉ (ÏÅÐÅÌÅÙÅÍÈÅ, ÄÎÁÀÂËÅÍÈÅ, ÓÄÀËÅÍÈÅ) ///////////////////////////////////////////////////////////

float fixInternalBounds(float internalPos, float internalWidth, float outerPos, float outerWidth)
{
	if ((internalPos + internalWidth) > (outerPos + outerWidth))
	{
		internalPos = (outerPos + outerWidth) - internalWidth;
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
	del_metr(200),

	str_pos(0.0), txt_pos(0.0), view_pos(0.0)
{
	texture.create(_box.width, _box.height);
	txt.setCharacterSize(14);
	txt.setFont(getFont());
	txt.setString(_str);
	//txt.setPosition(5.0, 0.0);
	textureUpdate();

	str_width = str.getFromNum(str.str.getSize() - 1).getRight();
	view_width = _box.getWidth();
	txt_width = view_width * 2.0;
	//std::cout << strWidth << " " << txt.findCharacterPos(str.str.getSize() - 1).x;
}

TbxProc::~TbxProc()
{
}

void TbxProc::mouseEvent(BoundingBox _box, MouseData md)
{
	if (md.now_lmp == 1)
	{
		if (md.prev_lmp == 0)
		{
			str.getFromPos(md.mp.x + view_pos, &first_hl_box, &first_hl_num);
			//std::cout << first_hl_num;
		}
		str.getFromPos(md.mp.x + view_pos, &second_hl_box, &second_hl_num);
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

void TbxProc::mandatoryUpdate()
{
	del_metr.update();
}

void TbxProc::backspaceEvent()
{
	if (del_metr.getIsPassed() == 1)
	{
		int l, r, s;
		if (first_hl_num < second_hl_num)
		{
			l = first_hl_num;
			r = second_hl_num;
		}
		else
		{
			r = first_hl_num;
			l = second_hl_num;
		}
		if (l == r)
		{
			if (l != 0)
			{
				BoundingBox first_del = str.getFromNum(l - 1);
				str.deleteSymbols(l - 1, 1);
				first_hl_num = l - 1;
				first_hl_box = str.getFromNum(l - 1);
				second_hl_num = first_hl_num;
				second_hl_box = first_hl_box;
				str_width = str.getFromNum(str.str.getSize() - 1).getRight();
				if (first_hl_box.getLeft() < view_pos)
				{
					setViewPos(first_hl_box.getLeft());
				}
				txt_pos = loadTxtBounds(view_pos, view_width, txt_pos, txt_width);
				txt_pos = fixInternalBounds(txt_pos, txt_width, str_pos, str_width);
				view_pos = fixInternalBounds(view_pos, view_width, txt_pos, txt_width);
				updateViews(); //÷òî òî ñäåëàòü ñ ïîâòîðåíèåì ýòîãî êîäà
				textureUpdate();
			}
		}
		else
		{
			BoundingBox first_del = str.getFromNum(l);
			str.deleteSymbols(l, r - l);
			first_hl_num = l;
			first_hl_box = str.getFromNum(l);
			second_hl_num = first_hl_num;
			second_hl_box = first_hl_box;
			str_width = str.getFromNum(str.str.getSize() - 1).getRight();
			if (first_hl_box.getLeft() < view_pos)
			{
				setViewPos(first_hl_box.getLeft());
			}
			txt_pos = loadTxtBounds(view_pos, view_width, txt_pos, txt_width);
			txt_pos = fixInternalBounds(txt_pos, txt_width, str_pos, str_width);
			view_pos = fixInternalBounds(view_pos, view_width, txt_pos, txt_width);
			updateViews();
			textureUpdate();
		}
	}
}

void TbxProc::charInputEvent(wchar_t c)
{
	if (first_hl_num != second_hl_num)
	{
		backspaceEvent();
	}
	str.addSymbol(first_hl_num, c);
	first_hl_num++;
	first_hl_box = str.getFromNum(first_hl_num);
	second_hl_num = first_hl_num;
	second_hl_box = first_hl_box;
	str_width = str.getFromNum(str.str.getSize() - 1).getRight();
	if (first_hl_box.getLeft() > (view_pos + view_width))
	{
		setViewPos(first_hl_box.getLeft() - view_width);
	}
	txt_pos = loadTxtBounds(view_pos, view_width, txt_pos, txt_width);
	txt_pos = fixInternalBounds(txt_pos, txt_width, str_pos, str_width);
	view_pos = fixInternalBounds(view_pos, view_width, txt_pos, txt_width);
	updateViews();
	textureUpdate();
}

void TbxProc::textureUpdate()
{
	float l, r, s;

	if (first_hl_box.position.x < second_hl_box.position.x)
	{
		l = first_hl_box.position.x - view_pos;
		r = second_hl_box.position.x - view_pos;
	}
	else
	{
		r = first_hl_box.position.x - view_pos;
		l = second_hl_box.position.x - view_pos;
	}
	s = r - l;


	RectangleShape hl_rect(Vector2f(s, 14.0));
	hl_rect.setPosition(Vector2f(l, 2.0));
	hl_rect.setFillColor(Color(0, 80, 160));

	RectangleShape hl_cursor_rect(Vector2f(1.0, 14.0));
	hl_cursor_rect.setPosition(Vector2f(second_hl_box.position.x - view_pos, 2.0));
	hl_cursor_rect.setFillColor(Color(200, 200, 200));

	texture.clear(Color::Black);
	texture.draw(hl_rect);
	texture.draw(hl_cursor_rect);
	texture.draw(txt);
	texture.display();
}

void TbxProc::moveView(float x)
{
	view_pos += x;
	txt_pos = loadTxtBounds(view_pos, view_width, txt_pos, txt_width); //÷òî òî ñäåëàòü ñ ýòîé ïîâòîðÿþùåéñÿ çàïèñüþ
	txt_pos = fixInternalBounds(txt_pos, txt_width, str_pos, str_width);
	view_pos = fixInternalBounds(view_pos, view_width, txt_pos, txt_width);
	updateViews();
}

void TbxProc::setViewPos(float x)
{
	view_pos = x;
	txt_pos = loadTxtBounds(view_pos, view_width, txt_pos, txt_width);
	txt_pos = fixInternalBounds(txt_pos, txt_width, str_pos, str_width);
	view_pos = fixInternalBounds(view_pos, view_width, txt_pos, txt_width);
	updateViews();
}

void TbxProc::updateViews()
{
	int l, r;
	BoundingBox nTxtPox;
	str.getFromPos(txt_pos, &nTxtPox, &l);
	str.getFromPos(txt_pos + txt_width, NULL, &r);
	if (str.str.getSize() == 0)
	{
		txt.setString("");
		txt.setPosition(Vector2f((int)nTxtPox.position.x - (int)view_pos, 0.0));
	}
	else
	{
		txt.setString(str.str.substring(l, r - l + 1));
		txt.setPosition(Vector2f((int)nTxtPox.position.x - (int)view_pos, 0.0));
	}
	//std::cout << (int)nTxtPox.position.x << " : " << (int)viewPos << "\n";
}


//TextBox//////////////////////////////////////////////////////////////////////////// ÓÐÎÂÅÍÜ 1 - ÈÍÒÅÐÔÅÉÑ (ÂÕÎÄ - ÂÛÕÎÄ) ////////////////////////////////////////////////////////////////////////////
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
	int i;
	proc.mandatoryUpdate();
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
			proc.mouseEvent(box, md);
		}
		else
		{
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::BackSpace) == 1)
	{
		proc.backspaceEvent();
	}
	for (i = 0; i < wm_dat.events.size(); i++)
	{
		if (wm_dat.events[i].type == Event::TextEntered && wm_dat.events[i].text.unicode != 8 && wm_dat.events[i].text.unicode != 13)
		{
			proc.charInputEvent(wm_dat.events[i].text.unicode);
		}
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
	hl_cursor_rect.setPosition(Vector2f(proc.str_width + proc.str_pos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.view_width + proc.view_pos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.txt_width + proc.txt_pos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.str_pos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.view_pos, 2.0));
	window.draw(hl_cursor_rect);
	hl_cursor_rect.setPosition(Vector2f(proc.txt_pos, 2.0));
	window.draw(hl_cursor_rect);
}