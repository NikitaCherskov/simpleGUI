#pragma once
#include "simpleGUI.h"

class MouseLinker;
class MouseEventer;

class MouseLinker
{
public:
	MouseLinker();
	~MouseLinker();
	virtual void leftDownEvent();
	virtual void moveEvent();
	virtual void leftUpEvent();
};
class MouseEventer
{
public:
	MouseEventer();
	~MouseEventer();
	void update(Interface& _interface);
private:
	bool prev_left;
	MouseLinker* linker;
};