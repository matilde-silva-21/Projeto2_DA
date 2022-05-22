// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#include "graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e: nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

int Graph::dfs1(int v, int &count) {
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e: nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) {
            count++;
            dfs1(w, count);
        }
    }

    return count;
}

void Graph::dfs2(int v, list<int> &order) {
    nodes[v].visited = true;
    for (auto e: nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited) {
            dfs2(w, order);
        }
    }
    order.emplace(order.begin(), v);
}


// Depth-First Search: example implementation
void Graph::bfs(int v) {
    for (int v = 1; v <= n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        cout << u << " "; // show node order
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

// ----------------------------------------------------------
// Exercicio 1: Introdução a uma classe simplificada de grafos
// ----------------------------------------------------------

// ..............................
// a) Contando diferentes somas de pares
// TODO
int Graph::outDegree(int v) {
    if (v >= 1 && v <= n) return nodes[v].adj.size();
    else return -1;
}

// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {
    int counter = 0;
    for (int v = 1; v <= n; v++) { nodes[v].visited = false; }
    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited) {
            counter++;
            dfs(v);
        }
    }

    return counter;
}


// ..............................
// b) Componente gigante
// TODO
int Graph::giantComponent() {
    int counter = 0, cur = 1, max = 0;
    for (int v = 1; v <= n; v++) { nodes[v].visited = false; }
    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited)dfs1(v, cur);
        if (cur > max) max = cur;
        cur = 1;
    }
    return max;
}


// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<int> Graph::topologicalSorting() {
    list<int> order;
    for (int v = 1; v <= n; v++) { nodes[v].visited = false; }
    for (int v = 1; v <= n; v++) {
        if (!nodes[v].visited) {
            dfs2(v, order);
        }
    }

    return order;
}

// ----------------------------------------------------------
// Exercicio 4: Distancias em grafos nao pesados
// ----------------------------------------------------------


// ..............................
// a) Distancia entre dois nos
// TODO
int Graph::distance(int a, int b) {
    return bfs1(a, b);
}

// ..............................
// b) Diametro
// TODO
int Graph::diameter() {
    return bfs2();
}

// ----------------------------------------------------------
// Exercicio 5: To or not be… a DAG!
// ----------------------------------------------------------
// TODO
bool Graph::hasCycle() {
    return false;
}

//esta funcao ve a menor distancia do nó V ao nó B (para grafos sem peso)
int Graph::bfs1(int v, int b) {
    if (v == b) return 0;
    //distance representa a distancia de qualquer node ao node 1
    int predecessor[nodes.size() + 1], distance[nodes.size() + 1];
    for (int i = 1; i <= n; i++) {
        distance[i] = INT16_MAX;
        predecessor[i] = -1;
        nodes[i].visited = false;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    distance[v] = 0;
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        cout << u << " "; // show node order
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                distance[w] = distance[u] + 1;
                predecessor[w] = u;
                q.push(w);
                nodes[w].visited = true;

                if (w == b) return distance[b];
            }


        }
    }

    return -1;
}

int Graph::bfs2() {

    if (connectedComponents() > 1) return -1;
    int max = 0;

    //distance representa a distancia de qualquer node ao node 1
    int predecessor[nodes.size() + 1], distance[nodes.size() + 1];
    for (int i = 1; i <= n; i++) {
        distance[i] = INT16_MAX;
        predecessor[i] = -1;
        nodes[i].visited = false;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(1);
    distance[1] = 0;
    nodes[1].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        cout << u << " "; // show node order
        for (auto e: nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                distance[w] = distance[u] + 1;
                predecessor[w] = u;
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }

    for (int i = 1; i < nodes.size(); i++) {
        if (distance[i] > max) max = distance[i];
    }

    return max;
}
