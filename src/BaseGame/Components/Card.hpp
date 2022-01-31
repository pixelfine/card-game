#ifndef _CARD_
#define _CARD_
#include "./Component.hpp"

class Card : public Component{
    public: 
        virtual int getValue() {    return 0;   };

        virtual int compare(Card &c){
            return this->getValue()-c.getValue();
        }

        virtual int getV()              {return 0;}
        virtual std::string getF()      {return "";}
        
        virtual std::string toString()  {return "["+std::to_string(getV())+","+getF()+"]";}

    protected:
        Card() : Component("Card"), hidden(false) {}
    private : 
        bool hidden;
};

#endif


/*
#ifndef _VALUEDCARD_
#define _VALUEDCARD_

#include "Card.hpp"

class ValuedCard : public Card {
    public: 
        virtual int getValue() = 0;

        int compare(ValuedCard &c){
            return this->getValue()-c.getValue();
        }

    protected:
        ValuedCard() : Card(){}
};

#endif
*/