#pragma once
#include "simpleGUI.h"
#include "GUITimer.h"


class numMark
{
public:
	numMark();
	numMark(BoundingBox _symb_box);
	~numMark();
	BoundingBox symb_box;
};

class posMark
{
public:
	posMark();
	posMark(BoundingBox _symb_box, int _symb_num);
	~posMark();
	BoundingBox symb_box;
	int symb_num;
};

class StrProc
{
public:
	StrProc();
	StrProc(const String& _str);
	~StrProc();
	BoundingBox getFromNum(int num);
	void getFromPos(float pos, BoundingBox* box_write = NULL, int* num_write = NULL);
	void deleteSymbols(int _pos, int _size);
	//getCentringFromPos(...);
	void updateMarks();
	String str;
private:
	std::vector<numMark> symb_nums;
	std::vector<posMark> symb_poses;
	int period_num;
	float period_pos;
};

/*
class TbxMover
{
public:
	TbxMover(const String* _str, BoundingBox _symb_box, int _symb_num, Point _base_pos);
	TbxMover(const String* _str, Point _base_pos);
	~TbxMover();
	void fromPosition(float position);
	void fromNum(int num);
	void moveNext();
	void movePrev();
	void moveFromNum(int amount = 1);
	void moveFromDist(float dist);


	void setBasePos(Point _base_pos);
	Point getBasePos();

	void setStringPtr(const String* _str, BoundingBox _symb_box, int _symb_num);
	void stringChange(BoundingBox _symb_box, int _symb_num);

	int getSymbNum();
	BoundingBox getSymbBox();


	//void strChanget(BoundingBox _symb_box, int _symb_num);
private:
	int symb_num;
	BoundingBox symb_box;
	const String* str;
	Point base_pos; 
};
*/
class TbxProc
{
public:
	TbxProc(BoundingBox _box /*возможно это лишнее*/, const String& _str);
	~TbxProc();
	void mouseEvent(BoundingBox _box, MouseData md);
	void mandatoryUpdate();
	void backspaceEvent();
	void textureUpdate();
	void moveView(float x);
	void setViewPos(float x);
	void updateViews();
//	RenderTexture& getTexture();
//private:
	//TbxMover first_symb;

	BoundingBox first_hl_box;
	int first_hl_num;
	BoundingBox second_hl_box;
	int second_hl_num;

	float strPos;
	float strWidth;
	float txtPos;
	float txtWidth;
	float viewPos;
	float viewWidth;

	RenderTexture texture;
	Text txt;
	StrProc str;
	Metronome del_metr;
};
class TextBox : public ControlElement
{
public:
	//TextBox();
	TextBox(BoundingBox _box, const String& _str);
	~TextBox();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
private:
	RectangleShape rect;
	BoundingBox box;
	TbxProc proc;
	//BoundingBox box;
};