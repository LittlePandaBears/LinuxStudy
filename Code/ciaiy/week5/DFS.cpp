#include <cstdio>
#include <queue>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_VERTEX_NUM 20
#define INFINITY 32678
#define NOSET 0

typedef int AdjType;
typedef int OtherInfo;
typedef int VertexData;

typedef struct ArcNode
{
    AdjType adj;
    OtherInfo info;
} ArcNode;

typedef struct
{
    VertexData vertex[MAX_VERTEX_NUM];
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum, arcnum;
} AdjMatrix;

bool createGraph(AdjMatrix **adj);
void insertVertex(AdjMatrix *adj, VertexData data);
void insertArc(AdjMatrix *adj, int source, int target, int weight);
void DFS(AdjMatrix *adj);

void DFS(AdjMatrix *adj) {
    
}

void insertArc(AdjMatrix *adj, int source, int target, int weight)
{
    adj->arcs[source][target].adj = 1;
    adj->arcs[source][target].info = weight;
    adj->arcnum++;
}

void insertVertex(AdjMatrix *adj, VertexData data)
{
    adj->vertex[adj->vexnum] = data;
    adj->vexnum++;
}

bool createGraph(AdjMatrix **adj)
{
    if (*adj != NULL)
    {
        return false;
    }

    *adj = (AdjMatrix *)malloc(sizeof(AdjMatrix));
    bzero(*adj, sizeof(AdjMatrix));

    return true;
}

int main(void)
{
    AdjMatrix *adj = NULL;
    createGraph(&adj);
    insertVertex(adj, '0');
    insertVertex(adj, '1');
    insertVertex(adj, '2');
    insertVertex(adj, '3');
    insertVertex(adj, '4');
    insertArc(adj, 0, 2, NOSET);
    insertArc(adj, 1, 0, NOSET);
    insertArc(adj, 1, 4, NOSET);
    insertArc(adj, 2, 0, NOSET);
    insertArc(adj, 3, 2, NOSET);
    insertArc(adj, 4, 2, NOSET);
    insertArc(adj, 4, 1, NOSET);

    return 0;
}