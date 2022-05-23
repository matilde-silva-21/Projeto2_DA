#include <iostream>
#include "FileHandler.h"
#include "graph.h"
#include "Cenario1.h"

int main() {

    FileHandler f1;
    std::string file("../tests/in00_b.txt");
    Graph g = f1.readTrips(file);

    Cenario1::cenario1_1(g,1,4);
    Cenario1::cenario1_2(g, 1, 4);


    return 0;
}
