#ifndef BINOMIALHEAP_H_INCLUDED
#define BINOMIALHEAP_H_INCLUDED

#include <iostream>
using namespace std;

template<class T>
struct BinomialNode
{
public:
    T key;
    int degree;
    BinomialNode<T>* child;
    BinomialNode<T>* parent;
    BinomialNode<T>* next;
    BinomialNode(T value):
        key(value), degree(0), child(NULL), parent(NULL), next(NULL) {}
};

template<class T>
class BinomialHeap
{
private:
    BinomialNode<T>* mRoot;
public:
    BinomialHeap();
    ~BinomialHeap();

    void insert(T key);
    void update(T old_key, T new_key);
    void remove(T key);
    void extractMinimum();
    void combine(BinomialHeap<T>* other);

    T minimum();
    bool contains(T key);
    void print();
private:
    void link(BinomialNode<T>* child, BinomialNode<T>* root);
    BinomialNode<T>* merge(BinomialNode<T>* h1, BinomialNode<T>* h2);
    BinomialNode<T>* combine(BinomialNode<T>* h1, BinomialNode<T>* h2);
    BinomialNode<T>* reverse(BinomialNode<T>* root);
    BinomialNode<T>* extractMinimum(BinomialNode<T>* root);
    BinomialNode<T>* remove(BinomialNode<T>* root, T key);
    BinomialNode<T>* search(BinomialNode<T>* root, T key);
    void increaseKey(BinomialNode<T>* node, T key);
    void decreaseKey(BinomialNode<T>* node, T key);
    void updateKey(BinomialNode<T>* node, T key);
    void minimum(BinomialNode<T>* root, BinomialNode<T>* &prev_y, BinomialNode<T>* &y);
    void print(BinomialNode<T>* node, BinomialNode<T>* prev, int direction);
};

template<class T>
BinomialHeap<T>::BinomialHeap():mRoot(NULL){}

template<class T>
BinomialHeap<T>::~BinomialHeap(){}

template<class T>
void BinomialHeap<T>::minimum(BinomialNode<T>* root, BinomialNode<T>* &prev_y, BinomialNode<T>* &y)
{
    BinomialNode<T> *x, *prev_x;
    if(root == NULL)
        return;
    prev_x = root;
    x = root->next;
    prev_y = NULL;
    y = root;
    while(x != NULL)
    {
        if(x->key < y->key)
        {
            y = x;
            prev_y = prev_x;
        }
        prev_x = x;
        x = x->next;
    }
}

template<class T>
T BinomialHeap<T>::minimum()
{
    BinomialNode<T> *prev_y, *y;
    minimum(mRoot, prev_y, y);
    return y->key;
}

template<class T>
void BinomialHeap<T>::link(BinomialNode<T>* child, BinomialNode<T>* root)
{
    child->parent = root;
    child->next = root->child;
    root->child = child;
    root->degree++;
}

template<class T>
BinomialNode<T>* BinomialHeap<T>::merge(BinomialNode<T>* h1, BinomialNode<T>* h2)
{
    BinomialNode<T>* root = NULL;
    BinomialNode<T>** pos = &root;
    while(h1 && h2)
    {
        if(h1->degree < h2->degree)
        {
            *pos = h1;
            h1 = h1->next;
        }
        else
        {
            *pos = h2;
            h2 = h2->next;
        }
        pos = &(*pos)->next;
    }
    if(h1)
        *pos = h1;
    else
        *pos = h2;
    return root;
}

template<class T>
BinomialNode<T>* BinomialHeap<T>::combine(BinomialNode<T>* h1, BinomialNode<T>* h2)
{
    BinomialNode<T>* root;
    BinomialNode<T> *prev_x, *x, *next_x;
    root = merge(h1, h2);
    if(root == NULL)
        return NULL;
    prev_x = NULL;
    x = root;
    next_x = x->next;
    while(next_x != NULL)
    {
        if((x->degree != next_x->degree) ||
           (next_x->next!=NULL && next_x->degree==next_x->next->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else if(x->key <= next_x->key)
        {
            x->next = next_x->next;
            link(next_x, x);
        }
        else
        {
            if(prev_x == NULL)
                root = next_x;
            else
                prev_x->next = next_x;
            link(x, next_x);
            x = next_x;
        }
        next_x = x->next;
    }
    return root;
}

template<class T>
void BinomialHeap<T>::combine(BinomialHeap<T>* other)
{
    if(other!=NULL && other->mRoot!=NULL)
        mRoot = combine(mRoot, other->mRoot);
}

template<class T>
void BinomialHeap<T>::insert(T key)
{
    BinomialNode<T>* node;
    if(contains(key))
    {
        cout << "Error: the key(" << key << ") is existed already!" << endl;
        return;
    }
    node = new BinomialNode<T>(key);
    if(node == NULL)
        return;
    mRoot = combine(mRoot, node);
}

template<class T>
BinomialNode<T>* BinomialHeap<T>::reverse(BinomialNode<T>* root)
{
    BinomialNode<T>* next;
    BinomialNode<T>* tail = NULL;
    if(!root)
        return root;
    root->parent = NULL;
    while(root->next)
    {
        next = root->next;
        root->next = tail;
        tail = root;
        root = next;
        root->parent = NULL;
    }
    root->next = tail;
    return root;
}

template<class T>
BinomialNode<T>* BinomialHeap<T>::extractMinimum(BinomialNode<T>* root)
{
    BinomialNode<T> *y, *prev_y;
    if(root == NULL)
        return root;
    minimum(root, prev_y, y);
    if(prev_y == NULL)
        root  = root->next;
    else
        prev_y->next = y->next;
    BinomialNode<T>* child = reverse(y->child);
    root = combine(root, child);
    delete y;
    return root;
}

template<class T>
void BinomialHeap<T>::extractMinimum()
{
    mRoot = extractMinimum(mRoot);
}

template<class T>
void BinomialHeap<T>::decreaseKey(BinomialNode<T>* node, T key)
{
    if(key>=node->key || contains(key))
    {
        cout << "Decrease failed: the new key(" << key << ") is existed already, or is no smaller than the current key(" <<
        node->key << ")" << endl;
        return;
    }
    node->key = key;
    BinomialNode<T> *child, *parent;
    child = node;
    parent = node->parent;
    while(parent!=NULL && child->key<parent->key)
    {
        swap(parent->key, child->key);
        child = parent;
        parent = child->parent;
    }
}

template<class T>
void BinomialHeap<T>::increaseKey(BinomialNode<T>* node, T key)
{
    if(key<=node->key || contains(key))
    {
        cout << "Increase failed: the new key(" << key << ") is existed already, " <<
        "or is no greater than the current key(" << node->key << ")" << endl;
        return;
    }
    node->key = key;
    BinomialNode<T> *cur, *child, *parent, *least;
    cur = node;
    child = cur->child;
    while(child != NULL)
    {
        if(cur->key > child->key)
        {
            least = child;
            while(child->next != NULL)
            {
                if(least->key > child->next->key)
                    least = child->next;
                child = child->next;
            }
            swap(least->key, cur->key);
            cur = least;
            child = cur->child;
        }
        else
            child = child->next;
    }
}

template<class T>
void BinomialHeap<T>::updateKey(BinomialNode<T>* node, T key)
{
    if(node == NULL)
        return;
    if(key < node->key)
        decreaseKey(node, key);
    else if(key > node->key)
        increaseKey(node, key);
    else
        cout << "No need to update!" << endl;
}

template<class T>
void BinomialHeap<T>::update(T old_key, T new_key)
{
    BinomialNode<T>* node;
    node = search(mRoot, old_key);
    if(node != NULL)
        updateKey(node, new_key);
}

template<class T>
BinomialNode<T>* BinomialHeap<T>::search(BinomialNode<T>* root, T key)
{
    BinomialNode<T>* child;
    BinomialNode<T>* parent = root;
    parent = root;
    while(parent != NULL)
    {
        if(parent->key == key)
            return parent;
        else
        {
            if((child=search(parent->child, key)) != NULL)
                return child;
            parent = parent->next;
        }
    }
    return NULL;
}

template<class T>
bool BinomialHeap<T>::contains(T key)
{
    return search(mRoot, key)!=NULL? true: false;
}

template<class T>
BinomialNode<T>* BinomialHeap<T>::remove(BinomialNode<T>* root, T key)
{
    BinomialNode<T>* node;
    BinomialNode<T> *parent, *prev, *pos;
    if(root == NULL)
        return root;
    if((node=search(root, key)) == NULL)
        return root;
    parent = node->parent;
    while(parent != NULL)
    {
        swap(node->key, parent->key);
        node = parent;
        parent = node->parent;
    }
    prev = NULL;
    pos = root;
    while(pos != node)
    {
        prev = pos;
        pos = pos->next;
    }
    if(prev)
        prev->next = node->next;
    else
        root = root->next;
    root = combine(root, reverse(node->child));
    delete node;
    return root;
}

template<class T>
void BinomialHeap<T>::remove(T key)
{
    mRoot = remove(mRoot, key);
}

template<class T>
void BinomialHeap<T>::print(BinomialNode<T>* node, BinomialNode<T>* prev, int direction)
{
    while(node != NULL)
    {
        if(direction == 1)
            cout << node->key << "(" << node->degree << ") is " << prev->key << "'s child" << endl;
        else
            cout << node->key << "(" << node->degree << ") is " << prev->key << "'s next" << endl;
        if(node->child != NULL)
            print(node->child, node, 1);
        prev = node;
        node = node->next;
        direction = 2;
    }
}

template<class T>
void BinomialHeap<T>::print()
{
    BinomialNode<T>* p;
    if(mRoot == NULL)
        return;
    cout << "BinomialHeap( ";
    p = mRoot;
    while(p != NULL)
    {
        cout << "B" << p->degree << " ";
        p = p->next;
    }
    cout << ") details:" << endl;
    int i = 0;
    p = mRoot;
    while(p != NULL)
    {
        i++;
        cout << i << ". BinomialTree B" << p->degree << ":" << endl;
        cout << p->key << "(" << p->degree << ") is root" << endl;
        print(p->child, p, 1);
        p = p->next;
    }
    cout << endl;
}

#endif // BINOMIALHEAP_H_INCLUDED
