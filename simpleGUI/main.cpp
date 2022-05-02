#include <SFML/Graphics.hpp>
#include <vector>
#include "simpleGUI.h"

using namespace sf; // подключаем пространство имен sf

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(1000, 1000), "SFML Works!");
	Interface exp;
	exp.setWindow(window);
	BoundingBox box1(Point(10.0, 10.0), 200.0, 20.0);
	Button* btn;
	btn = new Button(box1);
	Label* lbl;
	lbl = new Label(Point(300.0, 300.0), 10);
	lbl->setString("1234567890abc");
	NumericLabel* nlb;
	float ftest = clock();
	nlb = new NumericLabel(Point(450.0, 202.0), 4, 2, &ftest);
	Slider* sld;
	BoundingBox box2(Point(10.0, 40.0), 200.0, 20.0);
	sld = new Slider(box2);
	BoundingBox box3(Point(500.0, 100.0), 200.0, 20.0);

	TextBox* tbx = new TextBox(BoundingBox(Point(500.0, 700.0), 200.0, 20.0), "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz");

	SubWindow* wnd = new SubWindow(BoundingBox(Point(10.0, 10.0), 200.0, 200.0));

	//btn->setString("abobus");
	exp.load(tbx);
	//exp.load(sld);
	//exp.load(btn);
	exp.load(lbl);
	exp.load(nlb);
	exp.load(wnd);
	wnd->load(btn);
	wnd->load(sld);

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		std::vector<Event> events;
		// Обрабатываем очередь событий в цикле
		Event e;
		while (window.pollEvent(e))
		{
			events.push_back(e);
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (e.type == Event::Closed)
				window.close(); // тогда закрываем его
			//if (e.type == Event::TextEntered)
			//	std::cout << e.text.unicode; // тогда закрываем его
		}
		// Установка цвета фона
		ftest -= clock();
		ftest = 1000.0 / ftest;
		window.clear();
		exp.update(events);
		exp.draw();
		// Отрисовка окна
		window.display();
		ftest = clock();
	}

	return 0;
}