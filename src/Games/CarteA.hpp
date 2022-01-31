#ifndef _CARTEA_
#define _CARTEA_

#include "./../BaseGame/Components/Card.hpp"

class CarteA : public Card {
    public: 
        std::string forme;
        int valeur;
        CarteA(std::string f, int v): forme(f), valeur(v) {}

        int getValue(){
            if(valeur == 12 || valeur == 13) return 10;
            else if(valeur == 1 || valeur == 8) return 20;
            else if(valeur == 8) return 50;
            else return valeur;
        }
        int getV() override {
            return valeur;
        }
        std::string getF() override {
            return forme;
        }
};

#endif