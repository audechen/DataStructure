#include <iostream>
#include <vector>
using namespace std;

#define MAX 100

class ListUDG
{
private:
    class ENode
    {
    public:
        int ivex;
        ENode* nextEdge;
    };
    class VNode
    {
    public:
        char data;
        ENode* firstEdge;
    };
private:
    int mVexNum;
    int mEdgNum;
    VNode mVexs[MAX];
public:
    ListUDG();
    ListUDG(char vexs[], int vlen, char edges[][2], int elen);
    ~ListUDG();

    void print();
private:
    char readChar();
    int getPosition(char ch);
    void linkLast(ENode* list, ENode* node);
};

ListUDG::ListUDG()
{
    char c1, c2;
    int v, e;
    int p1, p2;
    ENode *node1, *node2;
    cout << "input vertex number: ";
    cin >> mVexNum;
    cout << "input edge number: ";
    cin >> mEdgNum;
    if(mVexNum<1 || mEdgNum<1 || (mEdgNum > (mVexNum*(mVexNum-1))))
    {
        cout << "input error: invalid parameters!" << endl;
        return;
    }
    for(int i=0; i<mVexNum; i++)
    {
        cout << "vertex(" << i << "): ";
        mVexs[i].data = readChar();
        mVexs[i].firstEdge = NULL;
    }
    for(int i=0; i<mEdgNum; i++)
    {
        cout << "edge(" << i << "): ";
        c1 = readChar();
        c2 = readChar();
        p1 = getPosition(c1);
        p2 = getPosition(c2);
        node1 = new ENode();
        node1->ivex = p2;
        if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
        node2 = new ENode();
        node2->ivex = p1;
        if(mVexs[p2].firstEdge == NULL)
            mVexs[p2].firstEdge = node2;
        else
            linkLast(mVexs[p2].firstEdge, node2);
    }
}

ListUDG::ListUDG(char vexs[], int vlen, char edges[][2], int elen)
{
    char c1, c2;
    int p1, p2;
    ENode *node1, *node2;
    mVexNum = vlen;
    mEdgNum = elen;
    for(int i=0; i<mVexNum; i++)
    {
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = NULL;
    }
    for(int i=0; i<mEdgNum; i++)
    {
        c1 = edges[i][0];
        c2 = edges[i][1];
        p1 = getPosition(c1);
        p2 = getPosition(c2);
        node1 = new ENode();
        node1->ivex = p2;
        if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
        node2 = new ENode();
        node2->ivex = p1;
        if(mVexs[p2].firstEdge == NULL)
            mVexs[p2].firstEdge = node2;
        else
            linkLast(mVexs[p2].firstEdge, node2);
    }
}

ListUDG::~ListUDG(){}

void ListUDG::linkLast(ENode* list, ENode* node)
{
    ENode* p = list;
    while(p->nextEdge)
        p = p->nextEdge;
    p->nextEdge = node;
}

int ListUDG::getPosition(char ch)
{
    for(int i=0; i<mVexNum; i++)
    {
        if(mVexs[i].data == ch)
            return i;
    }
    return -1;
}

char ListUDG::readChar()
{
    char ch;
    do
    {
        cin >> ch;
    }
    while(!((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')));
    return ch;
}

void ListUDG::print()
{
    ENode* node;
    cout << "List Graph: " << endl;
    for(int i=0; i<mVexNum; i++)
    {
        cout << i << "(" << mVexs[i].data << "): ";
        node = mVexs[i].firstEdge;
        while(node != NULL)
        {
            cout << node->ivex << "(" << mVexs[node->ivex].data << ") ";
            node = node->nextEdge;
        }
        cout << endl;
    }
}

int main()
{
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'C'},
        {'A', 'D'},
        {'A', 'F'},
        {'B', 'C'},
        {'C', 'D'},
        {'E', 'G'},
        {'F', 'G'}};
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);
    ListUDG* pG;
    pG = new ListUDG(vexs, vlen, edges, elen);
    pG->print();
    return 0;
}
