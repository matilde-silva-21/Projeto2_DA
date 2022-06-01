#include <iostream>
#include "FileHandler.h"
#include "graph.h"
#include "Cenario1.h"

int main() {

    FileHandler f1;
    std::string file("../tests/in01_b.txt");
    Graph g = f1.readTrips(file);

    //s-1 A-2 B-3 C-4 D-5 t-6
    /*Graph pp1(6,true);
    pp1.addEdge(1,2, 6, 0);
    pp1.addEdge(1,4, 3,0);
    pp1.addEdge(2,3,3,0);
    pp1.addEdge(2, 4, 3,0);
    pp1.addEdge(4,3,3,0);
    pp1.addEdge(4,5,3,0);
    pp1.addEdge(3,6,5,0);
    pp1.addEdge(5, 3, 1, 0);
    pp1.addEdge(5,6,3,0);


    cout << "edmonds-karp: "<<pp1.edmonds_karp(1,6)<<endl;*/
    Cenario1::cenario1_1(g,1,50);
    Cenario1::cenario1_2(g, 1, 50);


    return 0;
}
