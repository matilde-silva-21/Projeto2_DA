//
// Created by Matilde on 28/03/2022.
//

#include "FileHandler.h"
#include "fstream"
#include "sstream"
#include "string"
#include "iostream"
#include "Estafeta.h"

std::map<int, Estafeta> FileHandler::readCarrinhas() {
    std::map<int, Estafeta> estafetas;
    int count = 1;
    std::string words[4];
    std::string line;
    std::ifstream file("input/carrinhas.txt");
    if(file.is_open()){
        getline (file, line); //primeira linha é para descartar;
        while(getline (file, line)){
            std::string matricula = "XX-XX-XX";
            split_str(line, ' ', words);
            Estafeta e1(matricula, std::stoi(words[0]), std::stoi(words[1]), std::stoi(words[2]));
            estafetas.insert(estafetas.begin(), std::pair<int,Estafeta> (e1.getid(), e1));
        }
        file.close();
    }

    else{std::cout << "Can't open file!\n";}

    return estafetas;

}


std::map<int, Encomenda> FileHandler::readEncomendas() {
    std::string words[4];
    std::map<int, Encomenda> encomendas;
    std::string line;
    std::ifstream file("input/encomendas.txt");
    if(file.is_open()){
        getline (file, line); //primeira linha é para descartar;
        while(getline (file, line)){
            split_str(line, ' ', words);
            Encomenda e1(std::stoi(words[0]), std::stoi(words[1]), std::stoi(words[2]));
            encomendas.insert(encomendas.begin(), std::make_pair(e1.getid(), e1));
        }
        file.close();
    }

    else{std::cout << "Can't open file!\n";}

    return encomendas;
}

std::map<int, Expresso> FileHandler::readExpresso() {
    std::string words[4];
    std::map<int, Expresso> expresso;
    std::string line;
    std::ifstream file("input/encomendas.txt");
    if(file.is_open()){
        getline (file, line); //primeira linha é para descartar;
        while(getline (file, line)){
            split_str(line, ' ', words);
            Expresso e1(std::stoi(words[0]), std::stoi(words[1]), std::stoi(words[2]), std::stoi(words[3]));
            expresso.insert(expresso.begin(), std::make_pair(e1.getid(), e1));
        }
        file.close();
    }

    else{std::cout << "Can't open file!\n";}

    return expresso;
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
