#pragma once

#include <iostream>


template<class T>
class Vector
{
public:
	Vector();
	Vector(Vector<T> &);
	Vector(Vector<T> &&);
	~Vector();

	Vector<T>& operator=(const Vector<T> &);
	Vector<T>& operator=(const Vector<T> &&);
	T& operator[](const int index);

	void push_back(const T &);
	void insert(const int, const T &);
	void erase(const int);
	int getSize();
	bool empty();

private:
	int capacity;
	int size;
	T* tab;

	void resize(const int);
	void capacityOverflow();
};