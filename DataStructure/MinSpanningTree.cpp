/**
 *Constructing a minimum spanning tree using the Kruskal algorithm
 */

 #include <iostream>
 #include <vector>
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

 class MatrixUDG
 {
     #define MAX 100
     #define INF (~(0x1<<31))
 private:
    char mVexs[MAX];
    int mVexNum;
    int mEdgNum;
    int mMatrix[MAX][MAX];
 public:
    MatrixUDG();
    MatrixUDG(char vexs[], int vlen, int matrix[][9]);
    ~MatrixUDG();

    void DFS();
    void BFS();
    void prim(int start);
    void kruskal();
    void print();
 private:
    char readChar();
    int getPosition(char ch);
    int firstVertex(int v);
    int nextVertex(int v, int w);
    void DFS(int i, int* visited);
    EData* getEdges();
    void sortEdges(EData* edges, int elen);
    int getEnd(int vends[], int i);
 };

 MatrixUDG::MatrixUDG()
 {
     char c1, c2;
     int p1, p2, weight;
     cout << "input vertex number: ";
     cin >> mVexNum;
     cout << "input edges number: ";
     cin >> mEdgNum;
     if(mVexNum<1 || mEdgNum<1 || mEdgNum<(mVexNum*(mVexNum-1)))
     {
         cout << "input error: invalid parameters!" << endl;
         return;
     }
     for (int i=0; i<mVexNum; i++)
     {
         cout << "vertex(" << i << "): ";
         mVexs[i] = readChar();
     }
     for(int i=0; i<mVexNum; i++)
     {
        for(int j=0; j<mVexNum; j++)
        {
            if(i == j)
                mMatrix[i][j] == 0;
            else
                mMatrix[i][j] == INF;
        }
     }
     for(int i=0; i<mEdgNum; i++)
     {
         cout << "edge(" << i << "): ";
         c1 = readChar();
         c2 = readChar();
         cin >> weight;
         p1 = getPosition(c1);
         p2 = getPosition(c2);
         if(p1==-1 || p2==-1)
         {
             cout << "input error: invalid edge!" << endl;
             return;
         }
         mMatrix[p1][p2] = weight;
         mMatrix[p2][p1] = weight;
     }
 }

 MatrixUDG::MatrixUDG(char vexs[], int vlen, int matrix[][9])
 {
     mVexNum = vlen;
     for(int i=0; i<mVexNum; i++)
        mVexs[i] = vexs[i];
     for(int i=0; i<mVexNum; i++)
     {
         for(int j=0; j<mVexNum; j++)
            mMatrix[i][j] = matrix[i][j];
     }
     for(int i=0; i<mVexNum; i++)
     {
         for(int j=0; j<mVexNum; j++)
         {
             if(i!=j && mMatrix[i][j]!=INF)
                mEdgNum++;
         }
     }
     mEdgNum /= 2;
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

 int MatrixUDG::firstVertex(int v)
 {
     if(v<0 || v>(mVexNum-1))
        return -1;
     for(int i=0; i<mVexNum; i++)
     {
         if(mMatrix[v][i]!=0 && mMatrix[v][i]!=INF)
            return i;
     }
     return -1;
 }

 int MatrixUDG::nextVertex(int v, int w)
 {
    if(v<0 || v>(mVexNum-1) || w<0 || w>(mVexNum-1))
        return -1;
    for(int i=w+1; i<mVexNum; i++)
    {
        if(mMatrix[v][i]!=0 && mMatrix[v][i]!=INF)
            return i;
    }
    return -1;
 }

 void MatrixUDG::DFS(int i, int* visited)
 {
     visited[i] = 1;
     cout << mVexs[i] << " ";
     for(int w=firstVertex(i); w>=0; w=nextVertex(i, w))
     {
         if(!visited[w])
            DFS(w, visited);
     }
 }

 void MatrixUDG::DFS()
 {
     int visited[MAX];
     for(int i=0; i<mVexNum; i++)
     {
         visited[i] = 0;
     }
     cout << "DFS: ";
     for(int i=0; i<mVexNum; i++)
     {
         if(!visited[i])
            DFS(i, visited);
     }
     cout << endl;
 }

 void MatrixUDG::BFS()
 {
     int head = 0;
     int rear = 0;
     int queue[MAX];
     int visited[mVexNum];
     for(int i=0; i<mVexNum; i++)
        visited[i] = 0;
     cout << "BFS: ";
     for(int i=0; i<mVexNum; i++) //确保所有的顶点都被搜索一遍
     {
         if(!visited[i]) //选择起点，进行一次广度优先搜索
         {
             visited[i] = 1;
             cout << mVexs[i] << " ";
             queue[rear++] = i;
         }
         while(head != rear)
         {
             int j = queue[head++];
             for(int k=firstVertex(j); k>=0; k=nextVertex(j, k))
             {
                 if(!visited[k])
                 {
                     visited[k] = 1;
                     cout << mVexs[k] << " ";
                     queue[rear++] = k;
                 }
             }
         }
     }
     cout << endl;
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

 void MatrixUDG::prim(int start)
 {
     int index = 0;
     char prims[mVexNum];
     int weights[MAX];
     prims[index++] = mVexs[start];
     for(int i=0; i<mVexNum; i++)
        weights[i] = mMatrix[start][i];
     weights[start] = 0;
     for(int i=0; i<mVexNum; i++)
     {
         if(start == i)
            continue;
         int j=0, k=0, min=INF;
         while(j < mVexNum)
         {
             if(weights[j]!=0 && weights[j]<min)
             {
                 min = weights[j];
                 k = j;
             }
             j++;
         }
         prims[index++] = mVexs[k];
         weights[k] = 0;
         for(int j=0; j<mVexNum; j++)
         {
             if(weights[j]!=0 && mMatrix[k][j]<weights[j])
                weights[j] = mMatrix[k][j];
         }
     }
     int sum = 0;
     for(int i=1; i<index; i++)
     {
         int min = INF;
         int n = getPosition(prims[i]);
         for(int j=0; j<i; j++)
         {
             int m = getPosition(prims[j]);
             if(mMatrix[m][n]<min)
                min = mMatrix[m][n];
         }
         sum += min;
     }
     cout << "Prim(" << mVexs[start] << ") = " << sum << ": ";
     for(int i=0; i<index; i++)
        cout << prims[i] << " ";
     cout << endl;
 }

 EData* MatrixUDG::getEdges()
 {
     int index = 0;
     EData* edges;

     edges = new EData[mEdgNum];
     for(int i=0; i<mVexNum; i++)
     {
         for(int j=i+1; j<mVexNum; j++)
         {
             if(mMatrix[i][j] != INF)
             {
                 edges[index].start = mVexs[i];
                 edges[index].end = mVexs[j];
                 edges[index].weight = mMatrix[i][j];
                 index++;
             }
         }
     }
     return edges;
 }

 void MatrixUDG::sortEdges(EData* edges, int elen)
 {
     for(int i=0; i<elen; i++)
     {
         for(int j=i+1; j<elen; j++)
         {
             if(edges[i].weight > edges[j].weight)
                swap(edges[i], edges[j]);
         }
     }
 }

 int MatrixUDG::getEnd(int vends[], int i)
 {
     while(vends[i] != 0)
        i = vends[i];
     return i;
 }

 void MatrixUDG::kruskal()
 {
     int p1, p2;
     int m, n;
     int length;
     int index = 0;
     int vends[MAX] = {0};
     EData res[MAX];
     EData* edges;

     edges = getEdges();
     sortEdges(edges, mEdgNum);
     for(int i=0; i<mEdgNum; i++)
     {
         p1 = getPosition(edges[i].start);
         p2 = getPosition(edges[i].end);

         m = getEnd(vends, p1);
         n = getEnd(vends, p2);
         if(m != n)
         {
             vends[m] = n;
             res[index++] = edges[i];
         }
     }
     delete[] edges;

     length = 0;
     for(int i=0; i<index; i++)
     {
         length += res[i].weight;
     }
     cout << "kruskal = " << length << ": ";
     for(int i=0; i<index; i++)
     {
         cout << "(" << res[i].start << "," << res[i].end << ")";
     }
     cout << endl;
 }

 int main()
 {
     char vexs[] = {'A','B','C','D','E','F','G'};
     int matrix[][9] = {
     {0,12,INF,INF,INF,16,14},
     {12,0,10,INF,INF,7,INF},
     {INF,10,0,3,5,6,INF},
     {INF,INF,3,0,4,INF,INF},
     {INF,INF,5,4,0,2,8},
     {16,7,6,INF,2,0,9},
     {14,INF,INF,INF,8,9,0}};
     int vlen = sizeof(vexs)/sizeof(vexs[0]);
     MatrixUDG* pG;
     pG = new MatrixUDG(vexs, vlen, matrix);
     pG->prim(0);
     pG->kruskal();
     return 0;
 }
