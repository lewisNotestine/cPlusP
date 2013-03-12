#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
	first = last = 0;
	listLen = 0;
}
LinkedList::~LinkedList()
{
}
void LinkedList::AddLinkToBack(void* ptr)
{
	
		Node* Nx = new Node; 

		//shift the prev and data pointers
		Nx->data = ptr;
		Nx->prev = last;
		
		if (listLen > 0) //shift the next or first pointer
		{
			last->next = Nx;
		}
		else //if this is the first object
		{
			first = Nx;
		}

		last = Nx;
		listLen++;
	
}
void* LinkedList::RemoveLinkFromFront()
{
	Node *ptr = 0;
	void *ptr1 = 0;

	if (listLen == 1)
	{
		ptr = first;
		first = last = 0;
	}
	else if (listLen > 1)
	{
		ptr = first;
		first = first -> next;
		first -> prev = 0;
		
	}

	listLen--;
	ptr1 = ptr->data;
	delete ptr;
	return ptr1;
}
Node* LinkedList::GetFirstNode()
{
	return first;
}
long LinkedList::GetListLength()
{
	return listLen;
}

Node* LinkedList::GetLastNode()
{
	return last;
}

void* LinkedList::RemoveThisLink(Node* node)
{
	Node* ptr = 0;
	void *ptr1 = 0;

	if (listLen == 1)
	{
		first = last = 0;
	}
	else if (node->prev == 0)
	{
		ptr = first;
		first = first -> next;
		first -> prev = 0;
	}
	else if (node->next == 0)
	{
		ptr = last;
		last = last ->prev;
		last -> next = 0;
	}
	else
	{
		ptr = node;
		ptr = ptr ->prev;
		ptr ->next = ptr->next->next;
		ptr = ptr->next->next;
		ptr ->prev = ptr->prev->prev;
	}

	listLen--;
	ptr1 = ptr->data;
	delete node;
	return ptr1;
}
