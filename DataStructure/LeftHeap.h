#ifndef LEFTHEAP_H_INCLUDED
#define LEFTHEAP_H_INCLUDED

#include <iostream>
using namespace std;

template<class T>
struct LeftHeapNode
{
public:
    T key;
    int npl; //NULL Path Length
    LeftHeapNode *left;
    LeftHeapNode *right;
    LeftHeapNode(T value, LeftHeapNode* l, LeftHeapNode* r):
        key(value), npl(0), left(l), right(r){}
};

template<class T>
class LeftHeap
{
private:
    LeftHeapNode<T>* mRoot;
public:
    LeftHeap();
    ~LeftHeap();

    void preOrder();
    void inOrder();
    void postOrder();

    void merge(LeftHeap<T>* other);
    void insert(T key);
    void remove();
    void destory();
    void print();
private:
    void preOrder(LeftHeapNode<T>* heap) const;
    void inOrder(LeftHeapNode<T>* heap) const;
    void postOrder(LeftHeapNode<T>* heap) const;

    void swapNode(LeftHeapNode<T>* &x, LeftHeapNode<T>* &y);
    LeftHeapNode<T>* merge(LeftHeapNode<T>* &x, LeftHeapNode<T>* &y);
    LeftHeapNode<T>* insert(LeftHeapNode<T>* &heap, T key);
    LeftHeapNode<T>* remove(LeftHeapNode<T>* &heap);
    void destory(LeftHeapNode<T>* &heap);
    void print(LeftHeapNode<T>* heap, T key, int direction);
};

template<class T>
LeftHeap<T>::LeftHeap():mRoot(NULL){}

template<class T>
LeftHeap<T>::~LeftHeap()
{
    destory(mRoot);
}

template<class T>
void LeftHeap<T>::preOrder(LeftHeapNode<T>* heap) const
{
    if(heap != NULL)
    {
        cout << heap->key << " ";
        preOrder(heap->left);
        preOrder(heap->right);
    }
}
template<class T>
void LeftHeap<T>::preOrder()
{
    preOrder(mRoot);
}

template<class T>
void LeftHeap<T>::inOrder(LeftHeapNode<T>* heap) const
{
    if(heap != NULL)
    {
        inOrder(heap->left);
        cout << heap->key << " ";
        inOrder(heap->right);
    }
}

template<class T>
void LeftHeap<T>::inOrder()
{
    inOrder(mRoot);
}

template<class T>
void LeftHeap<T>::postOrder(LeftHeapNode<T>* heap) const
{
    if(heap != NULL)
    {
        postOrder(mRoot->left);
        postOrder(mRoot->right);
        cout << heap->key << " ";
    }
}

template<class T>
void LeftHeap<T>::postOrder()
{
    posrOrder(mRoot);
}

template<class T>
void LeftHeap<T>::swapNode(LeftHeapNode<T>* &x, LeftHeapNode<T>* &y)
{
    LeftHeapNode<T>* tmp = x;
    x = y;
    y = tmp;
}

template<class T>
LeftHeapNode<T>* LeftHeap<T>::merge(LeftHeapNode<T>* &x, LeftHeapNode<T>* &y)
{
    if(x == NULL)
        return y;
    if(y == NULL)
        return x;
    if(x->key > y->key)
        swapNode(x, y);
    x->right = merge(x->right, y);
    if(x->left == NULL || x->left->npl<x->right->npl)
        swapNode(x->left, x->right);
    if(x->right==NULL || x->left==NULL)
        x->npl = 0;
    else
        x->npl = (x->left->npl > x->right->npl)? (x->right->npl + 1): (x->left->npl + 1);
    return x;
}

template<class T>
void LeftHeap<T>::merge(LeftHeap<T>* other)
{
    mRoot = merge(mRoot, other->mRoot);
}

template<class T>
LeftHeapNode<T>* LeftHeap<T>::insert(LeftHeapNode<T>* &heap, T key)
{
    LeftHeapNode<T>* node;
    node  = new LeftHeapNode<T>(key, NULL, NULL);
    if(node == NULL)
    {
        cout << "Error: create node failed!" << endl;
        return heap;
    }
    return merge(mRoot, node);
}

template<class T>
void LeftHeap<T>::insert(T key)
{
    mRoot = insert(mRoot, key);
}

template<class T>
LeftHeapNode<T>* LeftHeap<T>::remove(LeftHeapNode<T>* &heap)
{
    if(heap == NULL)
        return NULL;
    LeftHeapNode<T>* l = heap->left;
    LeftHeapNode<T>* r = heap->right;
    delete heap;
    return merge(l, r);
}

template<class T>
void LeftHeap<T>::remove()
{
    mRoot = remove(mRoot);
}

template<class T>
void LeftHeap<T>::destory(LeftHeapNode<T>* &heap)
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
void LeftHeap<T>::destory()
{
    destory(mRoot);
}

template<class T>
void LeftHeap<T>::print(LeftHeapNode<T>* heap, T key, int direction)
{
    if(heap != NULL)
    {
        if(direction == 0)
            cout << heap->key << "(" << heap->npl << ")" << " is root" << endl;
        else
            cout << heap->key << "(" << heap->npl << ")" << " is " << key << "'s " <<
            (direction==1? "right child": "left child") << endl;
        print(heap->left, heap->key, -1);
        print(heap->right, heap->key, 1);
    }
}

template<class T>
void LeftHeap<T>::print()
{
    if(mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}


#endif // LEFTHEAP_H_INCLUDED
