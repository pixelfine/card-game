#include "TurnGame.hpp"
#include <iostream>

void TurnGame::start(){
    initComponent();
    std::cout<<"Nb joueur : "<< component->getTurnManager().size()<<"\n";
    for(size_t i=0;i<component->getTurnManager().size(); i++){
        std::cout<<"Player "<<component->getTurnManager()[i]->player->getId()<<"\n";
    }
    while(!isEnd()){
        for(size_t i=0; i<component->getTurnManager().size(); i++){
            if(isEnd()) break;
            turnLoop(component->getTurnManager()[i]);
        }
        endOfTurn();
    }
    endOfLoop();
    
}
