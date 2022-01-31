#ifndef _PIOCHE_
#define _PIOCHE_

#include "Action.hpp"
#include "./../Components/GameComponent.hpp"

class Pass :public Action{
    public:
        Pass(std::string desc) : Action(desc){};
        
        void action(std::shared_ptr<Player> p, std::shared_ptr<GameComponent> c) override{}
};
#endif