//
// Created by Matilde on 28/03/2022.
//

#include "FileHandler.h"
#include "fstream"
#include "sstream"
#include "string"
#include "iostream"


Graph FileHandler::readTrips(std::string filename) {
    std::string sizes[4];
    std::string words[4];
    std::string line;
    std::ifstream file(filename);
    if(file.is_open()){
        getline (file, line); //primeira linha contem o numero de nos e arestas;
        split_str(line, ' ', sizes);
        Graph g(std::stoi(sizes[0]), true);
        while(getline (file, line)){
            split_str(line, ' ', words);
            g.addEdge(std::stoi(words[0]), std::stoi(words[1]),  std::stoi(words[2]), std::stoi(words[3]));
        }
        file.close();
        return g;
    }
    else{std::cout << "Can't open test file!\n";}

    return Graph(0, true);
}

void FileHandler::split_str( std::string const &str, const char delim, std::string (&words)[4])
{
    // create a stream from the string
    std::stringstream s(str);
    int count = 0;
    std::string s2;
    while (std:: getline (s, s2, delim))
    {
        words[count] = s2; // store the string in s2
        count++;
    }
}
