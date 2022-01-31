#ifndef _COMPONENT_
#define _COMPONENT_

#include "Factory.hpp"

class Component{
    public :
        int getId(){    return id;  };


        int hash(){
            int h1 = std::hash<std::string>{}(typeid(Component).name());
            int h2 = std::hash<std::string>{}(std::to_string(id));
            int res = (h1^(h2<<1));
            if(res>0) return res;
            return res*-1;
        }
        
    protected: 
        Component(std::string code):id(Factory::makeId(code)){};

    private:
        int id;
};

#endif