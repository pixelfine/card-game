#ifndef _CARTET_
#define _CARTET_

#include "./../BaseGame/Components/Card.hpp"

class CarteT : public Card {
    public: 
        std::string forme;
        int valeur;
        CarteT(std::string f, int v): forme(f), valeur(v) {}

        int getValue(){
            if((valeur==1 && forme.at(0)=='*')||( valeur==21 && forme.at(0)=='*')||(valeur==14)) return 9;
            if(valeur == 13) return 7;
            if(valeur == 12) return 5;
            if(valeur == 11) return 3;
            return 1;
        }

        int getV() override {
            return valeur;
        }
        
        std::string getF() override {
            return forme;
        }

        int compare(Card &c) override{
            if(this->getF().at(0)=='*' && c.getF().at(0)!='*'){
                return 1;
            }else if(this->getF().at(0)!='*' && c.getF().at(0)=='*'){
                return -1;
            }else{
                return this->getV()-c.getV();
            }
        }
};

#endif