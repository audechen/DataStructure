#include <iostream>
#include "AVLTree.h"
using namespace std;

static int arr[] = {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
# define TBL_SIZE(a) (sizeof(a)/sizeof(a[0]))

int main()
{
    int len = TBL_SIZE(arr);
    AVLTree<int>* tree = new AVLTree<int>();

    cout << "==Numbers waiting in line: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
        tree->insert(arr[i]);
    }
    cout << "\n==PreOrder: ";
    tree->preOrder();
    cout << "\n==InOrder: ";
    tree->inOrder();
    cout << "\n==PostOrder:";
    tree->postOrder();
    cout << endl;
    cout << "==Height: " << tree->height() << endl;
    cout << "==Minimum value: " << tree->minimum() << endl;
    cout << "==maximum value: " << tree->maximum() << endl;
    cout << "==Structure details: " << endl;
    tree->print();
    int i = 7;
    cout << "\n==Delete root: " << i;
    tree->remove(i);
    cout << "\n==Height: " << tree->height() << endl;
    cout << "==PreOrder: ";
    tree->preOrder();
    cout << "\n==InOrder: ";
    tree->inOrder();
    cout << "\n==PostOrder:";
    tree->postOrder();
    cout << endl;
    cout << "==Structure details: " << endl;
    tree->print();
    tree->destory();

    return 0;
}
