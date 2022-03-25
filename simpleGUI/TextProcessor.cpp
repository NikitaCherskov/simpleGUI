#include "simpleGUI.h"
#include "TextProcessor.h"

TextProcessor::TextProcessor():
	first_hlcursor(0),
	second_hlcursor(0)
{
}

TextProcessor::~TextProcessor()
{
}

void TextProcessor::update(WMInterfaceData& wm_dat, RenderWindow& window, Point local_mp)
{
	if (wm_dat.now_lmp == 1)
	{
		second_hlcursor = positionConverter(local_mp.x, &second_hlposition);
		if (wm_dat.prev_lmp == 0)
		{
			first_hlcursor = second_hlcursor;
		}
	}
	else
	{
	}
}

void TextProcessor::textUpdate()
{
	box.position = text.getPosition();
	box.width = text.getGlobalBounds().width;
	box.height = text.getGlobalBounds().height;
}

void TextProcessor::draw(RenderTarget& target)
{
}

int TextProcessor::positionConverter(float position, float* curosor_position) //выгл€дит кривовато и странно
{
	int i;
	float lsbound;
	float rsbound;
	i = 0;
	lsbound = text.getPosition().x;
	rsbound = text.getPosition().x + text.getFont()->getGlyph(text.getString()[i], text.getCharacterSize(), 0, 0.0).advance;
	while (i < text.getString().getSize())
	{
		if (position < rsbound - 2.0)
		{
			*curosor_position = lsbound;
			return i;
		}
		i++;
		lsbound = rsbound;
		rsbound = rsbound + text.getFont()->getGlyph(text.getString()[i], text.getCharacterSize(), 0, 0.0).advance;
	}

	*curosor_position = lsbound;

	return i;

	/*
	int i;
	float symbol_position;
	float symbol_width;
	symbol_position = text.getPosition().x;
	for (i = 0, symbol_width = 0.0; i < text.getString().getSize(); i++) //возможно убрать minpos
	{
		if (position < symbol_position)
		{
			hlposition = symbol_position;
			hlcursor = i;
			return;
		}
		symbol_width = text.getFont()->getGlyph(text.getString()[i], text.getCharacterSize(), 0).bounds.width;
		symbol_position += symbol_width;
	}
	hlposition = symbol_position;
	hlcursor = i;
	return;
	*/
}

void TextProcessor::getHlBounds(float* l, float* r, float* c)
{
	float fc, sc;
	int i;
	float* where_write;
	if (second_hlcursor > first_hlcursor)
	{
		fc = first_hlcursor;
		sc = second_hlcursor;
		where_write = r;
	}
	else
	{
		sc = first_hlcursor;
		fc = second_hlcursor;
		where_write = l;
	}
	*l = text.getPosition().x;
	for (i = 0; i < text.getString().getSize(); i++)
	{
		if (i >= fc)
		{
			break;
		}
		*l += text.getFont()->getGlyph(text.getString()[i], text.getCharacterSize(), 0, 0.0).advance;
	}
	*r = *l;
	for (; i < text.getString().getSize(); i++)
	{
		if (i >= sc)
		{
			break;
		}
		*r += text.getFont()->getGlyph(text.getString()[i], text.getCharacterSize(), 0, 0.0).advance;
	}
	*c = *where_write;
	return;
}
