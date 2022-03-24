#include "Fonts.h"
Fonts::Fonts()
{
	roboto_reguar.loadFromFile("Roboto-Regular.ttf");
	roboto_mono.loadFromFile("RobotoMono-VariableFont_wght.ttf");
}
Fonts::~Fonts()
{
}

const Font& Fonts::getRobotoRegular() const
{
	return roboto_reguar;
}