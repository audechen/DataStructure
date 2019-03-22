#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
#include <iomanip>
#include <iostream>
using namespace std;

template<class T>
struct BinarySearchTreeNode
{
public:
    T key;
    BinarySearchTreeNode *left;
    BinarySearchTreeNode *right;
    BinarySearchTreeNode *parent;
    BinarySearchTreeNode(T t, BinarySearchTreeNode *l, BinarySearchTreeNode *r, BinarySearchTreeNode *p):
        key(t), left(l), right(r), parent(p) {}
};

template<class T>
class BinarySearchTree
{
private:
    BinarySearchTreeNode<T> *mRoot;
public:
    BinarySearchTree();
    ~BinarySearchTree();
    void preOrder();
    void inOrder();
    void postOrder();
    BinarySearchTreeNode<T> *search(T key);
    BinarySearchTreeNode<T> *iterativeSearch(T key);
    T minimum();
    T maximum();
    BinarySearchTreeNode<T> *successor(BinarySearchTreeNode<T> *n);
    BinarySearchTreeNode<T> *predecessor(BinarySearchTreeNode<T> *n);
    void insert(T key);
    void remove(T key);
    void destory();
    void print();
private:
    void preOrder(BinarySearchTreeNode<T> *n) const;
    void inOrder(BinarySearchTreeNode<T> *n) const;
    void postOrder(BinarySearchTreeNode<T> *n) const;
    BinarySearchTreeNode<T> *search(BinarySearchTreeNode<T>* n, T key) const;
    BinarySearchTreeNode<T> *iterativeSearch(BinarySearchTreeNode<T>* n, T key) const;
    BinarySearchTreeNode<T> *minimum(BinarySearchTreeNode<T>* n);
    BinarySearchTreeNode<T> *maximum(BinarySearchTreeNode<T>* n);
    void insert(BinarySearchTreeNode<T>* &tree, BinarySearchTreeNode<T> *n);
    BinarySearchTreeNode<T> *remove(BinarySearchTreeNode<T>* &tree, BinarySearchTreeNode<T> *n);
    void destory(BinarySearchTreeNode<T>* &Tree);
    void print(BinarySearchTreeNode<T>* &tree, T key, int direction);
};

template<class T>
BinarySearchTree<T>::BinarySearchTree():mRoot(NULL){}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    destory();
}

template<class T>
void BinarySearchTree<T>::preOrder(BinarySearchTreeNode<T> *n) const
{
    if (n != NULL)
    {
        cout << n->key << " ";
        preOrder(n->left);
        preOrder(n->right);
    }
}

template<class T>
void BinarySearchTree<T>::preOrder()
{
    preOrder(mRoot);
}

template<class T>
void BinarySearchTree<T>::inOrder(BinarySearchTreeNode<T> *n) const
{
    if (n != NULL)
    {
        inOrder(n->left);
        cout << n->key << " ";
        inOrder(n->right);
    }
}

template<class T>
void BinarySearchTree<T>::inOrder()
{
    inOrder(mRoot);
}

template<class T>
void BinarySearchTree<T>::postOrder(BinarySearchTreeNode<T> *n) const
{
    if (n != NULL)
    {
        postOrder(n->left);
        postOrder(n->right);
        cout << n->key << " ";
    }
}

template<class T>
void BinarySearchTree<T>::postOrder()
{
    postOrder(mRoot);
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::search(BinarySearchTreeNode<T>* n, T key) const
{
    if (n == NULL || n->key == key)
        return n;
    if (key < n->key)
        return search(n->left, key);
    else
        return search(n->right, key);
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::search(T key)
{
    search(mRoot, key);
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::iterativeSearch(BinarySearchTreeNode<T>* n, T key) const
{
    while ((n != NULL) && (n->key != key))
    {
        if (key < n->key)
            n = n->lefy;
        else
            n = n->right;
    }
    return n;
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::iterativeSearch(T key)
{
    iterativeSearch(mRoot, key);
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::minimum(BinarySearchTreeNode<T>* n)
{
    if (n == NULL)
        return NULL;
    while (n->left != NULL)
        n = n->left;
    return n;

}

template<class T>
T BinarySearchTree<T>::minimum()
{
    BinarySearchTreeNode<T>* res = minimum(mRoot);
    if (res != NULL)
        return res->key;
    return (T)NULL;
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::maximum(BinarySearchTreeNode<T>* n)
{
    if (n == NULL)
        return NULL;
    while (n->right != NULL)
        n = n->right;
    return n;
}

template<class T>
T BinarySearchTree<T>::maximum()
{
    BinarySearchTreeNode<T>* res = maximum(mRoot);
    if (res != NULL)
        return res->key;
    return (T)NULL;
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::successor(BinarySearchTreeNode<T>* n)
{
    if (n->right != NULL)
        return minimum(n->right);
    BinarySearchTreeNode<T>* m = n->parent;
    while ((m != NULL) && (n == m->right))
    {
        n = m;
        m = n->parent;
    }
    return m;
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::predecessor(BinarySearchTreeNode<T>* n)
{
    if (n->left != NULL)
        return maximum(n->left);
    BinarySearchTreeNode<T>* m = n->parent;
    while ((m != NULL) && n == m.left)
    {
        n = m;
        m = n.parent;
    }
    return m;
}

template<class T>
void BinarySearchTree<T>::insert(BinarySearchTreeNode<T>* &tree, BinarySearchTreeNode<T>* n)
{
    BinarySearchTreeNode<T>* pos = NULL;
    BinarySearchTreeNode<T>* tmp = tree;
    while (tmp != NULL)
    {
        pos = tmp;
        if (n->key < tmp->key)
            tmp = tmp->left;
        else if (n->key > tmp->key)
            tmp = tmp->right;
        else
        {
            cout << n->key << "is an existing value!!!" << endl;
            return;
        }
    }
    n->parent = pos;
    if (pos == NULL)
    {
        tree = n;
    }
    else if (n->key < pos->key)
    {
        pos->left = n;
    }
    else
    {
        pos->right = n;
    }
}

template<class T>
void BinarySearchTree<T>::insert(T key)
{
    BinarySearchTreeNode<T> *n = NULL;
    if ((n = new BinarySearchTreeNode<T>(key, NULL, NULL, NULL)) == NULL)
        return;
    insert (mRoot, n);
}

template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::remove(BinarySearchTreeNode<T>* &Tree, BinarySearchTreeNode<T>* n)
{
    BinarySearchTreeNode<T>* x = NULL;
    BinarySearchTreeNode<T>* y = NULL;

    if ((n->left == NULL) || (n->right == NULL))
        y = n;
    else
        y = successor(n);

    if (y->left != NULL)
        x = y->left;
    else
        x = y->right;

    if (x != NULL)
        x->parent = y->parent;

    if (y->parent == NULL)
        Tree = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != n)
        n->key = y->key;

    return y;
}

template<class T>
void BinarySearchTree<T>::remove(T key)
{
    BinarySearchTreeNode<T> *ifExist, *delNode;
    if ((ifExist = search(mRoot, key)) != NULL)
        if ((delNode = remove(mRoot, ifExist)) != NULL)
            delete delNode;
}

template<class T>
void BinarySearchTree<T>::destory(BinarySearchTreeNode<T>* &tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL)
        return destory(tree->left);
    if (tree->right != NULL)
        return destory(tree->right);
    delete tree;
    tree = NULL;
}

template<class T>
void BinarySearchTree<T>::destory()
{
    destory(mRoot);
}

template<class T>
void BinarySearchTree<T>::print(BinarySearchTreeNode<T>* &tree, T key, int direction)
{
    if (tree != NULL)
    {
        if (direction == 0)
            cout << tree->key << " is root" << endl;
        else
            cout << tree->key << " is " << key << "'s " << (direction == 1? "right child" : "left child") << endl;
        print (tree->left, tree->key, -1);
        print (tree->right, tree->key, 1);
    }
}

template<class T>
void BinarySearchTree<T>::print()
{
    if (mRoot != NULL)
        print (mRoot, mRoot->key, 0);
}

#endif // BINARYSEARCHTREE_H_INCLUDED
