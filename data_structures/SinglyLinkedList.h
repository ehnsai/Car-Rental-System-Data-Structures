#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <string>

using namespace std;

template <typename T>
struct SNode
{
    T data;
    SNode<T>* next;

    SNode(T value)
    {
        data = value;
        next = nullptr;
    }
};

template <typename T>
class SinglyLinkedList
{
private:
    SNode<T>* head;
    int count;

public:
    SinglyLinkedList()
    {
        head = nullptr;
        count = 0;
    }

    ~SinglyLinkedList()
    {
        SNode<T>* current = head;
        while (current != nullptr)
        {
            SNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void addToEnd(T value)
    {
        SNode<T>* newNode = new SNode<T>(value);

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            SNode<T>* current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }

        count++;
    }

    void addToBeginning(T value)
    {
        SNode<T>* newNode = new SNode<T>(value);
        newNode->next = head;
        head = newNode;
        count++;
    }

    bool removeByIndex(int index)
    {
        if (index < 0 || index >= count)
        {
            return false;
        }

        if (index == 0)
        {
            SNode<T>* temp = head;
            head = head->next;
            delete temp;
            count--;

            return true;
        }

        SNode<T>* current = head;
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }

        SNode<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
        count--;

        return true;
    }

    T* getByIndex(int index)
    {
        if (index < 0 || index >= count)
        {
            return nullptr;
        }

        SNode<T>* current = head;
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

    SNode<T>* getHead()
    {
        return head;
    }
};

#endif
