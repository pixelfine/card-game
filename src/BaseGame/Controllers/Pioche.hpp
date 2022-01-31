#ifndef _PIOCHE_
#define _PIOCHE_

#include "Action.hpp"
#include "./../Components/GameComponent.hpp"

class Pioche :public Action{
    public:
        Pioche(std::string desc) : Action(desc){};
        
        void action(std::shared_ptr<Player> p, std::shared_ptr<GameComponent> c) override{
            p->addHand(p->popDeck());
        }
};
#endif