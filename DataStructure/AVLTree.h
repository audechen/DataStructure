#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include <iostream>
using namespace std;

template<class T>
struct AVLTreeNode
{
public:
    T key;
    int height;
    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r):
        key(value), height(0), left(l), right(r){}
};

template<class T>
class AVLTree
{
private:
    AVLTreeNode<T> *mRoot;
public:
    AVLTree();
    ~AVLTree();

    int height();
    int max(int a, int b);

    void preOrder();
    void inOrder();
    void postOrder();

    AVLTreeNode<T>* search(T key);
    AVLTreeNode<T>* iterativeSearch(T key);

    T minimum();
    T maximum();

    void insert(T key);
    void remove(T key);
    void destory();
    void print();
private:
    int height(AVLTreeNode<T>* tree);

    void preOrder(AVLTreeNode<T>* tree) const;
    void inOrder(AVLTreeNode<T>* tree) const;
    void postOrder(AVLTreeNode<T>* tree) const;

    AVLTreeNode<T>* search(AVLTreeNode<T>* tree, T key) const;
    AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* tree, T key) const;

    AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

    AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* n);
    AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* n);

    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* n);
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* n);

    AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);
    AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z);

    void destory(AVLTreeNode<T>* &tree);
    void print(AVLTreeNode<T>* tree, T key, int direction);
};

template<class T>
AVLTree<T>::AVLTree():mRoot(NULL){}

template<class T>
AVLTree<T>::~AVLTree()
{
    destory(mRoot);
}

template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
    if(tree != NULL)
        return tree->height;
    return 0;
}

template<class T>
int AVLTree<T>::height()
{
    return height(mRoot);
}

template<class T>
int AVLTree<T>::max(int a, int b)
{
    return a>b? a: b;
}

template<class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        cout << tree->key << " ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template<class T>
void AVLTree<T>::preOrder()
{
    preOrder(mRoot);
}

template<class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        cout << tree->key << " ";
        inOrder(tree->right);
    }
}

template<class T>
void AVLTree<T>::inOrder()
{
    inOrder(mRoot);
}

template<class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->key << " ";
    }
}

template<class T>
void AVLTree<T>::postOrder()
{
    postOrder(mRoot);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* tree, T key) const
{
    if(tree==NULL || tree->key==key)
        return tree;
    else if(key < tree->key)
        return search(tree->left, key);
    else
        return search(tree->right, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(T key)
{
    return search(mRoot, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* tree, T key) const
{
    while(tree!=NULL && tree->key!=key)
    {
        if (key < tree->key)
            tree = tree->key;
        else
            tree = tree->right;
    }
    return tree;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key)
{
    return iterativeSearch(mRoot, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T> *tree)
{
    if(tree == NULL)
        return NULL;
    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template<class T>
T AVLTree<T>::minimum()
{
    AVLTreeNode<T>* p = minimum(mRoot);
    if(p != NULL)
        return p->key;
    return (T)NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
    if(tree == NULL)
        return NULL;
    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template<class T>
T AVLTree<T>::maximum()
{
    AVLTreeNode<T>* p = maximum(mRoot);
    if(p != NULL)
        return p->key;
    return (T)NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* n)
{
    AVLTreeNode<T>* leftChild;
    leftChild = n->left;
    n->left = leftChild->right;
    leftChild->right = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    leftChild->height = max(height(leftChild->left), height(leftChild->right)) + 1;
    return leftChild;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* n)
{
    AVLTreeNode<T>* rightChild;
    rightChild = n->right;
    n->right = rightChild->left;
    rightChild->left = n;
    n->height = max(height(n->left), height(n->right)) + 1;
    rightChild->height = max(height(rightChild->left), height(rightChild->right)) + 1;
    return rightChild;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* n)
{
    n->left = rightRightRotation(n->left);
    return leftLeftRotation(n);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* n)
{
    n->right = leftLeftRotation(n->right);
    return rightRightRotation(n);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
    if(tree == NULL)
    {
        tree = new AVLTreeNode<T>(key, NULL, NULL);
        if(tree == NULL)
        {
            cout << "Error: create AVL tree node failed!" << endl;
            return NULL;
        }
    }
    else if(key < tree->key)
    {
        tree->left = insert(tree->left, key);
        if(height(tree->left) - height(tree->right) == 2)
        {
            if(key < tree->left->key)
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else if(key > tree->key)
    {
        tree->right = insert(tree->right, key);
        if(height(tree->right) - height(tree->left) == 2)
        {
            if(key > tree->right->key)
                tree = rightRightRotation(tree);
            else
                tree = rightLeftRotation(tree);
        }
    }
    else
    {
        cout << "Error: This node can not be inserted twice" << endl;
    }
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}

template<class T>
void AVLTree<T>::insert(T key)
{
    insert(mRoot, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* z)
{
    if(tree==NULL || z==NULL)
        return NULL;
    if(z->key < tree->key) // delete in its left child
    {
        tree->left = remove(tree->left, z);
        if(height(tree->right) - height(tree->left) == 2)
        {
            AVLTreeNode<T>* r = tree->right;
            if(height(r->left) > height(r->right))
                tree = rightLeftRotation(tree);
            else
                tree = rightRightRotation(tree);
        }
    }
    else if(z->key > tree->key) // delete in its right child
    {
        tree->right = remove(tree->right, z);
        if(height(tree->left) - height(tree->right) == 2)
        {
            AVLTreeNode<T>* l = tree->left;
            if(height(l->left) > height(l->right))
                tree = leftLeftRotation(tree);
            else
                tree = leftRightRotation(tree);
        }
    }
    else // tree is the node to be deleted
    {
        if(tree->left!=NULL && tree->right!=NULL)
        {
            if(height(tree->left) > height(tree->right))
            {
                AVLTreeNode<T>* Max = maximum(tree->left);
                tree->key = Max->key;
                tree->left = remove(tree->left, Max);
            }
            else
            {
                AVLTreeNode<T>* Min = minimum(tree->right);
                tree->key = Min->key;
                tree->right = remove(tree->right, Min);
            }
        }
        else
        {
            AVLTreeNode<T>* tmp = tree;
            tree = (tree->left!=NULL)? tree->left: tree->right;
            delete tmp;
        }
    }
    return tree;
}

template<class T>
void AVLTree<T>::remove(T key)
{
    AVLTreeNode<T>* z;
    if((z=search(mRoot, key)) != NULL)
        mRoot = remove(mRoot, z);
}

template<class T>
void AVLTree<T>::destory(AVLTreeNode<T>* &tree)
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
void AVLTree<T>::destory()
{
    destory(mRoot);
}

template<class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)
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
void AVLTree<T>::print()
{
    if(mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}


#endif // AVLTREE_H_INCLUDED
