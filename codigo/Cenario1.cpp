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
    std::cout<<")\nCapacity: "<<k.second<<" Transhipments: "<<k.first.size()-2<< "\n\n";

}

void Cenario1::cenario1_2(Graph &g,int start, int finish) {

    std::cout<<"\n---------------------CENARIO 1 ALINEA 2---------------------\n\n";

    std::cout << "Paret-Optimal path(s): \n\n";
    vector<int> curPath;
    vector<vector<int>> allPaths, paretOpt;
    float curBestRatio=0.0;
    bool empty = true;
    g.allPossiblePaths(start, finish, curPath, allPaths, empty);

    for(auto l: allPaths){
        float ratio = ((float)(g.getPathCap(l)))/((float)(l.size() - 1));
        if(roundf(ratio) > roundf(curBestRatio)){
            curBestRatio = ratio;
            paretOpt.clear();
            paretOpt.push_back(l);
        }
        else if(ratio == curBestRatio){
            paretOpt.push_back(l);
        }
    }

    for(int k=0; k<paretOpt.size(); k++){
        std::cout << "\nPath "<<k+1<<": (";
        for (int i = 0; i < paretOpt[k].size(); i++) {
            std::cout << paretOpt[k][i];
            if (i != paretOpt[k].size() - 1) { std::cout << ","; }
        }
        std::cout << ")\nCapacity: "<<g.getPathCap(paretOpt[k])<<" Transhipments: "<<paretOpt[k].size()-2<<"\n";
    }

}
