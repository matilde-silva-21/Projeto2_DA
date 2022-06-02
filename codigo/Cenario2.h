//
// Created by Matilde on 02/06/2022.
//

#ifndef PROJETO2_CENARIO2_H
#define PROJETO2_CENARIO2_H

#include <iostream>
#include "graph.h"

class Cenario2 {

public:
    /*podia meter o cenario 2 e 3 a chamar os outros primeiro para evitar user error*/
    static Graph cenario2_1(Graph &g,int start, int finish, int groupDimension);
    static void cenario2_2(Graph &g,int start, int finish, int groupDimension, int value);
    static void cenario2_3(Graph &g, int start, int finish);
};


#endif //PROJETO2_CENARIO2_H
