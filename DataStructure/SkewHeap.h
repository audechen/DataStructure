#ifndef SKEWHEAP_H_INCLUDED
#define SKEWHEAP_H_INCLUDED

#include <iostream>
using namespace std;

template<class T>
struct SkewNode
{
public:
    T key;
    SkewNode* left;
    SkewNode* right;
    SkewNode(T value, SkewNode* l, SkewNode* r):
        key(value), left(l), right(r){}
};

template<class T>
class SkewHeap
{
private:
    SkewNode<T>* mRoot;
public:
    SkewHeap();
    ~SkewHeap();

    void preOrder();
    void inOrder();
    void postOrder();

    void merge(SkewHeap<T>* other);
    void insert(T key);
    void remove();
    void destory();
    void print();
private:
    void preOrder(SkewNode<T>* heap) const;
    void inOrder(SkewNode<T>* heap) const;
    void postOrder(SkewNode<T>* heap) const;

    void swapNode(SkewNode<T>* &x, SkewNode<T>* &y);
    SkewNode<T>* merge(SkewNode<T>* &x, SkewNode<T>* &y);
    void destory(SkewNode<T>* &heap);
    void print(SkewNode<T>* heap, T key, int direction);
};

template<class T>
SkewHeap<T>::SkewHeap():mRoot(NULL){}

template<class T>
SkewHeap<T>::~SkewHeap()
{
    destory(mRoot);
}

template<class T>
void SkewHeap<T>::preOrder(SkewNode<T>* heap) const
{
    if(heap != NULL)
    {
        cout << heap->key << " ";
        preOrder(heap->left);
        preOrder(heap->right);
    }
}

template<class T>
void SkewHeap<T>::preOrder()
{
    preOrder(mRoot);
}

template<class T>
void SkewHeap<T>::inOrder(SkewNode<T>* heap) const
{
    if(heap != NULL)
    {
        inOrder(heap->left);
        cout << heap->key << " ";
        inOrder(heap->right);
    }
}

template<class T>
void SkewHeap<T>::inOrder()
{
    inOrder(mRoot);
}

template<class T>
void SkewHeap<T>::postOrder(SkewNode<T>* heap) const
{
    if(heap != NULL)
    {
        postOrder(heap->left);
        postOrder(heap->right);
        cout << heap->key << " ";
    }
}

template<class T>
void SkewHeap<T>::postOrder()
{
    postOrder(mRoot);
}

template<class T>
void SkewHeap<T>::swapNode(SkewNode<T>* &x, SkewNode<T>* &y)
{
    SkewNode<T>* tmp = x;
    x = y;
    y = tmp;
}

template<class T>
SkewNode<T>* SkewHeap<T>::merge(SkewNode<T>* &x, SkewNode<T>* &y)
{
    if(x == NULL)
        return y;
    if(y == NULL)
        return x;
    if(x->key > y->key)
        swapNode(x, y);
    SkewNode<T>* tmp = merge(x->right, y);
    x->right = x->left;
    x->left = tmp;
    return x;
}

template<class T>
void SkewHeap<T>::merge(SkewHeap<T>* other)
{
    mRoot = merge(mRoot, other->mRoot);
}

template<class T>
void SkewHeap<T>::insert(T key)
{
    SkewNode<T> * node;
    node = new SkewNode<T>(key, NULL, NULL);
    if(node == NULL)
    {
        cout << "Error: create node failed!!!" << endl;
        return;
    }
    mRoot = merge(mRoot, node);
}
template<class T>
void SkewHeap<T>::remove()
{
    if(mRoot == NULL)
        return;
    SkewNode<T>* l = mRoot->left;
    SkewNode<T>* r = mRoot->right;
    delete mRoot;
    mRoot = merge(l, r);
}

template<class T>
void SkewHeap<T>::destory(SkewNode<T>* &heap)
{
    if(heap == NULL)
        return;
    if(heap->left != NULL)
        destory(heap->left);
    if(heap->right != NULL)
        destory(heap->right);
    delete heap;
}

template<class T>
void SkewHeap<T>::destory()
{
    destory(mRoot);
}

template<class T>
void SkewHeap<T>::print(SkewNode<T>* heap, T key, int direction)
{
    if(heap != NULL)
    {
        if(direction == 0)
            cout << heap->key << " is root" << endl;
        else
            cout << heap->key << " is " << key << "'s " << (direction==1? "right child": "left child") << endl;
        print(heap->left, heap->key, -1);
        print(heap->right, heap->key, 1);
    }
}

template<class T>
void SkewHeap<T>::print()
{
    if(mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}
#endif // SKEWHEAP_H_INCLUDED
