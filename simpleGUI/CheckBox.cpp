#include "CheckBox.h"

CheckBox::CheckBox() //заполнить этот коструктор
{
}

CheckBox::CheckBox(BoundingBox _box) :
	Element(_box),
	is_checked(0)
{
	modelUpdate();
	textUpdate();
	rect.setOutlineThickness(1.0);
	rect.setOutlineColor(Color(128, 128, 128));
}

CheckBox::~CheckBox()
{
}

void CheckBox::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	if (check_box.contains(wm_dat.md.mp))
	{
		if (wm_dat.now_lmp == 1)
		{
			setColor(Color(30, 30, 30));
			if (wm_dat.prev_lmp == 0)
			{
				if (is_checked == 1)
				{
					is_checked = 0;
				}
				else
				{
					is_checked = 1;
				}
				std::cout << 1;
			}
		}
		else
		{
			setColor(Color(40, 40, 40));
		}
	}
	else
	{
		setColor(Color(20, 20, 20));
	}
}

void CheckBox::draw(RenderTarget* target)
{
	target->draw(rect);
	if (is_checked == 1)
	{
		const int check_size = 3.0; //костыль!
		Point c;
		c.x = check_box.position.x + (check_box.width / 2.0);
		c.y = check_box.position.y + (check_box.height / 2.0);
		drawLine(Point(c.x + check_size, c.y - check_size), Point(c.x, c.y + check_size), Color::White, target);
		drawLine(Point(c.x, c.y + check_size), Point(c.x - check_size, c.y - check_size), Color::White, target);
	}
	target->draw(text);
}

void CheckBox::setColor(Color _color)
{
	rect.setFillColor(_color);
}

void CheckBox::textUpdate()
{
	text.setPosition(check_box.position.x + 17.0, int(((check_box.getLd().y + check_box.getRu().y) / 2) - (text.getLocalBounds().height / 1.5))); //возможно изменить высоту расположения текста
}

void CheckBox::modelUpdate()
{
	check_box.position.x = box.position.x;
	check_box.position.y = box.position.y;
	check_box.width = 15.0;
	check_box.height = 15.0;
	check_box.position.y = box.position.y;
	rect.setPosition(box.getLu().x + 1.0, box.getLu().y + 1.0);
	rect.setSize(Vector2f(13.0, 13.0));
}