#include "./Factory.hpp"

std::unordered_map<std::string, int> Factory::id_map = {};

int Factory::getLastId(std::string code) {
    auto id = Factory::id_map.find(code);
    if(id==id_map.end()){
        return -1;
    }else{
        return id->second;
    }
}

int Factory::makeId(std::string code) {
    auto id = Factory::id_map.find(code);
    if(id==id_map.end()){
        id_map[code]=0;
        return 0;
    }else{
        id_map[code]+=1;
        return id->second;
    }
}


