#ifndef _FACTORY_
#define _FACTORY_
#include <unordered_map>
#include <memory>

#include <iostream>

class Factory{
    public:
        static int getLastId(std::string code);
        static int makeId(std::string code);
        
    private:
        static std::unordered_map<std::string, int> id_map;
};

#endif