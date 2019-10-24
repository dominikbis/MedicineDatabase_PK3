#pragma once

#include <iostream>

#include "Vector.h"
#include "Vector.cpp"


template<class T>
class LinkedListNode
{
public:
	LinkedListNode();
	LinkedListNode(const T, Vector<LinkedListNode>*);

	T element;
	Vector<LinkedListNode> *link;		//polaczone listy
};