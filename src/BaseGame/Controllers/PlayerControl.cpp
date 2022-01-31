#include "PlayerControl.hpp"
#include "./../Input.hpp"
#include <random>

#include "./../Components/GameComponent.hpp"

int PlayerControl::choose(){
    int n =-1;
    if(player->getAi()>=0){
        n = rand()%choiceList.size();
    }else{
        for(size_t i=0; i<choiceList.size(); i++){
            std::cout<<i<<" : "<<choiceList[i]->getDescription()<<"\n";
        }
        while(!(n>=0 && ((size_t)n)<choiceList.size())){
            n = Input::numericIn("Select a displayed number:");
        }
    }return n;
}

int PlayerControl::chooseRange(int start, int end, std::string desc){
    int n =-1;
    if(player->getAi()>=0){
        n = start + (rand()%(end+1));
    }else{
        std::cout<<desc<<"\n";
        while(!(n>=start && n<=end)){
            n = Input::numericIn("Select a displayed number:");
        }
    }return n;
}

void PlayerControl::play(int i, std::shared_ptr<GameComponent> game){
    this->choiceList[i]->action(player, game);
    emptyAction();
}

void PlayerControl::use(Action_ptr action){
    action->action(player, game);
}

void PlayerControl::addAction(Action_ptr a){
    choiceList.push_back(a);
}

void PlayerControl::emptyAction(){
    choiceList.clear();
}