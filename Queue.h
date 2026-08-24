#ifndef QUEUE_H
#define QUEUE_H

#include <string>

using namespace std;

template <typename T>
struct QueueNode
{
    T data;
    QueueNode<T>* next;

    QueueNode(T value)
    {
        data = value;
        next = nullptr;
    }
};

template <typename T>
class Queue
{
private:
    QueueNode<T>* front;
    QueueNode<T>* rear;
    int count;

public:
    Queue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    ~Queue()
    {
        while (front != nullptr)
        {
            QueueNode<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(T data)
    {
        QueueNode<T>* newNode = new QueueNode<T>(data);

        if (rear == nullptr)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }

        count++;
    }

    T dequeue()
    {
        T data = front->data;
        QueueNode<T>* temp = front;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;
        count--;

        return data;
    }

    T* peek()
    {
        if (front == nullptr)
        {
            return nullptr;
        }

        return &(front->data);
    }

    bool isEmpty()
    {
        return count == 0;
    }

    int getCount()
    {
        return count;
    }

    QueueNode<T>* getFront()
    {
        return front;
    }
};

#endif