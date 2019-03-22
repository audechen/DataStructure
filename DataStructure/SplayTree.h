#ifndef SPLAYTREE_H_INCLUDED
#define SPLAYTREE_H_INCLUDED

#include <iostream>
using namespace std;

template<class T>
struct SplayTreeNode
{
public:
    T key;
    SplayTreeNode *left;
    SplayTreeNode *right;
    SplayTreeNode():left(NULL), right(NULL){}
    SplayTreeNode(T value, SplayTreeNode* l, SplayTreeNode* r):
        key(value), left(l), right(r){}
};

template<class T>
class SplayTree
{
private:
    SplayTreeNode<T>* mRoot;
public:
    SplayTree();
    ~SplayTree();

    void preOrder();
    void inOrder();
    void postOrder();

    SplayTreeNode<T>* search(T key);
    SplayTreeNode<T>* iterativeSearch(T key);

    T minimum();
    T maximum();

    void splay(T key);
    void insert(T key);
    void remove(T key);
    void destory();
    void print();
private:
    void preOrder(SplayTreeNode<T>* tree) const;
    void inOrder(SplayTreeNode<T>* tree) const;
    void postOrder(SplayTreeNode<T>* tree) const;

    SplayTreeNode<T>* search(SplayTreeNode<T>* tree, T key) const;
    SplayTreeNode<T>* iterativeSearch(SplayTreeNode<T>* tree, T key) const;

    SplayTreeNode<T>* minimum(SplayTreeNode<T>* tree);
    SplayTreeNode<T>* maximum(SplayTreeNode<T>* tree);

    SplayTreeNode<T>* splay(SplayTreeNode<T>* tree, T key);
    SplayTreeNode<T>* insert(SplayTreeNode<T>* &tree, SplayTreeNode<T>* z);
    SplayTreeNode<T>* remove(SplayTreeNode<T>* &tree, T key);
    void destory(SplayTreeNode<T>* &tree);
    void print(SplayTreeNode<T>* tree, T key, int direction);
};

template<class T>
SplayTree<T>::SplayTree():mRoot(NULL){}

template<class T>
SplayTree<T>::~SplayTree()
{
    destory(mRoot);
}

template<class T>
void SplayTree<T>::preOrder(SplayTreeNode<T>* tree) const
{
    if (tree != NULL)
    {
        cout << tree->key << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}
template<class T>
void SplayTree<T>::preOrder()
{
    preOrder(mRoot);
}

template<class T>
void SplayTree<T>::inOrder(SplayTreeNode<T>* tree) const
{
    if (tree != NULL)
    {
        inOrder(tree->left);
        cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template<class T>
void SplayTree<T>::inOrder()
{
    inOrder(mRoot);
}

template<class T>
void SplayTree<T>::postOrder(SplayTreeNode<T>* tree) const
{
    if (tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->key << " ";
    }
}

template<class T>
void SplayTree<T>::postOrder()
{
    postOrder(mRoot);
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::search(SplayTreeNode<T>* tree, T key) const
{
    if(tree==NULL || tree->key==key)
        return tree;
    if(key < tree->key)
        return search(tree->left, key);
    else
        return search(tree->right, key);
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::search(T key)
{
    return search(mRoot, key);
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::iterativeSearch(SplayTreeNode<T>* tree, T key) const
{
    while (tree!=NULL && tree->key!=key)
    {
        if(key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(mRoot, key);
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::minimum(SplayTreeNode<T>* tree)
{
    if(tree == NULL)
        return NULL;
    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template<class T>
T SplayTree<T>::minimum()
{
    SplayTreeNode<T>* p = minimum(mRoot);
    if(p != NULL)
        return p->key;
    return (T)NULL;
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::maximum(SplayTreeNode<T>* tree)
{
    if(tree == NULL)
        return NULL;
    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template<class T>
T SplayTree<T>::maximum()
{
    SplayTreeNode<T>* p = maximum(mRoot);
    if(p != NULL)
        return p->key;
    return (T)NULL;
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::splay(SplayTreeNode<T>* tree, T key)
{
    SplayTreeNode<T> N;
    SplayTreeNode<T> *l, *r, *c;
    if(tree == NULL)
        return tree;
    N.left = N.right = NULL;
    l = r = &N;
    while(true)
    {
        if(key < tree->key)
        {
            if(tree->left == NULL)
                break;
            if(key < tree->left->key)
            {
                c = tree->left;
                tree->left = c->right;
                c->right = tree;
                tree = c;
                if(tree->left == NULL)
                    break;
            }
            r->left = tree;
            r = tree;
            tree = tree->left;
        }
        else if(key > tree->key)
        {
            if(tree->right == NULL)
                break;

            if(key > tree->right->key)
            {
                c = tree->right;
                tree->right = c->left;
                c->left = tree;
                tree = c;
                if(tree->right == NULL)
                    break;
            }
            l->right = tree;
            l = tree;
            tree = tree->right;
        }
        else
            break;
    }
    l->right = tree->left;
    r->left = tree->right;
    tree->left = N.right;
    tree->right = N.left;

    return tree;
}

template<class T>
void SplayTree<T>::splay(T key)
{
    mRoot = splay(mRoot, key);
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::insert(SplayTreeNode<T>* &tree, SplayTreeNode<T>* z)
{
    SplayTreeNode<T>* pos = NULL;
    SplayTreeNode<T>* x = tree;
    while(x != NULL)
    {
        pos = x;
        if(z->key < x->key)
            x = x->left;
        else if(z->key > x->key)
            x = x->right;

        else
        {
            cout << "Error: found a same node(" << z->key << ")" << endl;
            delete z;
            return tree;
        }
    }
    if(pos == NULL)
        tree = z;
    else if(z->key < pos->key)
        pos->left = z;
    else
        pos->right = z;
    return tree;
}

template<class T>
void SplayTree<T>::insert(T key)
{
    SplayTreeNode<T>* z = NULL;
    if((z=new SplayTreeNode<T>(key, NULL, NULL)) == NULL)
        return;
    mRoot = insert(mRoot, z);
    mRoot = splay(mRoot, key);
}

template<class T>
SplayTreeNode<T>* SplayTree<T>::remove(SplayTreeNode<T>* &tree, T key)
{
    SplayTreeNode<T>* x;
    if(tree == NULL)
        return NULL;
    if(search(tree, key) == NULL)
        return tree;
    tree = splay(tree, key);
    if(tree->left != NULL)
    {
        x = splay(tree->left, key);
        x->right = tree->right;
    }
    else
        x = tree->right;
    delete tree;
    return x;
}

template<class T>
void SplayTree<T>::remove(T key)
{
    mRoot = SplayTree(mRoot, key);
}

template<class T>
void SplayTree<T>::destory(SplayTreeNode<T>* &tree)
{
    if(tree == NULL)
        return;
    if(tree->left != NULL)
        destory(tree->left);
    if(tree->right != NULL)
        destory(tree->right);
    delete tree;
}

template<class T>
void SplayTree<T>::destory()
{
    destory(mRoot);
}

template<class T>
void SplayTree<T>::print(SplayTreeNode<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction == 0)
            cout << tree->key << " is root" << endl;
        else
            cout << tree->key << " is " << key << "'s " << (direction==1? "right child": "left child") << endl;
        print(tree->left, tree->key, -1);
        print(tree->right, tree->key, 1);
    }
}

template<class T>
void SplayTree<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}

#endif // SPLAYTREE_H_INCLUDED
