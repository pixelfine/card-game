#include "Tarot.hpp"
#include <algorithm>
#include "./../BaseGame/Input.hpp"

#include "./../BaseGame/Controllers/PiocheGameDeck.hpp"
#include "./../BaseGame/Controllers/PutGameDeck.hpp"
#include "./../BaseGame/Controllers/PutFront.hpp"

void Tarot::init(){
    component->getTurnManager().push_back(std::make_shared<PlayerControl>(std::make_shared<Player>(Player(-1)), component));
    for(int i=0; i<3; i++){
        component->getTurnManager().push_back(std::make_shared<PlayerControl>(std::make_shared<Player>(Player(0 )), component));
    }
    for(int i=1; i<15; i++){
        component->getDeck().push_back(std::make_shared<CarteT>(CarteT("Trefle", i)));
    }
    for(int i=1; i<15; i++){
        component->getDeck().push_back(std::make_shared<CarteT>(CarteT("Pique", i)));
    }
    for(int i=1; i<15; i++){
        component->getDeck().push_back(std::make_shared<CarteT>(CarteT("Losange", i)));
    }
    for(int i=1; i<15; i++){
        component->getDeck().push_back(std::make_shared<CarteT>(CarteT("Coeur", i)));
    }
    for(int i=1; i<22; i++){
        component->getDeck().push_back(std::make_shared<CarteT>(CarteT("*", i)));
    }

    std::cout << "DeckSize : "<<component->getDeck().size()<<"\n";
}

void Tarot::distribution(){
    int idx=0;
    int n=-1;

    while(preneur==-1){
        std::shuffle(std::begin(component->getDeck()), std::end(component->getDeck()), rnd);
        for(auto p : component->getTurnManager()){

            for(int i=0; i<18; i++) p->use(std::make_shared<PiocheGameDeck>(PiocheGameDeck("Piocher une carte")));
            if(preneur==-1){
                std::cout<<p->player->toString()<<"\n";
                n=p->chooseRange(0,1, "0 : Pass\n1 : Keep with chien\n");
                switch(n){
                    case 0 : break;
                    case 1 : preneur = idx; break;
                }
            }
            idx++;
        }
        if(preneur == -1){
            for(auto p : component->getTurnManager()){
                for(size_t i=0; i< p->player->getHand().size(); i++){
                    p->use(std::make_shared<PutGameDeck>(PutGameDeck("Put to deck", i)));
                }
            }
        }
    }
    std::cout<<"Le preneur est : Player "<<component->getTurnManager()[preneur]->player->getId()<<"\n";
    while(!component->getDeck().empty()){
        component->getTurnManager()[preneur]->player->pushDeck(component->getDeck().back());
        component->getDeck().pop_back();
    }
}

int Tarot::oneTurn(int current){
    if(component->getTurnManager()[current]->player->getHand().empty()) return -1;

    std::cout<<"---------------------New Turn--------------------------------------------------\n";

    int index = current;
    for(size_t i=0; i<component->getTurnManager().size(); i++){

        turnLoop(component->getTurnManager()[index]);
        index=(index+1)%component->getTurnManager().size();
    }

    int best = bestPlayerFront();
    for(auto p : component->getTurnManager()){
        component->getTurnManager()[best]->player->pushDeck(p->player->removeFront(0));
        component->getDeck().clear();
    }
    std::cout<<"---------------------Player "<<component->getTurnManager()[best]->player->getId()<<"wins the turn--------------------------\n";
    return oneTurn(best);
}

void Tarot::turnLoop(std::shared_ptr<PlayerControl> p){
    std::cout<<"--------------------Turn of Player"<<p->player->getId()<<"---------------------------------------\n"<<component->toString()<<"\n";
    std::cout<<p->player->toString()<<"\n";

    int n =0;
    if(component->getDeck().size()==0){
        for(size_t i=0; i<p->player->getHand().size(); i++){
            p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte "+p->player->getHand()[i]->toString(), i))  );
        }
    }else if(component->getDeck().back()->getF().at(0)=='*'){
        for(size_t i=0; i<p->player->getHand().size(); i++){
            if( p->player->getHand()[i]->compare(*component->getDeck().back()) >0 ){
                p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte "+p->player->getHand()[i]->toString(), i))  );
            }
        }
    }else{
        for(size_t i=0; i<p->player->getHand().size(); i++){
             if((p->player->getHand()[i]->getF().at(0) == component->getDeck().back()->getF().at(0))){
                 p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte "+p->player->getHand()[i]->toString(), i))  );
             }
        }
    }
    if(p->choiceList.empty()){
        for(size_t i=0; i<p->player->getHand().size(); i++){
            if(p->player->getHand()[i]->getF().at(0)=='*')
                p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte "+p->player->getHand()[i]->toString(), i))  );
        }
    }
    
    if(p->choiceList.empty()){
        for(size_t i=0; i<p->player->getHand().size(); i++){
            p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte "+p->player->getHand()[i]->toString(), i))  );
        }
    }
    n = p->choose();
    p->play(n, component);
    component->getDeck().push_back(p->player->getFront()[0]);
    
}

void Tarot::start() {
    init();
    distribution();
    oneTurn(preneur);

    int res=0;
    for(size_t i=0; i<component->getTurnManager().size(); i++ ){
        while(! component->getTurnManager()[i]->player->getDeck().empty()){
            res+=component->getTurnManager()[i]->player->popDeck()->getValue();
        }
        std::cout<<"Player "<<component->getTurnManager()[i]->player->getId()<< ": "<< res <<"\n";
        res=0;
    }
}

int Tarot::bestPlayerFront(){
    auto tmp = component->getTurnManager(); 
    size_t idx =0;
    auto max = tmp[0]->player->getFront()[0];
    for(size_t i=1; i<component->getTurnManager().size(); i++){
        if(max->compare(*(tmp[i]->player->getFront()[0])) <0){
            idx = i;
            max = tmp[i]->player->getFront()[0];
        }
    }
    return idx;
}