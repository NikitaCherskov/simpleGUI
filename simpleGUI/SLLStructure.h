#pragma once
//SinglyLinkedList
template <class T>
class SinglyNode
{
public:
	SinglyNode(const T& element, SinglyNode* my_prev, SinglyNode* my_next);
	~SinglyNode();
	T stored;
	SinglyNode<T>* next;
};
template <class T>
class SinglyLinkedList
{
public:
	//конструктор-деструктор
	SinglyLinkedList();
	~SinglyLinkedList();
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
	SinglyNode<T>* getFrontNode();
	SinglyNode<T>* getBackNode();
private:
	void moveCurrent(int num);
	SinglyNode<T>* getFromNum(int num);
	void zeroPush(const T& element);
	void onePop();
	SinglyNode<T>* front;
	SinglyNode<T>* back;
	SinglyNode<T>* current;
	int current_num;
	int size;
};

//SinglyNode
//конструктор-деструктор
template <class T>
SinglyNode<T>::SinglyNode(const T& element, SinglyNode* my_prev, SinglyNode* my_next) :
	stored(element),
	next(my_next)
{
	if (my_prev != NULL)
	{
		my_prev->next = this;
	}
}
template <class T>
SinglyNode<T>::~SinglyNode()
{}

//SinglyLinkedList
//конструктор-деструктор

template <class T>
SinglyLinkedList<T>::SinglyLinkedList() :
	front(NULL),
	back(NULL),
	current(NULL),
	current_num(0),
	size(0)
{}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	clear();
}

//изменение элементов
template <class T>
T& SinglyLinkedList<T>::getFront()
{
	return front->stored;
}

template <class T>
T& SinglyLinkedList<T>::getBack()
{
	return back->stored;
}

template <class T>
T& SinglyLinkedList<T>::operator[] (int num)
{
	moveCurrent(num);
	return current->stored;
}

//получение данных
template <class T>
const T& SinglyLinkedList<T>::getFront() const
{
	return front->stored;
}

template <class T>
const T& SinglyLinkedList<T>::getBack() const
{
	return back->stored;
}

/*
template <class T>
const T& SinglyLinkedList<T>::operator[] (int num) const //проверить на работу, возможно превратить в const T& getLast() const
{
	moveCurrent(num);
	return current;
}
*/

template <class T>
int SinglyLinkedList<T>::getSize() const
{
	return size;
}
//добавление элементов
template <class T>
void SinglyLinkedList<T>::pushFront(const T& element)
{
	if (size != 0)
	{
		front = new SinglyNode<T>(element, NULL, front);
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

template <class T>
void SinglyLinkedList<T>::pushBack(const T& element)
{
	if (size != 0)
	{
		back = new SinglyNode<T>(element, back, NULL);
		size++;
	}
	else
	{
		zeroPush(element);
	}
}

template <class T>
void SinglyLinkedList<T>::pushNum(const T& element, int num)
{
	if (size != 0)
	{
		if (num > 1)
		{
			SinglyNode<T>* desired = getFromNum(num - 1);
			new SinglyNode<T>(element, desired, desired->next);
		}
		else
		{
			front = new SinglyNode<T>(element, NULL, front);
		}
		size++;
	}
	else
	{
		zeroPush(element);
	}
}

//удаление элементов
template <class T>
void SinglyLinkedList<T>::popFront()
{
	if (size > 1)
	{
		SinglyNode<T>* tmp = front;
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
	else if (size = 1)
	{
		onePop();
	}
}

template <class T>
void SinglyLinkedList<T>::popBack()
{
	if (size > 1)
	{
		SinglyNode<T>* desired = getFromNum(size - 2);
		delete back;
		back = desired;
		back->next = NULL;
		if (current_num == (size - 1))
		{
			current = desired;
			current_num--;
		}
		size--;
	}
	else if (size = 1)
	{
		onePop();
	}
}

template <class T>
void SinglyLinkedList<T>::popNum(int num)
{
	if (size > 1)
	{
		if (num > 0)
		{
			//а что, если num = size?
			SinglyNode<T>* desired = getFromNum(num - 1);
			SinglyNode<T>* tmp = desired->next;
			desired->next = desired->next->next;
			if (current_num > num)
			{
				current_num--;
			}
			else if (current_num == num)
			{
				current = desired;
				current_num--;
			}
			delete tmp;
			size--;
		}
		else
		{
			SinglyNode<T>* tmp = front;
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
	else if (size = 1)
	{
		onePop();
	}
}

template <class T>
void SinglyLinkedList<T>::clear()
{
	while (size > 0)
	{
		popFront();
	}
}

//получить ноды
template <class T>
SinglyNode<T>* SinglyLinkedList<T>::getFrontNode()
{
	return front;
}
template <class T>
SinglyNode<T>* SinglyLinkedList<T>::getBackNode()
{
	return back;
}

//внутренние функции
template <class T>
void SinglyLinkedList<T>::moveCurrent(int num)
{
	if (num - current_num == 1)
	{
		current = current->next;
		current_num++;
	}
	else
	{
		int i;
		if (num >= current_num)
		{
			for (i = current_num; i != num; i++)
			{
				current = current->next;
			}
			current_num = num;
		}
		else
		{
			current = front;
			for (i = 0; i != num; i++)
			{
				current = current->next;
			}
			current_num = num;
		}
	}
}

template <class T>
SinglyNode<T>* SinglyLinkedList<T>::getFromNum(int num)
{
	if (num - current_num == 1)
	{
		return current->next;
	}
	else
	{
		int i;
		SinglyNode<T>* desired;
		if (num >= current_num)
		{
			desired = current;
			for (i = current_num; i != num; i++)
			{
				desired = desired->next;
			}
		}
		else
		{
			desired = front;
			for (i = 0; i != num; i++)
			{
				desired = desired->next;
			}
		}
		return desired;
	}
}

template <class T>
void SinglyLinkedList<T>::zeroPush(const T& element)
{
	current = front = back = new SinglyNode<T>(element, NULL, NULL);
	current_num = 0;
	size = 1;
}

template <class T>
void SinglyLinkedList<T>::onePop()
{
	delete front;
	front = NULL;
	back = NULL;
	current = NULL;
	size = 0;
	current_num = 0;
}