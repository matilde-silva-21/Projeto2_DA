// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#include "graph.h"


// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num + 1) {
}

// Add edge from source to destination with a certain capacity and duration
void Graph::addEdge(int src, int dest, int capacity, int duration) {
    if (src < 1 || src > n || dest < 1 || dest > n) return;
    nodes[src].adj.push_back({src, dest, capacity, duration, 0});
    if (!hasDir) nodes[dest].adj.push_back({src, dest, capacity, duration, 0});
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
                int cap=UINT16_MAX;
                if(edgeExists(two,one)){
                    cap = getEdge(two, one)->capacity;
                }
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
    int pai[n+1], cap[n+1];
    MaxHeap<int, int> q(n+1, -1);

    vector<int> path;

    cap[start] = UINT16_MAX;
    int last=finish, cur=0, min=cap[start], count=0;


    for(int i=1; i<n+1; i++){
        pai[i] = -1;
        if(i!=start) cap[i] = 0;
        q.insert(i, cap[i]);
    }

    while(q.getSize()!=0){
        pair<int, int> v = q.removeMax();
        int failsafe = nodes[v.first].adj.size();
        for(Edge edge: nodes[v.first].adj){
            if(failsafe==0){break;}
            if(std::min(v.second, edge.capacity) > cap[edge.dest]){
                cap[edge.dest] = std::min(v.second, edge.capacity);
                pai[edge.dest] = v.first;
                q.increaseKey(edge.dest, cap[edge.dest]);
            }
            failsafe--;
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


// Breadth-First Search: example implementation
void Graph::bfs(int a) {
    for (int v = 1; v <= n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(a);
    nodes[a].visited = true;
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

//esta funcao ve a menor distancia do nó V ao nó B
std::pair<int, vector<Graph::Edge>> Graph::bfs1(int v, int b) {

    vector<Edge> final;

    if(v == b){return make_pair(0, final);}

    //distance representa a distancia de qualquer node ao node 1
    int predecessor[nodes.size() + 1], distance[nodes.size() + 1], min = INT16_MAX;
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
        int u = q.front(), cf=0;
        q.pop();
        for (auto e: nodes[u].adj) {
            if(e.capacity == 0) continue;
            int w = e.dest;
            if (!nodes[w].visited) {
                distance[w] = distance[u] + 1;
                predecessor[w] = u;
                q.push(w);
                nodes[w].visited = true;

                if (w == b) {
                    while(w!=v){
                        cf = getEdge(predecessor[w], w)->capacity - getEdge(predecessor[w], w)->flow;
                        if(min>cf){min = cf;}
                        final.emplace(final.begin(),*getEdge(predecessor[w], w));
                        w = predecessor[w];
                    }

                    return make_pair(min, final);
                }
            }


        }
    }


    final.clear();
    return make_pair(-1, final);
}


Graph::Edge* Graph::getEdge(int a, int b) {
    for(auto& i: nodes[a].adj){
        if(i.dest==b) return &i;
    }

    return new Graph::Edge{
        -1,-1,-1, -1,-1
    };

}

int Graph::edmonds_karp(int start, int finish) {

    Graph residual_network = *this;
    for(Node& node: nodes){
        for(Edge& e: node.adj){
            e.flow = 0;
        }
    }

    std::pair<int, vector<Graph::Edge>> bfs_result = residual_network.bfs1(start, finish);
    vector<Edge> path = bfs_result.second;
    int cp = bfs_result.first;

    while(cp != -1){
        for(Edge &e: path){
            if(edgeExists(e.src,e.dest)){
                getEdge(e.src, e.dest)->flow += cp;
            }

            else getEdge(e.dest, e.src)->flow -= cp;
        }

        for(auto& node: nodes){
            for(auto& e: node.adj){
                int cf = e.capacity - e.flow;
                if(cf >= 0){
                    if(edgeExists(e.src,e.dest)){residual_network.getEdge(e.src, e.dest)->capacity = cf;}
                    else residual_network.addEdge(e.src,e.dest,cf,-1);
                }
                else{
                    residual_network.addEdge(e.dest,e.src,e.flow,-1);
                }
            }
        }


        bfs_result = residual_network.bfs1(start, finish);
        cp = bfs_result.first;
        path = bfs_result.second;
    }



    return getFlow(start);

}

bool Graph::edgeExists(int a, int b) {
    return getEdge(a,b)->src != -1;
}

bool Graph::Edge::operator==(Graph::Edge &e1) const {
    return (e1.dest == dest &&
    e1.flow == flow &&
    e1.src == src &&
    e1.capacity == capacity &&
    e1.duration == duration);
}

void Graph::allPossiblePaths(int start, int end, vector<int>& curPath, vector<vector<int>>& allPaths, bool& empty) {

    for(auto i: nodes[start].adj){
        curPath.push_back(i.src);
        if(i.dest == end){
            curPath.push_back(i.dest);
            allPaths.push_back(curPath);
            curPath.pop_back();
        }
        else if(nodes[i.dest].adj.empty()){
            curPath.pop_back();
            continue;
        }
        else{
            allPossiblePaths(i.dest,end,curPath,allPaths, empty);
        }
        curPath.pop_back();
    }

}

int Graph::getPathCap(vector<int>& path){
    int min = UINT16_MAX;
    for(int i = 0; i < path.size() - 1; i++){
        int cap = getEdge(path[i], path[i+1])->capacity;
        if(cap < min){min = cap;}
    }
    return min;
}

int Graph::getFlow(int start) {

    int finalflow = 0;

    for(auto& e: nodes[start].adj){
        finalflow += e.flow;
    }

    for(auto& node: nodes){
        for(auto& e: node.adj){
            if(e.dest == start){
                finalflow -= e.flow;
            }
        }
    }

    return finalflow;
}

int Graph::edmonds_karp_2(int start, int finish, int flowObjective, Graph& residual_network) {


    std::pair<int, vector<Graph::Edge>> bfs_result = residual_network.bfs1(start, finish);
    vector<Edge> path = bfs_result.second;
    int cp = bfs_result.first, c = getFlow(start);

    while(cp != -1 && c < flowObjective){
        for(Edge &e: path){
            if(edgeExists(e.src,e.dest)){
                getEdge(e.src, e.dest)->flow += cp;
            }

            else getEdge(e.dest, e.src)->flow -= cp;
        }

        for(auto& node: nodes){
            for(auto& e: node.adj){
                int cf = e.capacity - e.flow;
                if(cf >= 0){
                    if(edgeExists(e.src,e.dest)){residual_network.getEdge(e.src, e.dest)->capacity = cf;}
                    else residual_network.addEdge(e.src,e.dest,cf,-1);
                }
                else{
                    residual_network.addEdge(e.dest,e.src,e.flow,-1);
                }
            }
        }


        bfs_result = residual_network.bfs1(start, finish);
        cp = bfs_result.first;
        path = bfs_result.second;
        c = getFlow(start);
    }


    c = getFlow(start);
    return c;

    //como extrair o encaminhamento?

}


pair<vector<int>,int> Graph::dijkstra_maximize_flow(int start, int finish){
    int pai[n+1], flow[n+1];
    MaxHeap<int, int> q(n+1, -1);

    vector<int> path;

    flow[start] = UINT16_MAX;
    int last=finish, cur=0, min=flow[start], count=0;


    for(int i=1; i<n+1; i++){
        pai[i] = -1;
        if(i!=start) flow[i] = 0;
        q.insert(i, flow[i]);
    }

    while(q.getSize()!=0){
        pair<int, int> v = q.removeMax();
        int failsafe = nodes[v.first].adj.size();
        for(Edge edge: nodes[v.first].adj){
            if(failsafe==0){break;}
            if(std::min(v.second, edge.flow) > flow[edge.dest]){
                flow[edge.dest] = std::min(v.second, edge.flow);
                pai[edge.dest] = v.first;
                q.increaseKey(edge.dest, flow[edge.dest]);
            }
            failsafe--;
        }
    }


    while(last != start){
        path.insert(path.begin(), last);
        cur = pai[last];
        if(cur == -1){path.clear(); return make_pair(path, -1);}
        if(flow[cur] < min) {min = flow[cur];}
        last = cur;
    }

    path.insert(path.begin(), start);

    for(int i=0; i<path.size()-1; i++){
        getEdge(path[i], path[i+1])->flow -= min;
    }

    return make_pair(path, min);
}

Graph Graph::extractPath(int start, int finish, int flowObjective, vector<pair<vector<int>,int>>& individualPaths, Graph& residual_network){
    Graph answer(n, true);

    int c = edmonds_karp_2(start, finish, flowObjective, residual_network);
    pair<vector<int>,int> func = dijkstra_maximize_flow(start, finish);
    vector<int> path = func.first;
    int flow = func.second;

    while(flow != -1 && (flow <= flowObjective || flowObjective > 0)){

        if((flowObjective - flow)<0){individualPaths.emplace_back(path,flow - flowObjective);}
        else individualPaths.emplace_back(path,flow);
        for(int i=0; i<path.size()-1; i++){
            Edge e = *getEdge(path[i], path[i+1]);
            answer.addEdge(e.src, e.dest,e.capacity, e.duration);
        }

        if(flow == flowObjective){break;}

        flowObjective-=flow;
        c = edmonds_karp_2(start, finish, flowObjective, residual_network);

        func = dijkstra_maximize_flow(start, finish);
        path = func.first;
        flow = func.second;
    }

    return answer;

}

