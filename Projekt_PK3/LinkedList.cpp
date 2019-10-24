#include "LinkedList.h"


template<class T>
void LinkedList<T>::add(const T element, const T element2, LinkedList<T> *list2)
{
	list.push_back(LinkedListNode<T>(element2, &list2->list));
	list2->list.push_back(LinkedListNode<T>(element, &list));
}


template<class T>
bool LinkedList<T>::remove(const T element, const T element2)
{
	Vector<LinkedListNode<T>> *link = nullptr;

	for (int i = 0; i < list.getSize(); i++)
	{
		if (list[i].element == element2)
		{
			link = list[i].link;
			list.erase(i);

			for (int i = 0; i < link->getSize(); i++)
			{
				if ((*link)[i].element == element)
				{
					link->erase(i);
					return true;		//usuwa 1
				}
			}
		}
	}
	return false;
}


template<class T>
void LinkedList<T>::removeAll(const T element)
{
	Vector<LinkedListNode<T>> *link = nullptr;
	while (!list.empty())
	{
		link = list[list.getSize() - 1].link;
		list.erase(list.getSize() - 1);

		for (int i = 0; i < link->getSize(); i++)
		{
			if ((*link)[i].element == element)
			{
				link->erase(i);
				break;		//usuwa 1
			}
		}
	}
}


template<class T>
void LinkedList<T>::change(const T element, const T newElement)
{
	Vector<LinkedListNode<T>> *link = nullptr;
	for (int i = 0; i < list.getSize(); i++)
	{
		link = list[i].link;
		for (int i = 0; i < link->getSize(); i++)
		{
			if ((*link)[i].element == element)
			{
				(*link)[i].element = newElement;
				break;
			}
		}
	}
}


template<class T>
bool LinkedList<T>::repeatControl(const T element1, const T element2)
{
	if (element1 == element2)
		return true;
	for (int i = 0; i < list.getSize(); i++)
		if (list[i].element == element2)
			return true;
	return false;
}


template<class T>
inline void LinkedList<T>::getAll()
{
	for (int i = 0; i < list.getSize(); i++)
		std::cout << '-' << list[i].element << std::endl;
}


template<class T>
inline T LinkedList<T>::get(int pos)
{
	return list[pos].element;
}


template<class T>
inline int LinkedList<T>::getSize()
{
	return list.getSize();
}