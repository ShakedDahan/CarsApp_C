#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdbool.h>
#include<malloc.h>
typedef struct Graph* Graph;
typedef Graph DirectedGraph;
typedef Graph UndirectedGraph;
typedef int Node;
DirectedGraph DirectedGraphCreate(int num_node);
UndirectedGraph UndirectedGraphCreate(int num_node);
void GraphDestroy(Graph g);
void addEdge(Graph g, Node i, Node j);
void eraseEdge(Graph g, Node i, Node j);
int numNodes(Graph g);
bool edgeExists(Graph g, Node i, Node j);
int isMainGruop(int** g,int graphSize,int group[],int gruopSize);
#endif