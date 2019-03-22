#include <iostream>
#include <vector>
using namespace std;

#define MAX 100
class MatrixUDG
{
private:
    char mVexs[MAX];
    int mVexNum;
    int mEdgNum;
    int mMatrix[MAX][MAX];
public:
    MatrixUDG();
    MatrixUDG(char vexs[], int vlen, char edges[][2], int elen);
    ~MatrixUDG();

    void print();
private:
    char readChar();
    int getPosition(char ch);
};

MatrixUDG::MatrixUDG()
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
        mVexs[i] = readChar();
    }
    for(int i=0; i<mEdgNum; i++)
    {
        cout << "edge(" << i << "): ";
        c1 = readChar();
        c2 = readChar();
        p1 = getPosition(c1);
        p2 = getPosition(c2);
        if(p1==-1 || p2==-1)
        {
            cout << "input error: invalid edge!" << endl;
            return;
        }
        mMatrix[p1][p2] = 1;
        mMatrix[p2][p1] = 1;
    }
}

MatrixUDG::MatrixUDG(char vexs[], int vlen, char edges[][2], int elen)
{
    int p1, p2;
    mVexNum = vlen;
    mEdgNum = elen;
    for(int i=0; i<mVexNum; i++)
        mVexs[i] = vexs[i];
    for(int i=0; i<mEdgNum; i++)
    {
        p1 = getPosition(edges[i][0]);
        p2 = getPosition(edges[i][1]);
        mMatrix[p1][p2] = 1;
        mMatrix[p2][p1] = 1;
    }
}

MatrixUDG::~MatrixUDG(){}

int MatrixUDG::getPosition(char ch)
{
    for(int i=0; i<mVexNum; i++)
    {
        if(mVexs[i] == ch)
            return i;
    }
    return -1;
}

char MatrixUDG::readChar()
{
    char ch;
    do
    {
        cin >> ch;
    }
    while(!((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')));
    return ch;
}

void MatrixUDG::print()
{
    cout << "Matrix Graph: " << endl;
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
    MatrixUDG* pG;
    pG = new MatrixUDG(vexs, vlen, edges, elen);
    pG->print();
    return 0;
}
