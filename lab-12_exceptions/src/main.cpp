#include <iostream>

#include <Matrix.hpp>


Matrix matrixes[10];

void load(std::string index){
    std::string file;
    std::cin >> file;
    std::ifstream in(file);
    in >> matrixes[index[1] - '0'];
    in.close();
}

void add(std::string firstIndex){
    std::string secondIndex;
    std::cin >> secondIndex;
    matrixes[firstIndex[1] - '0'] += matrixes[secondIndex[1] - '0'];
}

void mult(std::string firstIndex){
    std::string secondIndex;
    std::cin >> secondIndex;
    matrixes[firstIndex[1] - '0'] *= matrixes[secondIndex[1] - '0'];
}

void elem(std::string index){
    int i, j;
    std::cin >> i >> j;
    std::cout << matrixes[index[1] - '0'].get(i, j);
}

void print(std::string index){
    std::cout << matrixes[index[1] - '0'];
}

int main() {
    std::string action, firstParam;
    while (true) {
        try {
            std::cin >> action;
            if(action == "exit"){
                break;
            } else {
                std::cin >> firstParam;
                if(action == "load"){
                    load(firstParam);
                } else if(action == "add"){
                    add(firstParam);
                } else if(action == "mul"){
                    mult(firstParam);
                } else if(action == "elem"){
                    elem(firstParam);
                } else if(action == "print"){
                    print(firstParam);
                }
            }
        } catch (MatrixException &e) {
            std::cout << e.what() << std::endl;
        }
    }
}