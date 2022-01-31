#ifndef _PUTGAMEDECk_
#define _PUTGAMEDECk_

#include "Action.hpp"
#include "./../Components/GameComponent.hpp"

class PutGameDeck :public Action{
    public:
        PutGameDeck(std::string desc, int i) : Action(desc, i){};
        
        void action(std::shared_ptr<Player> p, std::shared_ptr<GameComponent> c) override{
            c->getDeck().push_back( p->removeHand(hand) );
        }
};
#endif