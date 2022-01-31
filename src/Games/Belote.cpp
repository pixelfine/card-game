#include "Belote.hpp"
#include <algorithm>
#include "./../BaseGame/Input.hpp"

#include "./../BaseGame/Controllers/PiocheGameDeck.hpp"
#include "./../BaseGame/Controllers/PutGameDeck.hpp"
#include "./../BaseGame/Controllers/PutFront.hpp"

void Belote::start() {
    init();
    int preneur = distribution();
    oneTurn(preneur);

    int res=0;
    std::shared_ptr<Card> c;
    for(size_t i=0; i<component->getTurnManager().size(); i++ ){
        if(i==der){
            res+=10;
        }
        while(! component->getTurnManager()[i]->player->getDeck().empty()){
            c = component->getTurnManager()[i]->player->popDeck();
            if(c->getF().compare(atout)==0){
                res+=getAtout(*c);
            }else{
                res+=c->getValue();
            }
        }
        std::cout<<"Player "<<component->getTurnManager()[i]->player->getId()<< ": "<< res <<"\n";
        res=0;
    }
}

void Belote::init() {
    component->getTurnManager().push_back(std::make_shared<PlayerControl>(std::make_shared<Player>(Player(-1)), component));
    for(int i=0; i<3; i++){
        component->getTurnManager().push_back(std::make_shared<PlayerControl>(std::make_shared<Player>(Player(0 )), component));
    }
    component->getDeck().push_back(std::make_shared<CarteB>(CarteB("Trefle",  1)));
    component->getDeck().push_back(std::make_shared<CarteB>(CarteB("Pique",   1)));
    component->getDeck().push_back(std::make_shared<CarteB>(CarteB("Losange", 1)));
    component->getDeck().push_back(std::make_shared<CarteB>(CarteB("Coeur",   1)));
    for(int i=7; i<14; i++) component->getDeck().push_back(std::make_shared<CarteB>(CarteB("Trefle", i)));
    for(int i=7; i<14; i++) component->getDeck().push_back(std::make_shared<CarteB>(CarteB("Pique", i)));
    for(int i=7; i<14; i++) component->getDeck().push_back(std::make_shared<CarteB>(CarteB("Losange", i)));
    for(int i=7; i<14; i++) component->getDeck().push_back(std::make_shared<CarteB>(CarteB("Coeur", i)));

    std::cout << "DeckSize : "<<component->getDeck().size()<<"\n";
}

int Belote::distribution() {
    int idx=0;
    int n=-1;
    int preneur = -1;
    int preneurtmp;
    while(atout.compare("")==0){
        std::shuffle(std::begin(component->getDeck()), std::end(component->getDeck()), rnd);
        for(auto p : component->getTurnManager()){
            for(int i=0; i<5; i++) p->use(std::make_shared<PiocheGameDeck>(PiocheGameDeck("Piocher une carte")));
        }
        for(auto p : component->getTurnManager()){
            if(preneur==-1){
                std::cout<<p->player->toString()<<"\n";
                n=p->chooseRange(0,1, "0 : Pass\n1 : Take Atout"+component->getDeck().back()->toString()+"\n");
                switch(n){
                    case 0 : break;
                    case 1 : preneur = idx; atout = component->getDeck().back()->getF(); break;
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
    preneurtmp = preneur;
    while(!component->getDeck().empty()){
        component->getTurnManager()[preneurtmp]->player->addHand(component->getDeck().back());
        component->getDeck().pop_back();
        preneurtmp=((preneurtmp+1)% component->getTurnManager().size());
    }return preneur;
}

int Belote::oneTurn(int current) {
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

void Belote::turnLoop(std::shared_ptr<PlayerControl> p) {
    std::cout<<"--------------------Turn of Player"<<p->player->getId()<<"---------------------------------------\n"<<component->toString()<<"\n"<<"Atout : "<<atout<<"\n";

    std::cout<<p->player->toString()<<"\n";

    int n =0;
    if(component->getDeck().size()==0){
        for(size_t i=0; i<p->player->getHand().size(); i++){
            p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte "+p->player->getHand()[i]->toString(), i))  );
        }
    }else{
        for(size_t i=0; i<p->player->getHand().size(); i++){
             if((p->player->getHand()[i]->getF().at(0) == component->getDeck().front()->getF().at(0))){
                 p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte "+p->player->getHand()[i]->toString(), i))  );
             }
        }
    }
    if(p->choiceList.empty()){
        for(size_t i=0; i<p->player->getHand().size(); i++){
            if(p->player->getHand()[i]->getF().compare(atout)==0)
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

int Belote::bestPlayerFront() {
    auto tmp = component->getTurnManager(); 
    size_t idx =0;
    auto max = tmp[0]->player->getFront()[0];
    for(size_t i=1; i<component->getTurnManager().size(); i++){
        if(compareAtout(*max, *(tmp[i]->player->getFront()[0])) <0){
            idx = i;
            max = tmp[i]->player->getFront()[0];
        }
    }
    if(component->getTurnManager()[0]->player->getHand().size()==0){
        der=idx;
    }
    return idx;
}

int Belote::getAtout(Card &c){
    switch(c.getV()){
        case 11: return 20;
        case 9 : return 14;
        case 1 : return 11;
        case 10: return 10;
        case 13: return 4 ;
        case 12: return 3 ;
        default: return 0 ;
    }
}

int Belote::compareAtout(Card &c, Card &d) {
    int v1=0;
    int v2=0;
    if(c.getF().compare(atout)==0) v1=getAtout(c); else v1= c.getValue();
    if(d.getF().compare(atout)==0) v2=getAtout(d); else v2= d.getValue();
    return v1-v2;
}
