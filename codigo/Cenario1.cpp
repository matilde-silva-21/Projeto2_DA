//
// Created by Matilde on 23/05/2022.
//

#include "Cenario1.h"



void Cenario1::cenario1_1(Graph &g, int start, int finish) {

    std::cout<<"\n---------------------CENARIO 1 ALINEA 1---------------------\n\n";
    pair<vector<int>,int> k = g.dijkstra_maximize_capacity(start, finish);

    std::cout<<"Path that maximizes capacity: (";

    for(int i=0; i<k.first.size(); i++){
        std::cout << k.first[i];
        if(i!=k.first.size()-1){std::cout<<",";}
    }
    std::cout<<")\nCapacity: "<<k.second<<" Edges: "<<k.first.size()<< "\n\n";

}

void Cenario1::cenario1_2(Graph &g,int start, int finish) {

    std::cout<<"\n---------------------CENARIO 1 ALINEA 2---------------------\n\n";

    pair<vector<int>,int> j = g.dijkstra_minimize_edges(start,finish);
    pair<vector<int>,int> k = g.dijkstra_maximize_capacity(start, finish);

    if(std::equal(j.first.begin(),j.first.end(), k.first.begin())) {
        std::cout << "Path that both maximizes capacity and minimizes edges: (";
    }

    else {
        std::cout<<"Path that maximizes capacity: (";

        for(int i=0; i<k.first.size(); i++){
            std::cout << k.first[i];
            if(i!=k.first.size()-1){std::cout<<",";}
        }
        std::cout<<")\nCapacity: "<<k.second<<" Edges: "<<k.first.size()<< "\n\n";

        std::cout << "Path that minimizes edges: (";
    }

    for (int i = 0; i < j.first.size(); i++) {
        std::cout << j.first[i];
        if (i != j.first.size() - 1) { std::cout << ","; }
    }

    std::cout << ")\nCapacity: " << j.second << " Edges: " << j.first.size()<< "\n\n";
}
