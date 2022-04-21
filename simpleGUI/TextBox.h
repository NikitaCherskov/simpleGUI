#pragma once
#include "simpleGUI.h"
class SymbMark
{
public: 
	SymbMark();
	SymbMark(BoundingBox _box, int _num);
	~SymbMark();
	BoundingBox box;
	int num;
};
class StrProc
{
public:
	StrProc();
	StrProc(const std::string& _str);
	~StrProc();
	void setString(const std::string& _str);
	void posToBox(float position, BoundingBox* _box, int* _num);
	BoundingBox numToBox(int num, BoundingBox* _box);
private:
	std::string str;
	std::vector<SymbMark> marks;
};
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
class TbxProc
{
public:
	TbxProc(BoundingBox _box /*�������� ��� ������*/, const String& _str);
	~TbxProc();
	void update(BoundingBox _box, MouseData md);
	void textureUpdate();
//	RenderTexture& getTexture();
//private:
	TbxMover first_symb;
	TbxMover first_hl;
	TbxMover second_hl;
	RenderTexture texture;
	Text txt;
	String str;
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