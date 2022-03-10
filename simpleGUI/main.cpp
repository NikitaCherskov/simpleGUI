#include <SFML/Graphics.hpp>
#include "simpleGUI.h"

using namespace sf; // ���������� ������������ ���� sf

int main()
{
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(1000, 1000), "SFML Works!");
	Interface exp;
	exp.setWindow(window);
	BondingBox box1(Point(500.0, 520.0), Point(700.0, 500.0));
	BondingBox box2(Point(500.0, 620.0), Point(700.0, 600.0));
	Button* btn;
	btn = new Button(box1);
	//btn->setString("abobus");
	exp.load(btn);
	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				window.close(); // ����� ��������� ���
		}
		// ��������� ����� ����
		window.clear();
		exp.update();
		exp.draw();
		// ��������� ����
		window.display();
	}

	return 0;
}