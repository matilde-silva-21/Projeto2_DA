// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#include "graph.h"
#include "minHeap.h"
#include "maxHeap.h"
#include <algorithm>


// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {
}

// Add edge from source to destination with a certain capacity and duration
void Graph::addEdge(int src, int dest, int capacity, int duration) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({src, dest, capacity, duration});
    if (!hasDir) nodes[dest].adj.push_back({src, dest, capacity, duration});
}

pair<vector<int>,int> Graph::dijkstra_minimize_edges(int start, int finish) {

    float distance[n+1];
    MinHeap<int, float> heap(n,0);
    int predecessor[n+1];
    vector<int> course;

    for(int i=1;i<=nodes.size(); i++){
        distance[i] = UINT32_MAX;
        nodes[i].visited = false;
    }

    heap.insert(start, 0.0);

    while(heap.getSize()!=0){
        pair<int,float> p = heap.removeMin();
        int min = p.first, finn = UINT16_MAX;
        nodes[min].visited = true;
        if(min == finish) {
            int one = finish, two;

            course.push_back(finish);

            while(one!=start){
                two = predecessor[one];
                course.emplace(course.begin(),two);
                int cap = getEdgeCapacity(two,one);
                one = two;
                if(cap != -1 && cap < finn) finn = cap;
            }
            return make_pair(course, finn);
        }
        for(auto& e: nodes[min].adj){
            if(nodes[e.dest].visited) break;

            else{
                int destine = e.dest;
                float weight = e.capacity + p.second;
                predecessor[destine]=min;
                if(!heap.hasKey(destine)) heap.insert(destine,weight);
                else heap.decreaseKey(destine,weight);
            }
        }

    }
    return make_pair(course, -1);
}

pair<vector<int>,int> Graph::dijkstra_maximize_capacity(int start, int finish){
    int pai[n], cap[n];
    MaxHeap<int, int> q(n, -1);

    vector<int> path;

    cap[start] = UINT16_MAX;
    int last=finish, cur=0, min=cap[start], count=0;


    for(int i=0; i<n; i++){
        pai[i] = -1;
        if(i!=start) cap[i] = 0;
        q.insert(i, cap[i]);
    }

    while(q.getSize()!=0){
        pair<int, int> v = q.removeMax();
        for(Edge edge: nodes[v.first].adj){
            if(std::min(v.second, edge.capacity) > cap[edge.dest]){
                cap[edge.dest] = std::min(v.second, edge.capacity);
                pai[edge.dest] = v.first;
                q.increaseKey(edge.dest, cap[edge.dest]);
            }
        }
    }


    while(last != start){
        path.insert(path.begin(), last);
        cur = pai[last];
        if(cap[cur] < min) {min = cap[cur];}
        last = cur;
    }

    path.insert(path.begin(), start);

    return make_pair(path, min);
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

int Graph::getEdgeCapacity(int a, int b) {
    for(auto i: nodes[a].adj){
        if(i.dest==b) return i.capacity;
    }
    return -1;
}
