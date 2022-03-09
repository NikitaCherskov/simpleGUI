#pragma once
#include <iostream>
template<class T>
class DoublyNode
{
public:
	DoublyNode(const T& element, DoublyNode<T>* my_prev, DoublyNode<T>* my_next);
	~DoublyNode();
	T stored;
	DoublyNode<T>* next;
	DoublyNode<T>* prev;
};

template<class T>
class DoublyLinkedList
{
public:
	//конструктор-деструктор
	DoublyLinkedList();
	~DoublyLinkedList();
	//изменение элементов
	T& getFront();
	T& getBack();
	T& operator[] (int num);
	//получение данных
	const T& getFront() const;
	const T& getBack() const;
	//const T& operator[] (int num) const;
	int getSize() const;
	//добавление элементов
	void pushFront(const T& element);
	void pushBack(const T& element);
	void pushNum(const T& element, int num);
	//удаление элементов
	void popFront();
	void popBack();
	void popNum(int num);
	void clear();
	//получить ноды
	DoublyNode<T>* getFrontNode();
	DoublyNode<T>* getBackNode();
private:
	void moveCurrent(int num);
	DoublyNode<T>* getFromNum(int num);
	void zeroPush(const T& element);
	void onePop();
	DoublyNode<T>* front;
	DoublyNode<T>* back;
	DoublyNode<T>* current;
	int current_num;
	int size;
};

//DoublyNode
template<class T>
DoublyNode<T>::DoublyNode(const T& element, DoublyNode<T>* my_prev, DoublyNode<T>* my_next) :
	stored(element),
	prev(my_prev),
	next(my_next)
{
	if (prev != NULL)
	{
		prev->next = this;
	}
	if (next != NULL)
	{
		next->prev = this;
	}
}
template<class T>
DoublyNode<T>::~DoublyNode()
{}

//DoublyLinkedList
//конструктор-деструктор
template<class T>
DoublyLinkedList<T>::DoublyLinkedList() :
	front(NULL),
	back(NULL),
	current(NULL),
	current_num(0),
	size(0)
{}
template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();
}
//изменение элементов
template<class T>
T& DoublyLinkedList<T>::getFront()
{
	return front->stored;
}
template<class T>
T& DoublyLinkedList<T>::getBack()
{
	return back->stored;
}
template<class T>
T& DoublyLinkedList<T>::operator[] (int num)
{
	moveCurrent(num);
	return current->stored;
}
//получение данных
template<class T>
const T& DoublyLinkedList<T>::getFront() const
{
	return front->stored;
}
template<class T>
const T& DoublyLinkedList<T>::getBack() const
{
	return back->stored;
}
//const T& operator[] (int num) const;
template<class T>
int DoublyLinkedList<T>::getSize() const
{
	return size;
}
//добавление элементов
template<class T>
void DoublyLinkedList<T>::pushFront(const T& element)
{
	if (size != 0)
	{
		front = new DoublyNode<T>(element, NULL, front);
		if (current_num != 0)
		{
			current_num++;
		}
		size++;
	}
	else
	{
		zeroPush(element);
	}
}
template<class T>
void DoublyLinkedList<T>::pushBack(const T& element)
{
	if (size != 0)
	{
		back = new DoublyNode<T>(element, back, NULL);
		size++;
	}
	else
	{
		zeroPush(element);
	}
}
template<class T>
void DoublyLinkedList<T>::pushNum(const T& element, int num)
{
	if (size != 0)
	{
		if (num > 1)
		{
			DoublyNode<T>* desired = getFromNum(num - 1);
			new DoublyNode<T>(element, desired, desired->next);
		}
		else
		{
			front = new DoublyNode<T>(element, NULL, front);
		}
		size++;
	}
	else
	{
		zeroPush(element);
	}
}
//удаление элементов
template<class T>
void DoublyLinkedList<T>::popFront()
{
	if (size > 1)
	{
		DoublyNode<T>* tmp = front;
		front = front->next;
		if (current_num == 0)
		{
			current = front;
		}
		else
		{
			current_num--;
		}
		delete tmp;
		size--;
	}
	else
	{
		onePop();
	}
}
template<class T>
void DoublyLinkedList<T>::popBack()
{
	if (size > 1)
	{
		DoublyNode<T>* tmp = back;
		back = back->prev;
		if (current_num == (size - 1))
		{
			current = back;
			current_num--;
		}
		delete tmp;
		size--;
	}
	else
	{
		onePop();
	}
}
template<class T>
void DoublyLinkedList<T>::popNum(int num)
{
	if (size > 1)
	{
		if (num > 0)
		{
			DoublyNode<T>* deleting = getFromNum(num);
			deleting->next->prev = deleting->prev;
			deleting->prev->next = deleting->next;
			if (current_num > num)
			{
				current_num--;
			}
			else if (current_num = num)
			{
				current = current->next;
			}
			delete deleting;
			size--;
		}
		else
		{
			DoublyNode<T>* tmp = front;
			front = front->next;
			if (current_num == 0)
			{
				current = front;
			}
			else
			{
				current_num--;
			}
			delete tmp;
			size--;
		}
	}
	else
	{
		onePop();
	}
}
template<class T>
void DoublyLinkedList<T>::clear()
{
	while (size != 0)
	{
		popBack();
	}
}
//получить ноды
template <class T>
DoublyNode<T>* DoublyLinkedList<T>::getFrontNode()
{
	return front;
}
template <class T>
DoublyNode<T>* DoublyLinkedList<T>::getBackNode()
{
	return back;
}

template<class T>
void DoublyLinkedList<T>::moveCurrent(int num)
{
	if (num - current_num == 1)
	{
		current = current->next;
		current_num++;
	}
	else if (num - current_num == -1)
	{
		current = current->prev;
		current_num--;
	}
	else
	{
		if (num < current_num)
		{
			if (num > current_num / 2)
			{
				while (current_num != num)
				{
					current = current->prev;
					current_num--;
				}
			}
			else
			{
				current = front;
				current_num = 0;
				while (current_num != num)
				{
					current = current->next;
					current_num++;
				}
			}
		}
		else
		{
			if (num < ((size - current_num) / 2) + current_num)
			{
				while (current_num != num)
				{
					current = current->next;
					current_num++;
				}
			}
			else
			{
				current = back;
				current_num = size - 1;
				while (current_num != num)
				{
					current = current->prev;
					current_num--;
				}
			}
		}
	}
}
template<class T>
DoublyNode<T>* DoublyLinkedList<T>::getFromNum(int num)
{
	if (num - current_num == 1)
	{
		return current->next;
	}
	else if (num - current_num == -1)
	{
		return current->prev;
	}
	else
	{
		DoublyNode<T>* desired;
		int desired_num;
		if (num < current_num)
		{
			if (num > current_num / 2)
			{
				desired = current;
				desired_num = current_num;
				while (desired_num != num)
				{
					desired = desired->prev;
					desired_num--;
				}
			}
			else
			{
				desired = front;
				desired_num = 0;
				while (desired_num != num)
				{
					desired = desired->next;
					desired_num++;
				}
			}
		}
		else
		{
			if (num < ((size - current_num) / 2) + current_num)
			{
				desired = current;
				desired_num = current_num;
				while (desired_num != num)
				{
					desired = desired->next;
					desired_num++;
				}
			}
			else
			{
				desired = back;
				desired_num = size - 1;
				while (desired_num != num)
				{
					desired = desired->prev;
					desired_num--;
				}
			}
		}
		return desired;
	}
}
template<class T>
void DoublyLinkedList<T>::zeroPush(const T& element)
{
	current = front = back = new DoublyNode<T>(element, NULL, NULL);
	current_num = 0;
	size = 1;
}
template<class T>
void DoublyLinkedList<T>::onePop()
{
	delete front;
	front = NULL;
	back = NULL;
	current = NULL;
	size = 0;
	current_num = 0;
}