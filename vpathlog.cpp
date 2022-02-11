
#include "vpathlog.h"
#include <iostream>

void vpathlog::print(std::string data,bool addNewLine){
    std::cout << data;
    if(addNewLine){
        std::cout << std::endl;
    }
}