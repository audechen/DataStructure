#include <iostream>
using namespace std;

void mergetwo (int* parr, int startPos, int endPos, int midPos)
{
    int *tmp = new int[endPos-startPos+1];
    int p1 = startPos;
    int p2 = midPos+1;
    int p3 = 0;
    while (p1<=midPos && p2<=endPos)
    {
        if (parr[p1] <= parr[p2])
            tmp[p3++] = parr[p1++];
        else
            tmp[p3++] = parr[p2++];
    }
    while (p1 <= midPos)
        tmp[p3++] = parr[p1++];
    while (p2 <= endPos)
        tmp[p3++] = parr[p2++];
    for (int i=0; i<p3; i++)
        parr[startPos+i] = tmp[i];
    delete[] tmp;
}

void MergeSortUp2Down(int* parr, int startPos, int endPos)
{
    if (parr==NULL || startPos>=endPos)
        return;
    int midPos = (endPos+startPos)/2;
    MergeSortUp2Down(parr, startPos, midPos);
    MergeSortUp2Down(parr, midPos+1, endPos);
    mergetwo(parr, startPos, endPos, midPos);
}

void mergeGroups(int* parr, int len, int gap)
{
    int twolen = gap*2;
    int i;
    for (i=0; i+twolen-1<len; i+=twolen)
        mergetwo(parr, i, i+twolen-1, i+gap-1);
    if (i+gap-1 < len-1)
    {
        mergetwo(parr, i, len-1, i+gap-1);
    }
}

void MergeSortDown2Up(int* parr, int len)
{
    if (parr==NULL && len<=0)
        return;
    for (int gap=1; gap<len; gap*=2)
        mergeGroups(parr, len, gap);
}

int main()
{
    int n;
    int arr[] = {30,30,40,60,10,10,20,50};
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << "Before sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Please enter 1 for Up2Down algorithm, 2 for Down2Up algorithm: ";
    cin >> n;
    switch(n)
    {
    case 1:
        MergeSortUp2Down(arr, 0, len-1);
        break;
    case 2:
        MergeSortDown2Up(arr, len);
        break;
    }
    cout << "After sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
