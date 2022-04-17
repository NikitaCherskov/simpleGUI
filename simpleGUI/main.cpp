#include <SFML/Graphics.hpp>
#include "simpleGUI.h"

using namespace sf; // подключаем пространство имен sf

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(1000, 1000), "SFML Works!");
	Interface exp;
	exp.setWindow(window);
	BoundingBox box1(Point(500.0, 500.0), 200.0, 20.0);
	Button* btn;
	btn = new Button(box1);
	Label* lbl;
	lbl = new Label(Point(300.0, 300.0), 10);
	lbl->setString("1234567890abc");
	NumericLabel* nlb;
	float ftest = clock();
	nlb = new NumericLabel(Point(450.0, 202.0), 4, 2, &ftest);
	Slider* sld;
	BoundingBox box2(Point(500.0, 200.0), 200.0, 20.0);
	sld = new Slider(box2);
	BoundingBox box3(Point(500.0, 100.0), 200.0, 20.0);
	//btn->setString("abobus");
	exp.load(sld);
	exp.load(btn);
	exp.load(lbl);
	exp.load(nlb);
	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем его
		}
		// Установка цвета фона
		ftest -= clock();
		ftest = 1000.0 / ftest;
		window.clear();
		exp.update();
		exp.draw();
		// Отрисовка окна
		window.display();
		ftest = clock();
	}

	return 0;
}