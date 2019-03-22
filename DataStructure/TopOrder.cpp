/**
 *Topological sorting of directed acyclic graph
 *Implemented by adjacency list
 */

 #include <iostream>
 #include <vector>
 #include <string.h>

 using namespace std;

 #define MAX 100

 class ListDG
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
    VNode* mVexs;
public:
    ListDG();
    ListDG(char vexs[], int vlen, char edges[][2], int elen);
    ~ListDG();
    void DFS();
    void BFS();
    void print();
    int topSort();
private:
    char readChar();
    int getPosition(char ch);
    void DFS(int i, int* visited);
    void linkLast(ENode* list, ENode* node);
 };

 ListDG::ListDG()
 {
     char c1, c2;
     int p1, p2;
     ENode* node;

     cout << "input vertex number: ";
     cin >> mVexNum;
     cout << "input edge number: ";
     cin >> mEdgNum;
     if(mVexNum<1 || mEdgNum<1 || mEdgNum>(mVexNum*(mVexNum-1)))
     {
         cout << "input error: invalid parameters!" << endl;
         return;
     }
     mVexs = new VNode[mVexNum];
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
         node = new ENode();
         node->ivex = p2;
         if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node;
         else
            linkLast(mVexs[p1].firstEdge, node);
     }
 }

 ListDG::ListDG(char vexs[], int vlen, char edges[][2], int elen)
 {
     char c1, c2;
     int p1, p2;
     ENode* node;
     mVexNum = vlen;
     mEdgNum = elen;
     mVexs = new VNode[mVexNum];
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
         node = new ENode();
         node->ivex = p2;
         if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node;
         else
            linkLast(mVexs[p1].firstEdge, node);
     }
}

ListDG::~ListDG()
{
    ENode* node;
    for(int i=0; i<mEdgNum; i++)
    {
        node = mVexs[i].firstEdge;
        while(node != NULL)
        {
            delete node;
            node = node->nextEdge;
        }
    }
    delete[] mVexs;
}

void ListDG::linkLast(ENode* list, ENode* node)
{
    ENode* p = list;
    while(p->nextEdge)
        p = p->nextEdge;
    p->nextEdge = node;
}

int ListDG::getPosition(char ch)
{
    for(int i=0; i<mVexNum; i++)
    {
        if(mVexs[i].data == ch)
            return i;
    }
    return -1;
}

char ListDG::readChar()
{
    char ch;
    do
    {
        cin >> ch;
    }
    while(!((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')));
    return ch;
}

void ListDG::DFS(int i, int* visted)
{
    ENode* node;
    visted[i] = 1;
    cout << mVexs[i].data << " ";
    node = mVexs[i].firstEdge;
    while(node != NULL)
    {
        if(!visted[node->ivex])
            DFS(node->ivex, visted);
        node = node->nextEdge;
    }
}

void ListDG::DFS()
{
    int* visted;
    visted = new int[mVexNum];
    for(int i=0; i<mVexNum; i++)
        visted[i] = 0;
    cout <<  "DFS: ";
    for(int i=0; i<mVexNum; i++)
    {
        if(!visted[i])
            DFS(i, visted);
    }
    cout << endl;
}

void ListDG::BFS()
{
    int head = 0;
    int rear = 0;
    int* queue;
    int* visited;
    ENode* node;
    queue = new int[mVexNum];
    visited = new int[mVexNum];
    for(int i=0; i<mVexNum; i++)
        visited[i] = 0;
    cout << "BFS: ";
    for(int i=0; i<mVexNum; i++)
    {
        if(!visited[i])
        {
            visited[i] = 1;
            cout << mVexs[i].data << " ";
            queue[rear++] = i;
        }
        while(head != rear)
        {
            int j = queue[head++];
            node = mVexs[j].firstEdge;
            while(node != NULL)
            {
                int k = node->ivex;
                if(!visited[k])
                {
                    visited[k] = 1;
                    cout << mVexs[k].data << " ";
                    queue[rear++] = k;
                }
                node = node->nextEdge;
            }
        }
    }
    cout << endl;
    delete[] visited;
    delete[] queue;
}

void ListDG::print()
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

int ListDG::topSort()
{
    int index = 0;
    int head = 0;
    int rear = 0;
    int* queue;
    int* ins;
    char* tops;
    ENode* node;
    ins = new int[mVexNum];
    queue = new int[mVexNum];
    tops = new char[mVexNum];
    memset(ins, 0, mVexNum*sizeof(int));
    memset(queue, 0, mVexNum*sizeof(int));
    memset(tops, 0, mVexNum*sizeof(char));
    for(int i=0; i<mVexNum; i++)
    {
        node = mVexs[i].firstEdge;
        while(node != NULL)
        {
            ins[node->ivex]++;
            node = node->nextEdge;
        }
    }
    for(int i=0; i<mVexNum; i++)
    {
        if(ins[i] == 0)
            queue[rear++] = i;
    }
    while(head != rear)
    {
        int j = queue[head++];
        tops[index++] = mVexs[j].data;
        node = mVexs[j].firstEdge;
        while(node != NULL)
        {
            ins[node->ivex]--;
            if(ins[node->ivex] == 0)
                queue[rear++] = node->ivex;
            node = node->nextEdge;
        }
    }
    if(index != mVexNum)
    {
        cout << "Graph has a cycle" << endl;
        delete queue;
        delete ins;
        delete tops;
        return 1;
    }
    cout << "TopSort: ";
    for(int i=0; i<mVexNum; i++)
        cout << tops[i] << " ";
    cout << endl;
    delete queue;
    delete ins;
    delete tops;
    return 0;
}

int main()
{
    char vexs[] = {'A','B','C','D','E','F','G'};
    char edges[][2] = {{'A','G'},{'B','A'},{'B','D'},{'C','F'},{'C','G'},{'D','E'},{'D','F'}};
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);
    ListDG* pG;
    pG = new ListDG(vexs, vlen, edges, elen);
    pG->print();
    pG->DFS();
    return 0;
}
