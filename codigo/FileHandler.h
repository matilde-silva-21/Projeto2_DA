//
// Created by Matilde on 28/03/2022.
//

#ifndef PROJETO1_FILEHANDLER_H
#define PROJETO1_FILEHANDLER_H

#include "string"
#include "fstream"
#include "graph.h"
#include "map"



class FileHandler {

public:
    /** @brief
     * Lê os dados do ficheiro passado em file, para criar o grafo
     */
    Graph readTrips(std::string filename);

    void split_str( std::string const &str, char delim, std::string (&words)[4]);
};


#endif //PROJETO1_FILEHANDLER_H
