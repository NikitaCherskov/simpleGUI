#pragma once
#include "simpleGUI.h"
class TbxMover
{
public:
	TbxMover(const String* _str, BoundingBox _symb_box, int _symb_num, Point _base_pos);
	~TbxMover();
	void fromPosition(Point position);
	void fromNum(int num);
	void moveNext();
	void movePrev();
	void moveFromNum(int amount = 1);
	void moveFromDist(float dist);


	void setBasePos(Point _base_pos);
	Point getBasePos();

	void setStringPtr(const String* _str, BoundingBox _symb_box, int _symb_num);
	void stringChanget(BoundingBox _symb_box, int _symb_num);

	int getSymbNum();
	BoundingBox getSymbBox();


	//void strChanget(BoundingBox _symb_box, int _symb_num);
private:
	int symb_num;
	BoundingBox symb_box;
	String* str;
	Point base_pos; 
};
class TbxProc
{
public:
	TbxProc(const String _str, BoundingBox _box);
	~TbxProc();
	void update(MouseData md);
//	RenderTexture& getTexture();
//private:
	TbxMover first_symb;
	RenderTexture texture;
	Text txt;
	String str;
};
class TextBox
{
public:
	TextBox();
	TextBox(BoundingBox _box, const String _str);
	~TextBox();
	void update(WMInterfaceData& wm_dat, RenderWindow& window);
	void draw(RenderWindow& window);
private:
	TbxProc proc;
	BoundingBox box;
};