#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

static int arr[] = {1, 5, 4, 3, 2, 6};
#define TBL_SIZE(a) ((sizeof(a))/(sizeof(a[0])))

int main()
{
    int i, n, len;
    BinarySearchTree<int>* tree = new BinarySearchTree<int>();
    len = TBL_SIZE(arr);
    cout << len << " numbers to be added: ";
    for (i=0; i<len; i++)
    {
        cout << arr[i] << " ";
        tree->insert(arr[i]);
    }
    cout << "\nPreOrder: ";
    tree->preOrder();
    cout << "\nInOrder: ";
    tree->inOrder();
    cout << "\nPostOrder: ";
    tree->postOrder();
    cout << endl;
    cout << "minimum value: " << tree->minimum() << endl;
    cout << "maximum value: " << tree->maximum() << endl;
    cout << "delicate information: " << endl;
    tree->print();
    cout << "if delete: " << endl;
    cin >> n;
    tree->remove(n);
    cout << "\nPreOrder: ";
    tree->preOrder();
    cout << "\nInOrder: ";
    tree->inOrder();
    cout << "\nPostOrder: ";
    tree->postOrder();
    cout << endl;
    cout << "minimum value: " << tree->minimum() << endl;
    cout << "maximum value: " << tree->maximum() << endl;
    cout << "delicate information: " << endl;
    tree->print();
    tree->destory();

    return 0;
}
