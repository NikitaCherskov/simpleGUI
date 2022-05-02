#pragma once
#include "simpleGUI.h"
#include "GUITimer.h"

bool isLetter(char c);

class NumMark
{
public:
	NumMark();
	NumMark(BoundingBox _symb_box);
	~NumMark();
	BoundingBox symb_box;
};

class PosMark
{
public:
	PosMark();
	PosMark(BoundingBox _symb_box, int _symb_num);
	~PosMark();
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
	void addSymbol(int _pos, wchar_t c);
	//getCentringFromPos(...);
	void updateMarks();
	String str;
private:
	std::vector<NumMark> symb_nums;
	std::vector<PosMark> symb_poses;
	int period_num;
	float period_pos;
};

class TbxProc
{
public:
	TbxProc(BoundingBox _box /*возможно это лишнее*/, const String& _str);
	~TbxProc();
	void mouseEvent(BoundingBox _box, MouseData md);
	void mandatoryUpdate();
	void backspaceEvent();
	void charInputEvent(wchar_t c);
	void textureUpdate();
	void moveView(float x);
	void setViewPos(float x);
	void updateViews();
	void noHlTextureUpdate();

	int getFirstHlNum();
	int getSecondHlNum();
	void setFirstHlNum(int num);
	void setSecondHlNum(int num);
	void firstToSecondNum();
	void specialMoveSecondRight();
	void specialMoveSecondLeft();
//	RenderTexture& getTexture();
//private:
	//TbxMover first_symb;

	BoundingBox first_hl_box;
	int first_hl_num;
	BoundingBox second_hl_box;
	int second_hl_num;

	float indent;
	float str_pos;
	float str_width;
	float txt_pos;
	float txt_width;
	float view_pos;
	float view_width;

	RenderTexture texture;
	Text txt;
	StrProc str;
	Metronome del_metr;
};
class TextBox : public Element
{
public:
	//TextBox();
	TextBox(BoundingBox _box, const String& _str);
	~TextBox();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderTarget* target);
private:
	bool focus;
	int hl_cursor_alpha;
	Metronome cursor_blinding;
	RectangleShape rect;
	BoundingBox box;
	TbxProc proc;
	//BoundingBox box;
};