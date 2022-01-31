#ifndef _ACTION_
#define _ACTION_
#include <memory>

class Player;
class GameComponent;

class Action {
    public:
        Action(std::string desc, int h) : description(desc), hand(h){};
        Action(std::string desc)        : description(desc), hand(0){};

        virtual void action(std::shared_ptr<Player> p, std::shared_ptr<GameComponent> c=0) = 0;
        virtual const std::string getDescription(){   return description;   }
        
    protected:
        const std::string description;
        int hand;
};
#endif