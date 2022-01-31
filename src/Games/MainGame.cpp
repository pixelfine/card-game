#include "MainGame.hpp"
#include <algorithm>
#include <random>
#include "./../BaseGame/Controllers/PiocheGameDeck.hpp"
#include "./../BaseGame/Controllers/PutFront.hpp"


void MainGame::initComponent() {
    component->getTurnManager().push_back(std::make_shared<PlayerControl>(std::make_shared<Player>(Player(-1)), component));
    component->getTurnManager().push_back(std::make_shared<PlayerControl>(std::make_shared<Player>(Player(0 )), component));

    for(int i=1; i<9; i++){
        component->getDeck().push_back(std::make_shared<Carte52>(Carte52("Trefle", i)));
    }
    for(int i=1; i<9; i++){
        component->getDeck().push_back(std::make_shared<Carte52>(Carte52("Pique", i)));
    }
    for(int i=1; i<9; i++){
        component->getDeck().push_back(std::make_shared<Carte52>(Carte52("Losange", i)));
    }
    for(int i=1; i<9; i++){
        component->getDeck().push_back(std::make_shared<Carte52>(Carte52("Coeur", i)));
    }
    std::random_device rd;
    auto rnd = std::default_random_engine{rd()};
    std::shuffle(std::begin(component->getDeck()), std::end(component->getDeck()), rnd);
};

bool MainGame::isEnd(){
    return component->getDeck().empty();
}


void MainGame::turnLoop(std::shared_ptr<PlayerControl> p){
    std::cout<<"--------------------Turn of Player"<<p->player->getId()<<"---------------------------------------\n"<<component->toString()<<"\n";

    p->use(std::make_shared<PiocheGameDeck>(PiocheGameDeck("Piocher une carte")));

    std::cout<<p->player->toString()<<"\n";
    
    for(size_t i=0; i< p->player->getHand().size(); i++){
        p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte ", i))  );
    }
    p->play(p->choose(), component);

    std::cout<<"Deck size : "<<component->getDeck().size()<<"\n";
}

void MainGame::endOfTurn(){
    int max= 0;
    int idx = -1;

    for(size_t i=0; i<component->getTurnManager().size(); i++){
        if(component->getTurnManager()[i]->player->getFront().back()->getValue() > max){
            max=component->getTurnManager()[i]->player->getFront().back()->getValue();
            idx=i;
        }else if(component->getTurnManager()[i]->player->getFront().back()->getValue() == max){
            idx=-1;
        }
    }
    if(idx!=-1){
        for(size_t i=0; i<component->getTurnManager().size(); i++){
            for(std::shared_ptr<Card> p : component->getTurnManager()[i]->player->getFront()){
                component->getTurnManager()[idx]->player->pushDeck( component->getTurnManager()[i]->player->removeFront(0) );
            }
        }
    }
}

void MainGame::endOfLoop(){
    std::cout << "Winner : Player ";
    size_t max = 0;
    std::shared_ptr<PlayerControl> winner;
    for( std::shared_ptr<PlayerControl> p : component->getTurnManager()){
        if(p->player->getDeck().size()>max){
            max = p->player->getDeck().size();
            winner = p;
        }
    }
    std::cout << "Winner : Player " <<winner->player->getId()<<"\n";
}
