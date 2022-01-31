#include "Input.hpp"
#include <iostream>
#include <limits>
#include <algorithm>


bool Input::isNum(std::string out){
    return !out.empty() && std::find_if(
        out.begin(), out.end(), [](unsigned char c){
            return !std::isdigit(c);
        }
    ) == out.end();
}


int Input::numericIn(std::string out) {
    std::cout<<out;
    std::string tmp;

    std::cin>>tmp;
    if(!Input::isNum(tmp)){
        std::cin.clear();
        return Input::numericIn(out);
    }else{
        return std::stoi(tmp);
    }
}
