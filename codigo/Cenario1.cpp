//
// Created by Matilde on 23/05/2022.
//

#include "Cenario1.h"



void Cenario1::cenario1_1(Graph &g, int start, int finish) {

    std::cout<<"\n---------------------SCENARIO 1 SUB-PROBLEM 1---------------------\n\n";
    pair<vector<int>,int> k = g.dijkstra_maximize_capacity(start, finish);

    std::cout<<"Path that maximizes capacity: (";

    for(int i=0; i<k.first.size(); i++){
        std::cout << k.first[i];
        if(i!=k.first.size()-1){std::cout<<",";}
    }
    std::cout<<")\nCapacity: "<<k.second<<" Transhipments: "<<k.first.size()-2<< "\n\n";

}

void Cenario1::cenario1_2(Graph &g,int start, int finish) {

    std::cout<<"\n---------------------SCENARIO 1 SUB-PROBLEM 2---------------------\n\n";

    std::cout << "Paret-Optimal path(s): \n\n";
    int edgeBound = g.dijkstra_maximize_capacity(start, finish).first.size(), count = 0;
    int capBound = g.bfs1(1, 50).first;


    vector<pair<int, vector<vector<int>>>> allPaths = g.allPossiblePaths(start, finish, edgeBound, capBound, 20);
    //vector<vector<int>> allPaths = g.allPossiblePaths(start, finish, edgeBound, capBound);

    for(auto& pair: allPaths){
        for(auto& path: pair.second){
            std::cout << "\nPath "<<++count<<": (";
            for(int i=0; i<path.size(); i++){
                std::cout << path[i];
                if(i!=path.size()-1){std::cout<<", ";}
            }
            std::cout << ")\nCapacity: "<< pair.first<<" Transhipments: "<< path.size()-2<<"\n";
        }

    }

    /*for(auto& path: allPaths){
        std::cout << "\nPath "<<++count<<": (";
        for(int i=0; i<path.size(); i++){
            std::cout << path[i];
            if(i!=path.size()-1){std::cout<<", ";}
        }
        std::cout << ")\nCapacity: "<< g.getPathCap(path)<<" Transhipments: "<< path.size()-2<<"\n";
    }*/

    return;

    //adicionar condicional, caso so haja um path (dataset pequeno) mandar o maximize_cap e minimize edges?
}
