#include "LinkedListNode.h"


template<class T>
LinkedListNode<T>::LinkedListNode() :link(nullptr)
{
}


template<class T>
LinkedListNode<T>::LinkedListNode(const T element, Vector<LinkedListNode> *list2) :element(element), link(list2)
{
}