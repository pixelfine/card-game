#ifndef _PUTFRONT_
#define _PUTFRONT_

#include "Action.hpp"
#include "./../Components/GameComponent.hpp"

class PutFront :public Action{
    public:
        PutFront(std::string desc, int h) : Action(desc, h){};
        
        void action(std::shared_ptr<Player> p, std::shared_ptr<GameComponent> c) override{
            p->addFront( p->removeHand(hand));
        }
};
#endif