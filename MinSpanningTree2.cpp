#include <iostream>

using namespace std;

class EData
{
public:
    char start;
    char end;
    int weight;
public:
    EData(){}
    EData(char s, char e, int w):
        start(s), end(e), weight(w){}
};

class ListUDG
{
    #define MAX 100
    #define INF ~(0x1<<31)
private:
    class ENode
    {
    public:
        int ivex;
        int weight;
        ENode* nextEdge;
        friend class ListUDG;
    };
    class VNode
    {
    public:
        char data;
        ENode* firstEdge;
        friend class listUDG;
    };
private:
    int mVexNum;
    int mEdgNum;
    VNode mVexs[MAX];
public:
    ListUDG();
    ListUDG(char vexs[], int vlen, EData* edges[], int elen);
    ~ListUDG();

    void DFS();
    void BFS();
    void print();
    void prim(int start);
    void kruskal();
private:
    char readChar();
    int getPos(char c);
    void DFS(int i, int* visited);
    void linkLast(ENode* list, ENode* node);
    int getWeight(int start, int end);
    EData* getEdges();
    void sortEdges(EData* edges, int elen);
    int getEnd(int vends[], int i);
};

ListUDG::ListUDG()
{
    char c1, c2;
    int p1, p2;
    int weight;
    ENode *node1, *node2;

    cout << "input vertex number: ";
    cin >> mVexNum;
    cout << "input edge number:";
    cin >> mEdgNum;
    if(mVexNum<1 || mEdgNum<1 || mEdgNum>(mVexNum*(mVexNum-1)))
    {
        cout << "input error: invalid parameters!" << endl;
        return;
    }
    for (int i=0; i<mEdgNum; i++)
    {
        cout << "edge(" << i << "): ";
        c1 = readChar();
        c2 = readChar();
        cin >> weight;

        p1 = getPos(c1);
        p2 = getPos(c2);

        node1 = new ENode();
        node1->ivex = p2;
        node1->weight = weight;
        if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);

        node2 = new ENode();
        node2->ivex = p1;
        node2->weight = weight;
        if(mVexs[p2].firstEdge == NULL)
            mVexs[p2].firstEdge = node2;
        else
            linkLast(mVexs[p2].firstEdge, node2);
    }
}

ListUDG::ListUDG(char vexs[], int vlen, EData* edges[], int elen)
{
    char c1, c2;
    int p1, p2;
    int weight;
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
        c1 = edges[i]->start;
        c2 = edges[i]->end;
        weight = edges[i]->weight;

        p1 = getPos(c1);
        p2 = getPos(c2);

        node1 = new ENode();
        node1->ivex = p2;
        node1->weight = weight;
        if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);

        node2 = new ENode();
        node2->ivex = p1;
        node2->weight = weight;
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

int ListUDG::getPos(char c)
{
    for(int i=0; i<mVexNum; i++)
    {
        if(mVexs[i].data == c)
            return i;
    }
    return -1;
}

char ListUDG::readChar()
{
    char c;
    do
    {
        cin >> c;
    }
    while(!((c>='a' && c<='z') || (c>='A' && c<='Z')));

    return c;
}

void ListUDG::DFS(int i, int* visited)
{
    ENode* node;
    visited[i] = 1;
    cout << mVexs[i].data << " ";
    node = mVexs[i].firstEdge;
    while(node != NULL)
    {
        if(!visited[node->ivex])
            DFS(node->ivex, visited);
        node = node->nextEdge;
    }
}

void ListUDG::DFS()
{
    int visited[MAX];
    for(int i=0; i<mVexNum; i++)
        visited[i] = 0;
    cout << "DFS: ";
    for(int i=0; i<mVexNum; i++)
    {
        if(!visited[i])
            DFS(i, visited);
    }
    cout << endl;
}

void ListUDG::BFS()
{
    int head = 0;
    int rear = 0;
    int queue[MAX];
    int visited[MAX];
    ENode* node;
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

int ListUDG::getWeight(int start, int end)
{
    ENode* node;
    if(start == end)
        return 0;
    node = mVexs[start].firstEdge;
    while(node != NULL)
    {
        if(end == node->ivex)
        {
            return node->weight;
        }
        node = node->nextEdge;
    }
    return INF;
}

void ListUDG::prim(int start)
{
    char prim[MAX];
    int weights[MAX];
    int index = 0;

    prim[index++] = mVexs[start].data;
    for(int i=0; i<mVexNum; i++)
        weights[i] = getWeight(start, i);
    for(int i=0; i<mVexNum; i++)
    {
        if(start == i)
            continue;
        int j = 0;
        int k = 0;
        int min = INF;
        while(j<mVexNum)
        {
            if(weights[j]!=0 && weights[j]<min)
            {
                min = weights[j];
                k = j;
            }
            j++;
        }
        prim[index++] = mVexs[k].data;
        weights[k] = 0;
        for(j=0; j<mVexNum; j++)
        {
            int tmp = getWeight(k, j);
            if(weights[j]!=0 && tmp<weights[j])
                weights[j] = tmp;
        }
    }

    int sum = 0;
    for(int i=1; i<mVexNum; i++)
    {
        int min = INF;
        int n = getPos(prim[i]);
        for(int j=0; j<i; j++)
        {
            int m = getPos(prim[j]);
            int tmp = getWeight(m, n);
            if(tmp < min)
                min = tmp;
        }
        sum += min;
    }
    cout << "Prim(" << mVexs[start].data << ") = " << sum << ": ";
    for(int i=0; i<index; i++)
        cout << prim[i] << " ";
    cout << endl;
}

EData* ListUDG::getEdges()
{
    int index = 0;
    EData* edges = new EData[mEdgNum];
    ENode* node;
    for(int i=0; i<mVexNum; i++)
    {
        node = mVexs[i].firstEdge;
        while(node != NULL)
        {
            if(node->ivex > i)
            {
                edges[index].start = mVexs[i].data;
                edges[index].end = mVexs[node->ivex].data;
                edges[index].weight = node->weight;
                index++;
            }
            node = node->nextEdge;
        }
    }
    return edges;
}

void ListUDG::sortEdges(EData* edges, int elen)
{
    for(int i=0; i<elen; i++)
    {
        for(int j=i+1; j<elen; j++)
        {
            if(edges[i].weight > edges[j].weight)
            {
                swap(edges[i], edges[j]);
            }
        }
    }
}

int ListUDG::getEnd(int vends[], int i)
{
    while(vends[i] != 0)
        i = vends[i];
    return i;
}

void ListUDG::kruskal()
{
    int p1, p2;
    int m, n;
    int index = 0;
    int vends[MAX] = {0};
    EData res[MAX];
    EData* edges = getEdges();
    sortEdges(edges, mEdgNum);
    for(int i=0; i<mEdgNum; i++)
    {
        p1 = getPos(edges[i].start);
        p2 = getPos(edges[i].end);

        m = getEnd(vends, p1);
        n = getEnd(vends, p2);

        if(m != n)
        {
            vends[m] = n;
            res[index++] = edges[i];
        }
    }
    delete[] edges;

    int length = 0;
    for(int i=0; i<index; i++)
    {
        length += res[i].weight;
    }
    cout << "Kruskal = " << length << " : ";
    for(int i=0; i<index; i++)
        cout << "(" << res[i].start << ", " << res[i].end << ") ";
    cout << endl;
}

int main()
{
    char vexs[] = {'A','B','C','D','E','F','G'};
    EData* edges[] = {
        new EData('A', 'B', 12),
        new EData('A', 'F', 16),
        new EData('A', 'G', 14),
        new EData('B', 'C', 10),
        new EData('B', 'F', 7),
        new EData('C', 'D', 3),
        new EData('C', 'E', 5),
        new EData('C', 'F', 6),
        new EData('D', 'E', 4),
        new EData('E', 'F', 2),
        new EData('E', 'G', 8),
        new EData('F', 'G', 9)
    };
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);
    ListUDG* pG;

    pG = new ListUDG(vexs, vlen, edges, elen);
    pG->print();
    pG->DFS();
    pG->BFS();
    pG->prim(0);
    pG->kruskal();

    return 0;
}
