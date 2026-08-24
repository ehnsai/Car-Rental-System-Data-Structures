#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <string>

using namespace std;

template <typename T>
class PriorityQueue
{
private:
    T* heap;
    int* priorities;
    int capacity;
    int size;

    void swap(int i, int j)
    {
        T tempData = heap[i];
        heap[i] = heap[j];
        heap[j] = tempData;

        int tempPriority = priorities[i];
        priorities[i] = priorities[j];
        priorities[j] = tempPriority;
    }

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;

            if (priorities[index] < priorities[parent])
            {
                swap(index, parent);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyDown(int index)
    {
        while (true)
        {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && priorities[left] < priorities[smallest])
            {
                smallest = left;
            }

            if (right < size && priorities[right] < priorities[smallest])
            {
                smallest = right;
            }

            if (smallest != index)
            {
                swap(index, smallest);
                index = smallest;
            }
            else
            {
                break;
            }
        }
    }

public:
    PriorityQueue(int cap = 500)
    {
        capacity = cap;
        size = 0;
        heap = new T[capacity];
        priorities = new int[capacity];
    }

    ~PriorityQueue()
    {
        delete[] heap;
        delete[] priorities;
    }

    bool enqueue(T data, int priority)
    {
        if (size >= capacity)
        {
            return false;
        }

        heap[size] = data;
        priorities[size] = priority;
        heapifyUp(size);
        size++;

        return true;
    }

    T dequeue()
    {
        T result = heap[0];

        heap[0] = heap[size - 1];
        priorities[0] = priorities[size - 1];
        size--;

        if (size > 0)
        {
            heapifyDown(0);
        }

        return result;
    }

    T* peek()
    {
        if (size == 0)
        {
            return nullptr;
        }

        return &heap[0];
    }

    bool isEmpty()
    {
        return size == 0;
    }

    int getSize()
    {
        return size;
    }

    T* getHeap()
    {
        return heap;
    }

    int* getPriorities()
    {
        return priorities;
    }
};

#endif