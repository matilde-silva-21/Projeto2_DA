//
// Created by Matilde on 02/06/2022.
//

#include "Cenario2.h"

Graph Cenario2::cenario2_1(Graph g, int start, int finish, int groupDimension) {

    std::cout<<"\n---------------------SCENARIO 2 SUB-PROBLEM 1---------------------\n";

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


void Cenario2::cenario2_2(Graph g, int start, int finish, int groupDimension, int value) {

    std::cout<<"\n---------------------SCENARIO 2 SUB-PROBLEM 2---------------------\n";

    vector<pair<vector<int>,int>> paths;
    Graph residual_network = g;
    if(residual_network.edmonds_karp(start,finish) < (value+groupDimension)){
        std::cout << "\nLooks like you have a lot of friends!\nToo many to make this trip unfortunately, there are no paths that fit all of you :(\n";
        return;
    }
    residual_network = g;


    /*chamar o cenario 2.1*/
    Graph graph = g.extractPath(start,finish,groupDimension, paths, residual_network);

    paths.clear();

    /*chamar o cenario 2.2*/
    graph = g.extractPath(start,finish,value+groupDimension, paths, residual_network);


    for(int k=0; k<paths.size(); k++){
        std::cout << "\nPath "<<k+1<<": (";
        for (int i = 0; i < paths[k].first.size(); i++) {
            std::cout << paths[k].first[i];
            if (i != paths[k].first.size() - 1) { std::cout << ","; }
        }
        std::cout << ")\nNumber of people on this path: "<<paths[k].second<<" Transhipments: "<<paths[k].first.size()-2<<"\n";
    }

}

void Cenario2::cenario2_3(Graph g, int start, int finish) {
    /*constroi o caminho do 0, nao usa a residual network de outro*/

    std::cout<<"\n---------------------SCENARIO 2 SUB-PROBLEM 3---------------------\n";

    vector<pair<vector<int>,int>> paths;
    Graph residual_network = g;
    int maxflow = residual_network.edmonds_karp(start,finish);
    residual_network = g;


    std::cout << "\nMaximum number of people to make this trip: "<<maxflow<<"\n\n";

    Graph graph = g.extractPath(start,finish,maxflow, paths, residual_network);


    for(int k=0; k<paths.size(); k++){
        std::cout << "\nPath "<<k+1<<": (";
        for (int i = 0; i < paths[k].first.size(); i++) {
            std::cout << paths[k].first[i];
            if (i != paths[k].first.size() - 1) { std::cout << ","; }
        }
        std::cout << ")\nNumber of people on this path: "<<paths[k].second<<" Transhipments: "<<paths[k].first.size()-2<<"\n";
    }

}

void Cenario2::cenario2_4(Graph g, int start, int finish) {
    std::cout<<"\n---------------------CENARIO 2 ALINEA 4---------------------\n\n";
    pair<vector<int>,int> k = g.earliest_start(start, finish);

    std::cout<<"Path that the group took: (";

    for(int i=0; i<k.first.size(); i++){
        std::cout << k.first[i];
        if(i!=k.first.size()-1){std::cout<<",";}
    }
    std::cout<<")\nMinimum Time required for the group to reunite: "<<k.second<<" Transhipments: "<<k.first.size()-2<< "\n\n";
}
