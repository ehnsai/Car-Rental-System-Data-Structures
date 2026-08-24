#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

using namespace std;

template <typename T>
struct AVLNode
{
    string key;
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;
    AVLNode(string k, T value)
    {
        key = k;
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

template <typename T>
class AVLTree
{
private:
    AVLNode<T>* root;
    int nodeCount;
    int getHeight(AVLNode<T>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->height;
    }

    int getBalance(AVLNode<T>* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    int maxHeight(int a, int b)
    {
        if (a > b)
        {
            return a;
        }
        return b;
    }

    AVLNode<T>* rightRotate(AVLNode<T>* y)
    {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = maxHeight(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = maxHeight(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x)
    {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = maxHeight(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = maxHeight(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode<T>* insertNode(AVLNode<T>* node, string key, T data)
    {
        if (node == nullptr)
        {
            nodeCount++;
            return new AVLNode<T>(key, data);
        }
        if (key < node->key)
        {
            node->left = insertNode(node->left, key, data);
        }
        else if (key > node->key)
        {
            node->right = insertNode(node->right, key, data);
        }
        else
        {
            node->data = data;
            return node;
        }
        node->height = 1 + maxHeight(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key) //LL
        {
            return rightRotate(node);
        }
        if (balance < -1 && key > node->right->key) // RR
        {
            return leftRotate(node);
        }
        if (balance > 1 && key > node->left->key) //LR
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) //RL
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    AVLNode<T>* findMinNode(AVLNode<T>* node)
    {
        AVLNode<T>* current = node;
        while (current->left != nullptr)
        {
            current = current->left;
        }

        return current;
    }

    AVLNode<T>* deleteNode(AVLNode<T>* node, string key)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (key < node->key)
        {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = deleteNode(node->right, key);
        }
        else
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                AVLNode<T>* temp = node->left ? node->left : node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }

                delete temp;
                nodeCount--;
            }
            else
            {
                AVLNode<T>* temp = findMinNode(node->right);
                node->key = temp->key;
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (node == nullptr)
        {
            return node;
        }

        node->height = 1 + maxHeight(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
        {
            return rightRotate(node);
        }

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = leftRotate(node->left);

            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
        {
            return leftRotate(node);
        }

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rightRotate(node->right);

            return leftRotate(node);
        }

        return node;
    }

    T* searchNode(AVLNode<T>* node, string key)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (key == node->key)
        {
            return &(node->data);
        }

        if (key < node->key)
        {
            return searchNode(node->left, key);
        }

        return searchNode(node->right, key);
    }

    void destroyTree(AVLNode<T>* node)
    {
        if (node != nullptr)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    AVLTree()
    {
        root = nullptr;
        nodeCount = 0;
    }

    ~AVLTree()
    {
        destroyTree(root);
    }

    void insert(string key, T data)
    {
        root = insertNode(root, key, data);
    }

    void remove(string key)
    {
        root = deleteNode(root, key);
    }

    T* search(string key)
    {
        return searchNode(root, key);
    }

    bool exists(string key)
    {
        return searchNode(root, key) != nullptr;
    }

    int getCount()
    {
        return nodeCount;
    }

    AVLNode<T>* getRoot()
    {
        return root;
    }
};

#endif