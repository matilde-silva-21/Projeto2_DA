#include <iostream>
#include "FileHandler.h"
#include "graph.h"
#include "Cenario1.h"
#include "Cenario2.h"

void menu(){
    int dataset, start, end, scenario, sub_problem, group_size, value;
    std::string file, choice;

    while(true) {
        std::cout << "\nPlease choose the dataset (0-10): ";
        std::cin >> choice;
        dataset = stoi(choice);
        if (dataset > 10 || dataset < 0) {
            std::cout << "\nInput not valid.";
            continue;
        }

        if (dataset != 10) {
            file = "../tests/in0" + to_string(dataset) + "_b.txt";
        } else {
            file = "../tests/in" + to_string(dataset) + "_b.txt";
        }
        break;

    }

    FileHandler f1;
    Graph g = f1.readTrips(file);

    while(true) {
        std::cout << "\nPlease choose your start point (1-" << g.getN() << "): ";
        std::cin >> choice;

        start = stoi(choice);

        if (start < 1 || start > g.getN()) {
            std::cout << "\nInput not valid.";
            continue;
        }
        break;
    }
    while (true){
        std::cout << "\nPlease choose your end point (1-" << g.getN() << "): ";
        std::cin >> choice;

        end = stoi(choice);

        if (end < 1 || end > g.getN()) {
            std::cout << "\nInput not valid.";
            continue;
        }
        break;
    }

    while (true){
        std::cout << "\nPlease choose your scenario (1 or 2): ";
        std::cin >> choice;
        scenario = stoi(choice);
        if(scenario!= 1 && scenario!=2){
            std::cout << "\nInput not valid.";
            continue;
        }
        break;
    }

    while (true){
        if(scenario == 1){
            std::cout << "\nPlease choose your sub-problem (1 or 2): ";
            std::cin >> choice;
            sub_problem = stoi(choice);
            if(sub_problem!= 1 && sub_problem!=2){
                std::cout << "\nInput not valid.";
                continue;
            }
            break;
        }

        else {
            std::cout << "\nPlease choose your sub-problem (1-5): ";
            std::cin >> choice;
            sub_problem = stoi(choice);
            if (sub_problem < 1 || sub_problem > 5) {
                std::cout << "\nInput not valid.";
                continue;
            }
            break;
        }

    }

    if((sub_problem == 1 || sub_problem == 2) && scenario == 2){
        std::cout << "\nPlease enter your group's size: ";
        std::cin >> choice;
        group_size = stoi(choice);
        if(sub_problem == 2){
            std::cout << "\nPlease enter the extra value: ";
            std::cin >> choice;
            value = stoi(choice);
        }
    }

    if(scenario == 1){
        if (sub_problem == 1){
            Cenario1::cenario1_1(g,start,end);
        }
        else {
            Cenario1::cenario1_2(g,start,end);
        }
    }

    else{
        if (sub_problem == 1){
            Cenario2::cenario2_1(g,start,end,group_size);
        }
        else if(sub_problem==2){
            Cenario2::cenario2_2(g,start,end,group_size,value);
        }
        else if(sub_problem==3){
            Cenario2::cenario2_3(g,start,end);
        }
        else if(sub_problem==4){
            Cenario2::cenario2_4(g,start,end);
        }
        else if(sub_problem==5){
            Cenario2::cenario2_5(g);
        }
    }


}
int main() {

    //s-1 A-2 B-3 C-4 D-5 t-6
    Graph pp1(6,true);
    pp1.addEdge(1,2, 6, 0);
    pp1.addEdge(1,4, 3,0);
    pp1.addEdge(2,3,3,0);
    pp1.addEdge(2, 4, 3,0);
    pp1.addEdge(4,3,3,0);
    pp1.addEdge(4,5,3,0);
    pp1.addEdge(3,6,5,0);
    pp1.addEdge(5, 3, 1, 0);
    pp1.addEdge(5,6,3,0);




    menu();


    return 0;
}
