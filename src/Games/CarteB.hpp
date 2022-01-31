#ifndef _CARTEB_
#define _CARTEB_

#include "./../BaseGame/Components/Card.hpp"

class CarteB : public Card {
    //Valet == 11; Dame == 12; Roi == 13
    public: 
        std::string forme;
        int valeur;
        CarteB(std::string f, int v): forme(f), valeur(v) {}

        //sans atout
        int getValue(){
            switch(valeur){
                case 1 : return 11;
                case 10: return 10;
                case 13: return 4 ;
                case 12: return 3 ;
                case 11: return 2;
                default: return 0;
            }
        }

        int getV() override {
            return valeur;
        }
        
        std::string getF() override {
            return forme;
        }
        std::string toString() override {
            switch(valeur){
                case 11: return "[V,"+getF()+"]";
                case 12: return "[D,"+getF()+"]";
                case 13: return "[R,"+getF()+"]";
                default: return "["+std::to_string(getV())+","+getF()+"]";
            }
        }
};

#endif