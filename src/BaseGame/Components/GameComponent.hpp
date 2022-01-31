#ifndef _GAMECOMPONENT_
#define _GAMECOMPONENT_

#include <vector>
#include <stack>
#include "./../Controllers/PlayerControl.hpp"
#include <memory>

class GameComponent : public Component{
    public:
        GameComponent() : Component("Game"), turnManager(std::vector<std::shared_ptr<PlayerControl>>()), deck(std::vector<std::shared_ptr<Card>>()){}

        std::vector<std::shared_ptr<PlayerControl>>& getTurnManager() {   return turnManager; }
        std::vector<std::shared_ptr<Card>>& getDeck()          {   return deck;        }

        virtual std::string toString(){
            std::string res = "GameDeck :";
            for(auto c : deck){
                res+=c->toString();
            }res+="\n";
            for(auto p : turnManager){
                res+= "Player : "+std::to_string(p->player->getId())+"\t Hand :"+ std::to_string(p->player->getHand().size())+ "\tDeck :"+std::to_string(p->player->getDeck().size()) +"\tFront :";
                for(auto c: p->player->getFront()){
                    res+=c->toString();
                }res+="\n";
            }
            return res;
        }

    private:
        std::vector<std::shared_ptr<PlayerControl>> turnManager;
        std::vector<std::shared_ptr<Card>> deck;
};

#endif