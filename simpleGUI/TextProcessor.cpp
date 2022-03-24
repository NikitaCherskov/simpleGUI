#include "simpleGUI.h"

TextProcessor::TextProcessor()
{
}

TextProcessor::~TextProcessor()
{
}

void TextProcessor::update(WMInterfaceData& wm_dat, RenderWindow& window, Point local_mp)
{
	if (wm_dat.now_lmp == 1)
	{
		if (wm_dat.prev_lmp == 0)
		{
			positionConverter(local_mp.x);
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

void TextProcessor::draw(RenderTarget& targer)
{
}

void TextProcessor::positionConverter(float position)
{
	int i;
	float lsbound;
	float rsbound;

	i = 0;
	lsbound = text.getPosition().x;
	rsbound = text.getPosition().x + text.getFont()->getGlyph(text.getString()[i], text.getCharacterSize(), 0, 0.0).advance;
	while (i < text.getString().getSize())
	{
		if (position < rsbound)
		{
			hlposition = lsbound;
			hlcursor = i;
			return;
		}
		i++;
		lsbound = rsbound;
		rsbound = rsbound + text.getFont()->getGlyph(text.getString()[i], text.getCharacterSize(), 0, 0.0).advance;
		if (i == 37)
		{
			int a = 0;
		}
	}

	hlposition = lsbound;
	hlcursor = i;

	return;

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
