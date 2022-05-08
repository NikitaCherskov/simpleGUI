#include "RadioButton.h"

RadioButton::RadioButton() //заполнить этот коструктор
{
}

RadioButton::RadioButton(BoundingBox _box) :
	Element(_box),
	is_checked(0)
{
	modelUpdate();
	textUpdate();
	out_circ.setOutlineThickness(1.0);
	out_circ.setOutlineColor(Color(128, 128, 128));
}

RadioButton::~RadioButton()
{
}

void RadioButton::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	Point check_pos;
	check_pos.x = check_box.position.x + (check_box.width / 2.0);
	check_pos.y = check_box.position.y + (check_box.height / 2.0);
	Point local_m = wm_dat.md.mp - check_pos;
	if (sqrt(local_m.x * local_m.x + local_m.y * local_m.y) < 7.0)
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

void RadioButton::draw(RenderTarget* target)
{
	target->draw(out_circ);
	if (is_checked == 1)
	{
		target->draw(inner_circ);
	}
	target->draw(text);
}

void RadioButton::setColor(Color _color)
{
	out_circ.setFillColor(_color);
}

void RadioButton::textUpdate()
{
	text.setPosition(check_box.position.x + 17.0, int(((check_box.getLd().y + check_box.getRu().y) / 2) - (text.getLocalBounds().height / 1.5))); //возможно изменить высоту расположения текста
}

void RadioButton::modelUpdate()
{
	check_box.position.x = box.position.x;
	check_box.position.y = box.position.y;
	check_box.width = 15.0;
	check_box.height = 15.0;
	check_box.position.y = box.position.y;
	float pos = box.height / 2.0;
	out_circ.setPosition(box.position.x + 1.0, box.position.y + 1.0);
	out_circ.setRadius(6);
	inner_circ.setPosition(box.position.x + 1.0 + 2.0, box.position.y + 1.0 + 2.0);
	inner_circ.setRadius(4);
}