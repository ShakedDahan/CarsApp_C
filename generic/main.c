#include "Graph.h"
int main()
{
UndirectedGraph p;
p=UndirectedGraphCreate(7);
addEdge(p,0,1);
addEdge(p,0,6);
addEdge(p,1,3);
addEdge(p,1,5);
addEdge(p,2,1);
addEdge(p,2,3);
addEdge(p,2,6);
addEdge(p,3,4);
addEdge(p,4,5);
addEdge(p,4,6);
addEdge(p,5,6);
int group[]={0,3,5};
isMainGruop(P,7,group,3);

    return 0;
}