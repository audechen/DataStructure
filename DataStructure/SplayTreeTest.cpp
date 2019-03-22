#include <iostream>
#include "SplayTree.h"
using namespace std;

static int arr[] = {10,50,40,30,20,60};
#define TBL_SIZE(a) (sizeof(a)/sizeof(a[0]))


int main()
{
    int len = TBL_SIZE(arr);
    SplayTree<int>* tree = new SplayTree<int>();

    cout << "Data in line: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
        tree->insert(arr[i]);
    }

    cout << "\nPreOrder: ";
    tree->preOrder();
    cout << "\nInOrder: ";
    tree->inOrder();
    cout << "\npostOrder: ";
    tree->postOrder();

    cout << "\nMinimum value: " << tree->minimum() << endl;
    cout << "Maximum value: " << tree->maximum() << endl;
    cout << "Structure details: " << endl;
    tree->print();

    int i = 30;
    cout << "\nRotate " << i << " as root" << endl;
    tree->splay(i);
    cout << "Updated details: " << endl;
    tree->print();

    tree->destory();
    return 0;
}
