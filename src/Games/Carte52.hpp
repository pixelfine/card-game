#ifndef _CARTE52_
#define _CARTE52_

#include "./../BaseGame/Components/Card.hpp"

class Carte52 : public Card {
    public: 
        std::string forme;
        int valeur;
        Carte52(std::string f, int v): Card(), forme(f), valeur(v) {}

        int getValue(){
            return valeur;
        }
        int getV() override{
            return valeur;
        }
        std::string getF() override{
            return forme;
        }
};

#endif