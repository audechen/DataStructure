#include <iostream>
using namespace std;

void quickSort(int* parr, int l, int r)
{
    if (l < r)
    {
        int ll, rr, mid;
        ll = l;
        rr = r;
        mid = parr[ll];
        while (ll < rr)
        {
            while ((ll < rr) && (parr[rr] > mid))
                rr--;
            if (ll < rr)
                parr[ll++] = parr[rr];
            while ((ll < rr) && (parr[ll] < mid))
                ll++;
            if (ll < rr)
                parr[rr--] = parr[ll];
        }
        parr[ll] = mid;
        quickSort(parr, l, ll-1);
        quickSort(parr, ll+1, r);
    }
}

int main()
{
    int arr[] = {53, 3, 52, 78, 14, 21, 15, 63, 66};
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << "Before sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    quickSort(arr, 0, len-1);
    cout << "After sort: ";
    for (int i=0; i<len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
