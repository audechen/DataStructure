#include <iostream>
#include <vector>
using namespace std;

#define MAX 100

class MatrixDG
{
private:
    char mVexs[MAX];
    int mVexNum;
    int mEdgNum;
    int mMatrix[MAX][MAX];
public:
    MatrixDG();
    MatrixDG(char vexs[], int vlen, char edges[][2], int elen);
    ~MatrixDG();
    void print();
private:
    char readchar();
    int getPostion(char ch);
};

MatrixDG::MatrixDG()
{
    char c1, c2;
    int p1, p2;
    cout << "input vertex number: ";
    cin >> mVexNum;
    cout << "input edge number: ";
    cin >> mEdgNum;
    if(mVexNum<1 || mEdgNum<1 || (mEdgNum>(mVexNum*(mVexNum-1))))
    {
        cout << "input error: invalid parameters!" << endl;
        return;
    }
    for(int i=0; i<mVexNum; i++)
    {
        cout << "vertex(" << i << "): ";
        mVexs[i] = readchar();
    }
    for(int i=0; i<mEdgNum; i++)
    {
        cout << "edge(" << i << "): ";
        c1 = readchar();
        c2 = readchar();
        p1 = getPostion(c1);
        p2 = getPostion(c2);
        if(p1==-1 || p2==-1)
        {
            cout << "input error: invalid edge!" << endl;
            return;
        }
        mMatrix[p1][p2] = 1;
    }
}

MatrixDG::MatrixDG(char vexs[], int vlen, char edges[][2], int elen)
{
    int p1, p2;
    mVexNum = vlen;
    mEdgNum = elen;
    for(int i=0; i<mVexNum; i++)
        mVexs[i] = vexs[i];
    for(int i=0; i<mEdgNum; i++)
    {
        p1 = getPostion(edges[i][0]);
        p2 = getPostion(edges[i][1]);
        mMatrix[p1][p2] = 1;
    }
}

MatrixDG::~MatrixDG(){}

int MatrixDG::getPostion(char ch)
{
    for (int i=0; i<mVexNum; i++)
    {
        if(mVexs[i] == ch)
            return i;
    }
    return -1;
}

char MatrixDG::readchar()
{
    char ch;
    do
    {
        cin >> ch;
    }
    while(!((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')));
    return ch;
}

void MatrixDG::print()
{
    cout << "Matrix Graph: " <<endl;
    for(int i=0; i<mVexNum; i++)
    {
        for(int j=0; j<mVexNum; j++)
            cout << mMatrix[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    char vexs[] = {'A','B','C','D','E','F','G'};
    char edges[][2] = {
        {'A','C'},
        {'A','D'},
        {'A','F'},
        {'B','C'},
        {'C','D'},
        {'E','G'},
        {'F','G'}
    };
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);
    MatrixDG* pG;
    pG = new MatrixDG(vexs, vlen, edges, elen);
    pG->print();
    return 0;
}
