#include "Subwindow.h"

GrabBox::GrabBox()
{
}

GrabBox::GrabBox(BoundingBox _box) :
	box(_box),
	moved_box(_box),
	is_grabbed(0)
{
}

GrabBox::~GrabBox()
{
}

void GrabBox::update(MouseData md)
{
	if (box.contains(md.mp))
	{
		if (md.lmp == 1)
		{
			if (md.prev_lmp == 0)
			{
				is_grabbed = 1;
				grab_point = md.mp - box.position;
			}
		}
	}
	if (md.lmp == 0)
	{
		if (is_grabbed == 1)
		{
			moved_box = box;
		}
		is_grabbed = 0;
	}
	if (is_grabbed == 1)
	{
		moved_box.position = md.mp - grab_point;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


SubWindow::SubWindow()
{
}

SubWindow::SubWindow(BoundingBox _box) :
	box(_box),
	view_box(Point(0.0, 15.0), 0.0, 0.0),
	max_pos(0.0, 0.0),
	h_slider(0),
	v_slider(0)
{
	h_scrol.sprite = &sprite;
	h_scrol.texture = &texture;
	resMovUpdate();
	header_rect.setFillColor(Color(220, 220, 220));

	h_rect.setFillColor(Color(180, 180, 180));
	v_rect.setFillColor(Color(180, 180, 180));
	inter_hv_rect.setFillColor(Color(160, 160, 160));
	inter_hv_rect.setSize(Vector2f(10.0, 10.0));
	//view_rect.setOrigin(0.0, -15.0); //setorigin ������
	view_rect.setFillColor(Color::Black);
	view_rect.setOutlineThickness(1.0);
	view_rect.setOutlineColor(Color(220, 220, 220));
	resizeUpdate();
	viewUpdate();
}

SubWindow::~SubWindow()
{
}

void SubWindow::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	int i;
	MouseData timed_md = wm_dat.md;
	timed_md.mp -= box.position;
	h_scrol.update(wm_dat, window);
	for (i = 0; i < 4; i++)
	{
		grabs[i].update(timed_md);
	}
	if (grabs[0].is_grabbed == 1)
	{
		box.position = grabs[0].moved_box.position + box.position;
		//moveUpdate();
		viewUpdate();
	}
	else
	{
		if (grabs[1].is_grabbed == 1)
		{
			box.width -= grabs[1].moved_box.position.x;
			box.position.x = grabs[1].moved_box.position.x + box.position.x;
			resizeUpdate();
			viewUpdate();
		}
		if (grabs[2].is_grabbed == 1)
		{
			box.width = grabs[2].moved_box.position.x + 2.0;
			resizeUpdate();
			viewUpdate();
		}
		if (grabs[3].is_grabbed == 1)
		{
			box.height = grabs[3].moved_box.position.y + 2.0;
			resizeUpdate();
			viewUpdate();
		}
	}
	for (i = 0; i < elements.size(); i++)
	{
		WMInterfaceData timed_wm_dat = wm_dat;
		timed_wm_dat.md.mp -= view_rect.getPosition();
		timed_wm_dat.md.mp += Point(sprite.getTextureRect().left, sprite.getTextureRect().top);
		elements[i]->update(timed_wm_dat, window);
	}
}

void SubWindow::draw(RenderTarget* target)
{
	int i;
	target->draw(header_rect);
	target->draw(view_rect);
	if (v_slider == 1)
	{
		target->draw(v_rect);
	}
	if (h_slider == 1)
	{
		target->draw(h_rect);
		h_scrol.draw(target);
	}
	if (v_slider == 1 && h_slider == 1)
	{
		target->draw(inter_hv_rect);
	}
	texture.clear(Color::Black);
	for (i = 0; i < elements.size(); i++)
	{
		elements[i]->draw(&texture);
	}
	texture.display();
	sprite.setPosition(view_rect.getPosition().x, view_rect.getPosition().y);


	float w = view_rect.getSize().x, h = view_rect.getSize().y;
	if (w > texture.getSize().x)
	{
		w = texture.getSize().x;
	}
	if (h > texture.getSize().y)
	{
		h = texture.getSize().y;
	}
	sprite.setTextureRect(IntRect(sprite.getTextureRect().left, sprite.getTextureRect().top, w, h));
	//std::cout << view_rect.getPosition().x << ":" << view_rect.getPosition().y << "\n";
	sprite.setTexture(texture.getTexture());
	target->draw(sprite);
	/*
	RectangleShape test_rect(Vector2f(grabs[2].box.width, grabs[2].box.height));
	test_rect.setPosition(grabs[2].box.position.x + box.position.x, grabs[2].box.position.y + box.position.y);
	test_rect.setFillColor(Color::Red);
	window.draw(test_rect);
	*/
}

void SubWindow::resizeUpdate()
{
	header_box.width = box.width;
	header_box.height = 15.0;
	view_box.width = box.width;
	view_box.height = box.height - 15.0;
	grabs[0].box = header_box;
	grabs[1].box = BoundingBox(Point(-2.0, -2.0), 5.0, box.height + 4.0);
	grabs[2].box = BoundingBox(Point(box.width - 2.0, -2.0), 5.0, box.height + 4.0);
	grabs[3].box = BoundingBox(Point(-2.0, box.height - 2.0), box.width + 2.0, 5.0);
	slideUpdate();
}

void SubWindow::moveUpdate()
{
}

void SubWindow::resMovUpdate()
{
	resizeUpdate();
	moveUpdate();
}

void SubWindow::viewUpdate()
{
	header_rect.setSize(Vector2f(header_box.width, header_box.height));
	view_rect.setSize(Vector2f(view_box.width - 2.0, view_box.height - 2.0));

	header_rect.setPosition(box.position.x, box.position.y);
	view_rect.setPosition(box.position.x + 1.0, box.position.y + 16.0);

	h_rect.setPosition(view_box.getLeft() + box.position.x, view_box.getDown() + box.position.y);////
	h_scrol.setPosition(Point(view_box.getLeft() + box.position.x, view_box.getDown() + box.position.y));

	v_rect.setPosition(view_box.getRight() + box.position.x, view_box.getUp() + box.position.y);
	inter_hv_rect.setPosition(view_box.getRight() + box.position.x, view_box.getDown() + box.position.y);
}

void SubWindow::slideUpdate()
{
	/*
	if (texture.getSize().x > view_rect.getSize().x)
	{
		h_slider = 1;
		if (texture.getSize().y > (view_rect.getSize().y - 10.0))
		{
			v_slider = 1;
		}
		else
		{
			v_slider = 0;
		}
	}
	else
	{
		h_slider = 0;
		if (texture.getSize().y > view_rect.getSize().y)
		{
			v_slider = 1;
		}
		else
		{
			v_slider = 0;
		}
	}

	if (texture.getSize().y > view_rect.getSize().y)
	{
		v_slider = 1;
		if (texture.getSize().x > (view_rect.getSize().x - 10.0))
		{
			h_slider = 1;
		}
		else
		{
			h_slider = 0;
		}
	}
	else
	{
		v_slider = 0;
		if (texture.getSize().x > view_rect.getSize().x)
		{
			h_slider = 1;
		}
		else
		{
			h_slider = 0;
		}
	}
	*/
	if (texture.getSize().x >= view_box.width - 1.0)
	{
		h_slider = 1;
		if (texture.getSize().y >= (view_box.height - 11.0)) //������� �� - 10.0 - 1.0, ��� 1.0 - �������� � ������ ������ �������
		{
			v_slider = 1;
		}
		else
		{
			v_slider = 0;
		}
	}
	else
	{
		h_slider = 0;
		if (texture.getSize().y >= view_box.height - 1.0)
		{
			v_slider = 1;
			if (texture.getSize().x >= (view_box.width - 11.0))
			{
				h_slider = 1;
			}
			else
			{
				h_slider = 0;
			}
		}
		else
		{
			v_slider = 0;
		}
	}

	if (v_slider == 1)
	{
		view_box.width -= 10.0;
	}
	if (h_slider == 1)
	{
		view_box.height -= 10.0;
		//h_rect.setPosition(view_box.getLeft() + box.position.x, view_box.getDown() + box.position.y);
		h_rect.setSize(Vector2f(view_box.width, 10.0));////
		h_scrol.setSize(Point(view_box.width, 10.0));
		viewUpdate(); //��������� �� ����������
	}
	if (v_slider == 1)
	{
		//v_rect.setPosition(view_box.getRight() + box.position.x, view_box.getUp() + box.position.y);
		v_rect.setSize(Vector2f(10.0, view_box.height));
		viewUpdate(); //��������� �� ����������
	}
}

void SubWindow::spriteCorrection()
{
	IntRect rect = sprite.getTextureRect();
	if ((rect.left + rect.width) > texture.getSize().x)
	{
		rect.left = texture.getSize().x - rect.width;
	}
	if (rect.left < 0.0)
	{
		rect.left = 0.0;
	}

	if ((rect.top + rect.height) > texture.getSize().y)
	{
		rect.top = texture.getSize().y - rect.height;
	}
	if (rect.top < 0.0)
	{
		rect.top = 0.0;
	}
	sprite.setTextureRect(rect);
}

void SubWindow::load(Element* element)
{
	elements.push_back(element);
	if (element->box.getRight() > max_pos.x) //�������� resizeUpdate() ����� �����
	{
		max_pos.x = element->box.getRight();
	}
	if (element->box.getDown() > max_pos.y)
	{
		max_pos.y = element->box.getDown();
	}
	texture.create(max_pos.x, max_pos.y);
	slideUpdate();
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Scroller::Scroller()
{
	rect.setFillColor(Color(200, 200, 200));
	scrol_rect.setFillColor(Color(120, 120, 120));
}
Scroller::Scroller(BoundingBox _box, Sprite* _sprite, RenderTexture* _texture) :
	box(_box),
	sprite(_sprite),
	texture(_texture),
	rect(Vector2f(_box.width, _box.height))
{
	rect.setPosition(_box.position.x, _box.position.y);
	rect.setFillColor(Color(200, 200, 200));
	scrol_rect.setFillColor(Color(160, 160, 160));
	modelUpdate();
}

Scroller::~Scroller()
{
}

void Scroller::update(WMInterfaceData& wm_dat, RenderWindow& window)
{
	scrol_box.update(wm_dat.md);
	if (scrol_box.is_grabbed == 1)
	{
		float p1 = sprite->getTextureRect().left;
		float w1 = sprite->getTextureRect().width;
		float w2 = texture->getSize().x;
		float op = scrol_box.moved_box.position.x - box.position.x - 1.0;
		float ow = box.width - 2.0;
		float np, nw;
		sprite->setTextureRect(IntRect(w2 * (op / ow), sprite->getTextureRect().top, sprite->getTextureRect().width, sprite->getTextureRect().height));
	}

	IntRect rect = sprite->getTextureRect();
	if ((rect.left + rect.width) > texture->getSize().x)
	{
		rect.left = texture->getSize().x - rect.width;
	}
	if (rect.left < 0.0)
	{
		rect.left = 0.0;
	}

	if ((rect.top + rect.height) > texture->getSize().y)
	{
		rect.top = texture->getSize().y - rect.height;
	}
	if (rect.top < 0.0)
	{
		rect.top = 0.0;
	}
	sprite->setTextureRect(rect);
	modelUpdate(); //������� ���������������� modelUpdate()
}

void Scroller::draw(RenderTarget* target)
{
	target->draw(rect);
	target->draw(scrol_rect);
}

void Scroller::setSize(Point _size)
{
	box.width = _size.x;
	box.height = _size.y;
	modelUpdate();
}

void Scroller::setPosition(Point _position)
{
	box.position = _position;
	modelUpdate();
}

Point Scroller::getSize()
{
	return Point(box.width, box.height);
}

Point Scroller::getPosition()
{
	return box.position;
}

void Scroller::modelUpdate()
{
	float p1 = sprite->getTextureRect().left;
	float w1 = sprite->getTextureRect().width;
	float w2 = texture->getSize().x;
	float op = box.position.x + 1.0;
	float ow = box.width - 2.0;
	float np, nw;
	nw = ow * (w1 / w2);
	np = (p1 / w2) * ow + op;
	scrol_rect.setPosition(np, box.position.y + 1.0);
	scrol_rect.setSize(Vector2f(nw, box.height - 2.0));
	scrol_box.box.position = Point(np, box.position.y + 1.0);
	scrol_box.box.width = nw;
	scrol_box.box.height = box.height - 2.0;
}
