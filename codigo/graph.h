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
        int dest;  // Destination node
        int capacity; // An integer capacity
        int duration; // An integer duration
        int flow;
        bool operator ==(Edge& e1) const;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;  // As the node been visited on a search
        vector<int> reachable_nodes;
    };

    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir);

    // Add edge from source to destination with a certain capacity and duration
    void addEdge(int src, int dest, int capacity, int duration);

    // Depth-First Search: example implementation
    void dfs(int v);

    // Breadth-First Search: example implementation
    vector<int> bfs(int v);

    int connectedComponents();

    int dfs1(int v, int &count);

    void dfs2(int v, list<int> &order);

    int getN();

    /** @BRIEF Determina o caminho com menos edges desde node v ao node b. Retorna o respetivo caminho e a capacidade do mesmo.**/
    pair<int, vector<Graph::Edge>> bfs1(int v, int b);

    /** @BRIEF Determina todos os caminhos possíveis desde node v ao node b.**/
    vector<pair<int, vector<vector<int>>>> allPossiblePaths(int start, int end, int edgeBound, int capBound);

    /** @BRIEF Determina a capacidade de um caminho.**/
    int getPathCap(vector<int>& path);

    /** @BRIEF Determina o caminho com maior capacidade. Retorna um vector que corresponde aos nodes que pertencem ao caminho e um int, a capacidade desse mesmo caminho.**/
    pair<vector<int>,int> dijkstra_maximize_capacity(int start, int finish);

    /** @BRIEF Se existir uma edge entre os nodes a e b, a função retorna a capacidade dessa edge, caso contrário retorna -1.**/
    Edge* getEdge(int a, int b);

    /** @BRIEF Retorna o valor do fluxo máximo de um dado grafo, partindo de flow 0.**/
    int edmonds_karp(int start, int finish);

    /** @BRIEF Retorna true caso exista uma edge entre a e b, caso contrário, false.**/
    bool edgeExists(int a, int b);

    /** @BRIEF Retorna o valor do fluxo de um dado grafo, sendo este valor maior ou igual a um valor flowObjective.**/
    int edmonds_karp_2(int start, int finish, int flowObjective, Graph& residual_network);

    /** @BRIEF Retorna o valor do fluxo de um dado grafo.**/
    int getFlow(int start);

    /** @BRIEF Retorna o grafo que representa o encaminhamento para fluxo igual a flowObjective. O valor individualPaths, passado por referência, contém todos os caminhos deste grafo.**/
    Graph extractPath(int start, int finish, int flowObjective, vector<pair<vector<int>,int>>& individualPaths, Graph& residual_network);

    /** @BRIEF Determina o caminho que maximiza o fluxo. Retorna um vector que corresponde aos nodes que pertencem ao caminho e um int, o fluxo desse mesmo caminho.**/
    pair<vector<int>,int> dijkstra_maximize_flow(int start, int finish);


};

#endif
