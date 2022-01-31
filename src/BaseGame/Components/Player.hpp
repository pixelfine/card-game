#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <stack>
#include "Factory.hpp"
#include "Component.hpp"
#include "Card.hpp"
#include <memory>

class Player : public Component{
    public: 
        std::string state;
        Player(int _ai) : Component("Player"), hand(std::vector<std::shared_ptr<Card>>()), deck(std::stack<std::shared_ptr<Card>>()), front(std::vector<std::shared_ptr<Card>>()), ai(_ai){
            state="";
        }

        int getAi(){    return ai;  }


        void addHand(std::shared_ptr<Card> c);
        std::shared_ptr<Card> removeHand(int index);
        std::vector<std::shared_ptr<Card>>& getHand();

        void pushDeck(std::shared_ptr<Card> c);
        std::shared_ptr<Card> popDeck();
        std::stack<std::shared_ptr<Card>>&  getDeck();

        void addFront(std::shared_ptr<Card> c);
        std::shared_ptr<Card> removeFront(int index);
        std::vector<std::shared_ptr<Card>>& getFront();

        virtual std::string toString(){
            std::string res="Player :"+std::to_string(this->getId())+"\n\tDeck :"+std::to_string(deck.size())+"\n\tHand :";
            for(auto c : this->getHand()){
                res+= c->toString();
            }
            res+="\n\tFront :";
            for(auto c : this->getFront()){
                res+= c->toString();
            }res+="\n";
            return res;
        }

    protected:
        std::vector<std::shared_ptr<Card>> hand;
        std::stack<std::shared_ptr<Card>>  deck;
        std::vector<std::shared_ptr<Card>> front;
    private : 
        int ai;
};

#endif