#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
class Fonts
{
public:
	Fonts();
	~Fonts();
	const Font& getRobotoRegular() const;
private:
	Font roboto_reguar;
	Font roboto_mono;
};