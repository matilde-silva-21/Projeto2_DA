#include <iostream>
#include "FileHandler.h"
#include "graph.h"

int main() {

    FileHandler f1;
    std::string file("../tests/in01_b.txt");
    Graph g = f1.readTrips(file);

    std::cout << "Graph created succesfully" << std::endl;

    std::cout << "solucao: " << g.dijkstra(1, 4) << std::endl;

    return 0;
}
