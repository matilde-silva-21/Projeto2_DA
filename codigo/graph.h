// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>
#include <queue>
#include <iostream>

using namespace std;

class Graph {
    struct Edge {
        int src;   // Source node
        int dest;   // Destination node
        int capacity; // An integer capacity
        int duration; // An integer duration
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

    // Depth-First Search: example implementation
    void dfs(int v);

    // Breadth-First Search: example implementation
    void bfs(int v);

    // ----- Functions to implement in this class -----
    int outDegree(int v);

    int connectedComponents();

    int giantComponent();

    list<int> topologicalSorting();

    int distance(int a, int b);

    int diameter();

    bool hasCycle();

    int dfs1(int v, int &count);

    void dfs2(int v, list<int> &order);

    int bfs1(int v, int b);

    int bfs2();

    pair<vector<int>,int> dijkstra_maximize_capacity(int start, int finish);

    pair<vector<int>,int> dijkstra_minimize_edges(int start, int finish);

    list<int> getAdjNodes(int n) {
        list<int> final;
        for(auto e: nodes[n].adj){
            final.push_back(e.dest);
        }
        return final;
    }

    /** @BRIEF Se existir uma edge entre os nodes a e b, a função retorna a capacidade dessa edge, caso contrário retorna -1.**/
    int getEdgeCapacity(int a, int b);


};

#endif
