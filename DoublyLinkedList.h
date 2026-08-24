#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>

using namespace std;

template <typename T>
struct DNode
{
    T data;
    DNode<T>* next;
    DNode<T>* prev;

    DNode(T value)
    {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class DoublyLinkedList
{
private:
    DNode<T>* head;
    DNode<T>* tail;
    int count;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    ~DoublyLinkedList()
    {
        DNode<T>* current = head;
        while (current != nullptr)
        {
            DNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void addToEnd(T value)
    {
        DNode<T>* newNode = new DNode<T>(value);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        count++;
    }

    void addToBeginning(T value)
    {
        DNode<T>* newNode = new DNode<T>(value);

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        count++;
    }

    bool removeByIndex(int index)
    {
        if (index < 0 || index >= count)
        {
            return false;
        }

        DNode<T>* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        if (current->prev != nullptr)
        {
            current->prev->next = current->next;
        }
        else
        {
            head = current->next;
        }

        if (current->next != nullptr)
        {
            current->next->prev = current->prev;
        }
        else
        {
            tail = current->prev;
        }

        delete current;
        count--;

        return true;
    }

    T* getByIndex(int index)
    {
        if (index < 0 || index >= count)
        {
            return nullptr;
        }

        DNode<T>* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        return &(current->data);
    }

    int getCount()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    DNode<T>* getHead()
    {
        return head;
    }

    DNode<T>* getTail()
    {
        return tail;
    }
};

#endif