#include <iostream>
#include "DoubleLink.h"
using namespace std;

void int_test()
{
    int iarr[4] = {10, 20, 30, 40};
    cout << "\n----int_test----" << endl;
    DoubleLink<int> *pdlink = new DoubleLink<int>();
    pdlink->insert_first(iarr[1]);
    pdlink->insert_last(iarr[0]);
    pdlink->insert(0, iarr[2]);
    cout << "is_empty() = " << pdlink->is_empty() << endl;
    cout << "size() = " << pdlink->size() << endl;
    int sz = pdlink->size();
    for (int i = 0 ; i < sz ; i++)
    {
        cout << "pdlink(" << i << ") = " << pdlink->get(i) << endl;
    }
}

void string_test()
{
    string sarr[4] = {"ten", "twenty", "thirty", "forty"};
    cout << "\n----string_test----" << endl;
    DoubleLink<string> *pdlink = new DoubleLink<string>();
    pdlink->insert_first(sarr[1]);
    pdlink->insert_last(sarr[0]);
    pdlink->insert(0, sarr[2]);
    cout << "is_empty() = " << pdlink->is_empty() << endl;
    cout << "size() = " << pdlink->size() << endl;
    int sz = pdlink->size();
    for (int i = 0 ; i < sz ; i++)
    {
        cout << "pdlink(" << i << ") = " << pdlink->get(i) << endl;
    }
}

struct stu
{
    int id;
    char name[20];
};

static stu arr_stu[] =
{
    {10, "sky"},{20, "water"},{30, "dyson"},{40, "mary"},
};

#define ARR_STU_SIZE ((sizeof(arr_stu))/(sizeof(arr_stu[0])))

void object_test()
{
    cout << "\n----object_test----" << endl;
    DoubleLink<stu> *pdlink = new DoubleLink<stu>();
    pdlink->insert_first(arr_stu[1]);
    pdlink->insert_last(arr_stu[0]);
    pdlink->insert(0, arr_stu[2]);
    cout << "is_empty() = " << pdlink->is_empty() << endl;
    cout << "size() = " << pdlink->size() << endl;
    int sz = pdlink->size();
    struct stu p;
    for (int i = 0 ; i < sz ; i++)
    {
        p = pdlink->get(i);
        cout << "pdlink(" << i << ") = [" << p.id << ", " << p.name << "]" <<endl;
    }
}

int main()
{
    int_test();
    string_test();
    object_test();

    return 0;
}
