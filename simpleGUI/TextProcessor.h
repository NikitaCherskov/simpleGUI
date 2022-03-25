#pragma once
class TextProcessor
{
public:
	TextProcessor();
	~TextProcessor();
	void update(WMInterfaceData& wm_dat, RenderWindow& window, Point local_mp);
	void textUpdate();
	void draw(RenderTarget& target);
	int positionConverter(float position, float* cursor_position);
	void getHlBounds(float* l, float* r, float* c);
	void move(Point distance);
	void setPosition(Point distance);
	Point text_position;
	BoundingBox box;
	Text text;
	bool is_hl;
	int second_hlcursor;
	int first_hlcursor;
	float second_hlposition;
private:
	void textPositionUpdate();
};