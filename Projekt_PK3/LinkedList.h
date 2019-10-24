#pragma once

#include <iostream>
#include <string>

#include "LinkedListNode.h"
#include "LinkedListNode.cpp"


template<class T>
class LinkedList
{
public:
	void add(const T, const T, LinkedList<T>*);
	bool remove(const T, const T);
	void removeAll(const T);
	void change(const T, const T);		//zamiana elementu
	bool repeatControl(const T, const T);
	void getAll();
	T get(int);
	int getSize();

private:
	Vector<LinkedListNode<T>>list;
};