//
// Created by Matilde on 28/03/2022.
//

#ifndef PROJETO1_FILEHANDLER_H
#define PROJETO1_FILEHANDLER_H

#include "string"
#include "Estafeta.h"
#include "Encomenda.h"
#include "map"



class FileHandler {

public:
    /** @brief
     * Lê os dados do ficheiro carrinhas.txt, para criar o dataset
     */
    std::map<int, Estafeta> readCarrinhas(); //inicializar o armazem com isto
    /** @brief
     * Lê os dados do ficheiro encomendas.txt, para criar o dataset e objetos do tipo Encomenda
     */
    std::map<int, Encomenda> readEncomendas(); //como é que eu distingo uma entrega expresso de uma normal
    void split_str( std::string const &str, char delim, std::string (&words)[4]);
    /** @brief
     * Lê os dados do ficheiro carrinhas.txt, para criar o dataset e objetos do tipo Expresso
     */
    std::map<int, Expresso> readExpresso();
};


#endif //PROJETO1_FILEHANDLER_H
