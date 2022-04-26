#include "Graph.h"

struct Graph {
int** matrix;
int num_nodes;
bool is_directed;
};
Graph GraphCreate(int num_nodes, bool is_directed);
UndirectedGraph UndirectedGraphCreate(int num_nodes) {
return GraphCreate(num_nodes, false);
}
DirectedGraph DirectedGraphCreate(int num_nodes) {
return GraphCreate(num_nodes, true);
}

Graph GraphCreate(int num_nodes, bool is_directed)
{
Graph g = (Graph)malloc(sizeof(struct Graph));
int i, n;
g->num_nodes = num_nodes;
g->is_directed = is_directed;
n=sizeof(int*)*g->num_nodes;
g->matrix = (int**)malloc(n);
n=g->num_nodes*g->num_nodes;
g->matrix[0] = (int*)calloc(n, sizeof(int));
for(i=1; i<g->num_nodes; i++)
g->matrix[i] = (g->matrix[0]+i*g->num_nodes);
return g;
}

void GraphDestroy(Graph g) {
free(g->matrix[0]);
free(g->matrix);
free(g);
}
void addEdge(Graph g, Node i, Node j) {
g->matrix[i][j] = 1;
if(!g->is_directed)
g->matrix[j][i] = 1;
}
void eraseEdge(Graph g, Node i, Node j) {
g->matrix[i][j] = 0;
if(!g->is_directed)
g->matrix[j][i] = 0;
}

int numNodes(Graph g) {
return g->num_nodes;
}
bool edgeExists(Graph g, Node i, Node j) {
return (g->matrix[i][j] != 0);
}

int inGroup(int num,int group[],int groupSize)
{
    int i;
    for(i=0;i<groupSize;i++)
    {
        if(num==group[i])
        {
        return 0;

        }
    }
    return 1;
}
int isMainGruop(int** g,int graphSize,int group[],int gruopSize)
{
    int i,j;
    for(i=0;i<graphSize;i++)
    {
        if(inGroup(i,group,gruopSize))
        {
            for(j=0;j<gruopSize;j++)
            {
                if(edgeExists(g,i,group[j]))
                {
                    break;    
                }
                if(j+1==gruopSize)
                {
                    printf("Node %d dosent linked to any node from main group",i);
                return 0;  
                }        
            }
        }
   }
    printf("this group is a main group");
   return 1;
}