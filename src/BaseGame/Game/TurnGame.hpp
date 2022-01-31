#ifndef _TURNGAME_
#define _TURNGAME_

#include "./../Components/GameComponent.hpp"
#include "./../Components/Card.hpp"
 
class TurnGame {
    public:
        TurnGame(GameComponent g) : component(std::make_shared<GameComponent> (g)){};

        virtual void initComponent() {};
        
        virtual void turnLoop(std::shared_ptr<PlayerControl> p){};

        virtual bool isEnd() {return true;}

        virtual void endOfTurn(){}

        virtual void endOfLoop(){}

        virtual void start();
    
    protected:
        std::shared_ptr<GameComponent> component;
};
#endif