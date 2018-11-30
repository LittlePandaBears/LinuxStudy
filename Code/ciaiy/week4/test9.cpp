#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAX_VERTEX_NUM  20  // 最多顶点个数
#define NOSET 0

typedef char VertexData;

typedef struct ArcNode {
    int adjvex;
    int otherInfo;
    struct ArcNode *nextArc;
}ArcNode;

typedef struct VertexNode {
    VertexData data;
    ArcNode *first;
}VertexNode;

typedef struct {
    VertexNode vertex[MAX_VERTEX_NUM];
    int vexnum, arcnum;
}AdjList;

bool initGraph(AdjList *adj);
bool insertVertex(AdjList *adj, VertexNode vertex);
bool insertArc(AdjList *adj, int sourceArc, int targetArc, int weight);
void showGraph(AdjList *adj);
bool deleteVertex(AdjList *adj, int index);
bool deleteArc(AdjList *adj, int source , int target);
void clearArc(AdjList *adj, int index);

void clearArc(AdjList *adj, int index) {
    for(int i = 0; i < adj->vexnum; i++) {
        if(i == index) {
            continue;
        }
        ArcNode *arc = adj->vertex[i].first;
        while(arc != NULL) {
            printf("$$%d$$\n", arc->adjvex);
            if(arc->adjvex == index) {
                printf("%d %d被杀了\n", i, index);
                deleteArc(adj, i, index);
            }
            arc = arc->nextArc;
        }
    }
}

bool deleteArc(AdjList *adj, int source , int target) {
    if(source < 0 || source >= adj->vexnum || target < 0 || target >= adj->vexnum) {
        return false;       
    }

    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->nextArc = adj->vertex[source].first;

    if(p->nextArc->adjvex == target) {
        ArcNode *ptemp = p->nextArc->nextArc;
        free(p->nextArc);
        adj->vertex[source].first = ptemp;
        adj->arcnum--;
        return true;
    }
    
    ArcNode *pb = p;
    p = p->nextArc;
    while(p->adjvex != target) {
        pb = p;
        p = p->nextArc;
    }
    pb->nextArc = p->nextArc;
    free(p);
    adj->arcnum--;

    return true;
}

bool deleteVertex(AdjList *adj, int index) {
    if(index >= adj->vexnum || index < 0) {
        return false;
    }

    ArcNode *arc = adj->vertex[index].first;


    clearArc(adj, index);
    showGraph(adj);
    printf("%%%%\n");

    if(arc != NULL) {
        ArcNode *after = arc->nextArc;
        while(after != NULL) {
            free(arc);
            arc = after;
            after = after->nextArc;
        }
    }

    for(int i = index; i < adj->vexnum - 1; i++) {
        adj->vertex[i] = adj->vertex[i + 1];
    }

    adj->vexnum--;
}

void showGraph(AdjList *adj) {
    for(int i = 0; i < adj->vexnum; i++) {
        printf("%d | %c -> ", i, adj->vertex[i].data);
        ArcNode *arc = adj->vertex[i].first;
        while(arc != NULL) {
            printf("%d(%d) ", arc->adjvex, arc->otherInfo);
            arc = arc->nextArc;
        }
        printf("\n");
    }
}

bool insertArc(AdjList *adj, int sourceArc, int targetArc, int weight) {
    int vertexNum = adj->vexnum;
    
    if(sourceArc >= vertexNum || targetArc >= vertexNum) {
        return false;
    }
    
    ArcNode *pNew = adj->vertex[sourceArc].first;
    if(pNew != NULL) {
        while((pNew->nextArc != NULL)) {
            pNew = pNew->nextArc;
        }
        pNew->nextArc = (ArcNode *)malloc(sizeof(ArcNode));
        bzero(pNew->nextArc,  sizeof(ArcNode));
        pNew = pNew->nextArc;
    }else {
        adj->vertex[sourceArc].first = (ArcNode *)malloc(sizeof(ArcNode));
        bzero(adj->vertex[sourceArc].first, sizeof(ArcNode));
        pNew = adj->vertex[sourceArc].first;
    }

    pNew->adjvex = targetArc;
    pNew->otherInfo = weight;    
    adj->arcnum++;

    return true;
}


bool insertVertex(AdjList *adj, VertexNode vertex) {
    int vertexNum = adj->vexnum;

    if(vertexNum >= MAX_VERTEX_NUM) {
        return false;
    }

    adj->vertex[vertexNum].data = vertex.data;
    adj->vertex[vertexNum].first = NULL;
    adj->vexnum++;
    return true;
}

bool initGraph(AdjList **adj) {
    if(*adj != NULL) {
        return false;
    }

    *adj = (AdjList *)malloc(sizeof(AdjList));
    bzero(*adj, sizeof(AdjList));
    return true;
}

int main(void) {
    AdjList *adj = NULL;
    initGraph(&adj);

    while(true) {
        printf("1. add vertex\n");
        printf("2. add arc\n");
        printf("3. delete vertex\n");
        printf("4. delete arc\n");
        char ch = getchar();
        getchar();
        VertexNode v;
        if(ch == '1') {
            printf("插入的数据");
            v.data = getchar();
            getchar();
            insertVertex(adj, v);
        }else if(ch == '2') {
            int source, target, weight;
            printf("输入节点下标， 目标节点下标");
            scanf("%d%d", &source, &target);
            insertArc(adj, source, target, NOSET);   
        }else if(ch == '3') {
            printf("要删除的下标:");
            int index;
            scanf("%d", &index);
            deleteVertex(adj, index);
        }else if(ch == '4') {
            int source, target, weight;
            printf("输入节点下标， 目标节点下标");
            scanf("%d%d", &source, &target);
            deleteArc(adj, source, target);  
        }
            showGraph(adj);
        
    }

    return 0;
}