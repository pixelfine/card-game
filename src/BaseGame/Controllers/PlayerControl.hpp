#ifndef _PLAYERCONTROL_
#define _PLAYERCONTROL_

#include <vector>
#include <iostream>

#include "Action.hpp"
#include <memory>
#include "./../Components/Player.hpp"


typedef std::shared_ptr<Action> Action_ptr;

class PlayerControl {
    public:
        std::shared_ptr<Player> player;
        std::vector<Action_ptr> choiceList;
        PlayerControl(std::shared_ptr<Player> p, std::shared_ptr<GameComponent> g) : player(p), game(g){
            choiceList=std::vector<Action_ptr>();
        };

        int choose();
        int chooseRange(int start, int end, std::string desc);
        void play(int i, std::shared_ptr<GameComponent> game);
        void use(Action_ptr action);

        void addAction(Action_ptr a);
        void emptyAction();


    private :
        std::shared_ptr<GameComponent> game;
};

#endif