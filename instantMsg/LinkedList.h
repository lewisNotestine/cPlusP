#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Node
{
	void* data;
	Node* prev;
	Node* next;

    Node()
    {
        data   = 0;
        prev   = 0;
        next   = 0;
    }
};


class LinkedList
{
private:
        Node* first;
        Node* last;
        long listLen;

public:
    LinkedList();
    ~LinkedList();
    void AddLinkToBack(void* ptr);
    void* RemoveLinkFromFront();
	void* RemoveLinkFromBack();
    Node* GetFirstNode();
	Node* GetLastNode();
    long GetListLength();
	void* RemoveThisLink(Node* node);
};

#endif