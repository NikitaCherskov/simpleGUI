#include <SFML/Graphics.hpp>
#include "simpleGUI.h"

using namespace sf; // подключаем пространство имен sf

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(1000, 1000), "SFML Works!");
	Interface exp;
	exp.setWindow(window);
	BondingBox box1(Point(500.0, 520.0), Point(700.0, 500.0));
	BondingBox box2(Point(500.0, 620.0), Point(700.0, 600.0));
	Button* btn;
	btn = new Button(box1);
	//btn->setString("abobus");
	exp.load(btn);
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
		window.clear();
		exp.update();
		exp.draw();
		// Отрисовка окна
		window.display();
	}

	return 0;
}