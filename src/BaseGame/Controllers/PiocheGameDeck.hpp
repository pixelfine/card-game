#ifndef _PIOCHEGAMEDECK_
#define _PIOCHEGAMEDECK_

#include "Action.hpp"
#include "./../Components/GameComponent.hpp"

class PiocheGameDeck :public Action{
    public:
        PiocheGameDeck(std::string desc) : Action(desc){};
        
        void action(std::shared_ptr<Player> p, std::shared_ptr<GameComponent> c) override{
            p->addHand(c->getDeck().back());
            c->getDeck().pop_back();
        }
};
#endif