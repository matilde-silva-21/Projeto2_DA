// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include "minHeap.h"
#include "maxHeap.h"
#include <algorithm>
#include "iterator"

using namespace std;

class Graph {
    struct Edge {
        int src;   // Source node
        int dest;   // Destination node
        int capacity; // An integer capacity
        int duration; // An integer duration
        int flow;

        bool operator ==(Edge& e1) const;
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;  // As the node been visited on a search?
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir);

    // Add edge from source to destination with a certain capacity and duration
    void addEdge(int src, int dest, int capacity, int duration);

    void deleteEdge(int src, int dest);

    // Depth-First Search: example implementation
    void dfs(int v);

    // Breadth-First Search: example implementation
    void bfs(int v);

    int connectedComponents();

    int dfs1(int v, int &count);

    void dfs2(int v, list<int> &order);

    /** @BRIEF Determina o caminho com menos edges desde node v ao node b.**/
    pair<int, vector<Graph::Edge>> bfs1(int v, int b);

    int bfs2();

    /** @BRIEF Determina o caminho com maior capacidade. Retorna um vector que corresponde aos nodes que pertencem ao caminho e um int, a capacidade desse mesmo caminho.**/
    pair<vector<int>,int> dijkstra_maximize_capacity(int start, int finish);

    /** @BRIEF Determina o caminho com menor quantidade de transbordos. Retorna um vector que corresponde aos nodes que pertencem ao caminho e um int, a capacidade desse mesmo caminho.**/
    pair<vector<int>,int> dijkstra_minimize_edges(int start, int finish);

    /** @BRIEF Se existir uma edge entre os nodes a e b, a função retorna a capacidade dessa edge, caso contrário retorna -1.**/
    Edge* getEdge(int a, int b);

    /** @BRIEF Retorna o valor do fluxo máximo de um dado grafo, partindo de flow 0.**/
    int edmonds_karp(int start, int finish);

    /** @BRIEF Retorna true caso exista uma edge entre a e b, caso contrário, false.**/
    bool edgeExists(int a, int b);



};

#endif
