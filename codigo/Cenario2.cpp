//
// Created by Matilde on 02/06/2022.
//

#include "Cenario2.h"

Graph Cenario2::cenario2_1(Graph &g, int start, int finish, int groupDimension) {

    std::cout<<"\n---------------------CENARIO 2 ALINEA 1---------------------\n";

    vector<pair<vector<int>,int>> paths;
    Graph residual_network = g;
    if(residual_network.edmonds_karp(start,finish) < groupDimension){
        std::cout << "\nLooks like you have a lot of friends!\nToo many to make this trip unfortunately, there are no paths that fit all of you :(\n";
        return g;
    }
    residual_network = g;

    Graph graph = g.extractPath(start,finish,groupDimension, paths, residual_network);
    for(int k=0; k<paths.size(); k++){
        std::cout << "\nPath "<<k+1<<": (";
        for (int i = 0; i < paths[k].first.size(); i++) {
            std::cout << paths[k].first[i];
            if (i != paths[k].first.size() - 1) { std::cout << ","; }
        }
        std::cout << ")\nNumber of people on this path: "<<paths[k].second<<" Transhipments: "<<paths[k].first.size()-2<<"\n";
    }

    return residual_network;

}


void Cenario2::cenario2_2(Graph &g, int start, int finish, int groupDimension, int value, Graph& residual_network) {

    std::cout<<"\n---------------------CENARIO 2 ALINEA 2---------------------\n";

    vector<pair<vector<int>,int>> paths;
    Graph copy = g;
    if(copy.edmonds_karp(start,finish) < (value+groupDimension)){
        std::cout << "\nLooks like you have a lot of friends!\nToo many to make this trip unfortunately, there are no paths that fit all of you :(\n";
        return;
    }

    Graph graph = g.extractPath(start,finish,value+groupDimension, paths, residual_network);

    //failsafe, se por acaso a iteraçao anterior tiver maximizado o grafo, a rede residual nao sera valida
    if(paths.empty()){
        copy = g;
        graph = g.extractPath(start,finish,value+groupDimension, paths, copy);
    }

    for(int k=0; k<paths.size(); k++){
        std::cout << "\nPath "<<k+1<<": (";
        for (int i = 0; i < paths[k].first.size(); i++) {
            std::cout << paths[k].first[i];
            if (i != paths[k].first.size() - 1) { std::cout << ","; }
        }
        std::cout << ")\nNumber of people on this path: "<<paths[k].second<<" Transhipments: "<<paths[k].first.size()-2<<"\n";
    }

}

void Cenario2::cenario2_3(Graph &g, int start, int finish, Graph& residual_network) {

    std::cout<<"\n---------------------CENARIO 2 ALINEA 3---------------------\n";

    vector<pair<vector<int>,int>> paths;
    Graph copy = g;
    int maxflow = copy.edmonds_karp(start,finish);

    std::cout << "\nMaximum number of people to make this trip: "<<maxflow<<"\n\n";

    Graph graph = g.extractPath(start,finish,maxflow, paths, residual_network);
    //failsafe, se por acaso a iteraçao anterior tiver maximizado o grafo, a rede residual nao sera valida
    if(paths.empty()){
        copy = g;
        graph = g.extractPath(start,finish,maxflow, paths, copy);
    }

    for(int k=0; k<paths.size(); k++){
        std::cout << "\nPath "<<k+1<<": (";
        for (int i = 0; i < paths[k].first.size(); i++) {
            std::cout << paths[k].first[i];
            if (i != paths[k].first.size() - 1) { std::cout << ","; }
        }
        std::cout << ")\nNumber of people on this path: "<<paths[k].second<<" Transhipments: "<<paths[k].first.size()-2<<"\n";
    }

}
