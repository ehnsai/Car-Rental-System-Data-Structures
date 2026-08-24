#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

using namespace std;

template <typename T>
struct HashNode
{
    string key;
    T data;
    bool isOccupied;
    bool isDeleted;
    HashNode()
    {
        key = "";
        isOccupied = false;
        isDeleted = false;
    }
};

template <typename T>
class HashTable
{
private:
    HashNode<T>* table;
    int tableSize;
    int itemCount;
    int hashFunction(string key)
    {
        unsigned long hash = 0;
        for (int i = 0; i < key.length(); i++)
        {
            hash = hash * 31 + key[i];
        }
        return hash % tableSize;
    }

    int probe(int index, int attempt)
    {
        return (index + attempt) % tableSize;
    }

public:
    HashTable(int size = 1000)
    {
        tableSize = size;
        itemCount = 0;
        table = new HashNode<T>[tableSize];
    }

    ~HashTable()
    {
        delete[] table;
    }

    bool insert(string key, T data)
    {
        if (itemCount >= tableSize * 0.7)
        {
            return false;
        }

        int index = hashFunction(key);
        int attempt = 0;

        while (attempt < tableSize)
        {
            int currentIndex = probe(index, attempt);

            if (!table[currentIndex].isOccupied || table[currentIndex].isDeleted)
            {
                table[currentIndex].key = key;
                table[currentIndex].data = data;
                table[currentIndex].isOccupied = true;
                table[currentIndex].isDeleted = false;
                itemCount++;

                return true;
            }

            if (table[currentIndex].key == key)
            {
                table[currentIndex].data = data;

                return true;
            }

            attempt++;
        }

        return false;
    }

    T* search(string key)
    {
        int index = hashFunction(key);
        int attempt = 0;

        while (attempt < tableSize)
        {
            int currentIndex = probe(index, attempt);

            if (!table[currentIndex].isOccupied && !table[currentIndex].isDeleted)
            {
                return nullptr;
            }

            if (table[currentIndex].isOccupied && !table[currentIndex].isDeleted
                && table[currentIndex].key == key)
            {
                return &(table[currentIndex].data);
            }

            attempt++;
        }

        return nullptr;
    }

    bool remove(string key)
    {
        int index = hashFunction(key);
        int attempt = 0;

        while (attempt < tableSize)
        {
            int currentIndex = probe(index, attempt);

            if (!table[currentIndex].isOccupied && !table[currentIndex].isDeleted)
            {
                return false;
            }

            if (table[currentIndex].isOccupied && table[currentIndex].key == key)
            {
                table[currentIndex].isDeleted = true;
                itemCount--;

                return true;
            }

            attempt++;
        }

        return false;
    }

    bool exists(string key)
    {
        return search(key) != nullptr;
    }

    int getCount()
    {
        return itemCount;
    }

    HashNode<T>* getTable()
    {
        return table;
    }

    int getTableSize()
    {
        return tableSize;
    }
};

#endif
