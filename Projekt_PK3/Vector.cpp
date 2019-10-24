#include "Vector.h"


template<class T>
Vector<T>::Vector() :capacity(0), size(0), tab(nullptr)
{
}


template<class T>
Vector<T>::Vector(Vector<T> &vector)
{
	tab = new T[vector.capacity];

	for (int i = 0; i < vector.size; i++)
		this->tab[i] = vector.tab[i];

	this->capacity = vector.capacity;
	this->size = vector.size;
}


template<class T>
Vector<T>::Vector(Vector<T> &&vector) :capacity(std::move(vector.capacity)), size(std::move(vector.size)), tab(std::move(vector.tab))
{
}


template<class T>
Vector<T>::~Vector()
{
	delete[] tab;
}


template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T> &vector)
{
	delete[] tab;
	tab = new T[vector.capacity];

	for (int i = 0; i < vector.size; i++)
		this->tab[i] = vector.tab[i];

	this->capacity = vector.capacity;
	this->size = vector.size;
	return *this;
}


template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T> &&vector)
{
	delete[] tab;
	this->capacity = std::move(vector.capacity);
	this->size = std::move(vector.size);
	this->tab = std::move(vector.tab);
	return *this;
}


template<class T>
inline T& Vector<T>::operator[](const int index)
{
	return tab[index];
}


template<class T>
inline void Vector<T>::resize(const int newCapacity)
{
	T*buffor = new T[newCapacity];

	for (int i = 0; i < size; i++)
		buffor[i] = tab[i];

	delete[] tab;
	tab = buffor;
	capacity = newCapacity;
}


template<class T>
inline void Vector<T>::capacityOverflow()
{
	if (capacity <= size)
	{
		if (size)
			resize(capacity << 1);
		else
			resize(1);		//rozmiar poczatkowy tablicy
	}
}


template<class T>
void Vector<T>::push_back(const T &element)
{
	capacityOverflow();

	tab[size] = element;
	size++;
}


template<class T>
void Vector<T>::insert(const int index, const T &element)
{
	T buffor = element;
	capacityOverflow();
	
	size++;
	for (int i = index; i < size; i++)
		std::swap(tab[i], buffor);
}


template<class T>
void Vector<T>::erase(const int index)
{
	for (int i = index; i < size - 1; i++)
		tab[i] = tab[i + 1];

	size--;
}


template<class T>
inline int Vector<T>::getSize()
{
	return size;
}


template<class T>
inline bool Vector<T>::empty()
{
	if (size)
		return false;
	return true;
}