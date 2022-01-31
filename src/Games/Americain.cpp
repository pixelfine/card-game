#include "Americain.hpp"
#include <algorithm>
#include <random>
#include "./../BaseGame/Controllers/PiocheGameDeck.hpp"
#include "./../BaseGame/Controllers/PutFront.hpp"
#include "./../BaseGame/Controllers/Pass.hpp"


void Americain::initComponent() {
    component->getTurnManager().push_back(std::make_shared<PlayerControl>(std::make_shared<Player>(Player(-1)), component));
    for(int i=0; i<2; i++){ component->getTurnManager().push_back(std::make_shared<PlayerControl>(std::make_shared<Player>(Player(0 )), component));}
    for(int i=1; i<13; i++){component->getDeck().push_back(std::make_shared<CarteA>(CarteA("Trefle", i)));}
    for(int i=1; i<13; i++){component->getDeck().push_back(std::make_shared<CarteA>(CarteA("Pique", i)));}
    for(int i=1; i<13; i++){component->getDeck().push_back(std::make_shared<CarteA>(CarteA("Carreau", i)));}
    for(int i=1; i<13; i++){component->getDeck().push_back(std::make_shared<CarteA>(CarteA("Coeur", i)));}
    auto rnd = std::default_random_engine{};
    std::shuffle(std::begin(component->getDeck()), std::end(component->getDeck()), rnd);

    for(int i=0; i<7; i++){
        for(size_t i=0; i<component->getTurnManager().size(); i++){
            if(component->getDeck().empty()) break;
            component->getTurnManager()[i]->player->addHand(component->getDeck().back());
            component->getDeck().pop_back();
        }
    }

    this->poolDeck.push_back(component->getDeck().back());
    component->getDeck().pop_back();
}

bool Americain::isEnd() {
    for(auto p : component->getTurnManager()){
        if(p->player->getHand().size()<=1){
            return true;
        }
    }return false;
}

void Americain::turnLoop(std::shared_ptr<PlayerControl> p) {
    updateDeck();
    std::cout<<"--------------------Turn of Player"<<p->player->getId()<<"---------------------------------------\n"<<component->toString()<<"\n";

    std::cout<<p->player->toString()<<"\n";
    std::cout<<"Pool card : ("<<this->poolDeck.back()->getV()<<","<<this->poolDeck.back()->getF()<<")\n";
    if(this->poolDeck.back()->getV()==2 && this->deuxPose==true){
        deuxPose=false;
        if(component->getDeck().size()>0) p->use(std::make_shared<PiocheGameDeck>(PiocheGameDeck("Piocher une carte")));
        if(component->getDeck().size()>0) p->use(std::make_shared<PiocheGameDeck>(PiocheGameDeck("Piocher une carte")));
        p->addAction(std::make_shared<Pass>(Pass("Passer son tour")));
        p->play(p->choose(), component);
        return;
    }

    if(this->poolDeck.back()->getV()==1){
        for(size_t i=0; i<p->player->getHand().size(); i++){
            if(p->player->getHand()[i]->getV()==1 || p->player->getHand()[i]->getV()==2){
                p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte ("+std::to_string(p->player->getHand()[i]->getV())+","+p->player->getHand()[i]->getF()+")", i))  );
            }
        }if(p->choiceList.empty()){
            for(int i=0; i<this->asPose; i++){
                if(component->getDeck().size()>0) p->use(std::make_shared<PiocheGameDeck>(PiocheGameDeck("Piocher une carte")));
                if(component->getDeck().size()>0) p->use(std::make_shared<PiocheGameDeck>(PiocheGameDeck("Piocher une carte")));
            }
        }
        p->addAction(std::make_shared<Pass>(Pass("Passer son tour")));
        p->play(p->choose(), component);
    }else{
        for(size_t i=0; i<p->player->getHand().size(); i++){
            if(p->player->getHand()[i]->getV()== this->poolDeck.back()->getV() ||  p->player->getHand()[i]->getF()== this->poolDeck.back()->getF() || 
              (p->player->getHand()[i]->getV()== 8 && this->poolDeck.back()->getV()!=2)
            ){
                p->addAction(std::make_shared<PutFront>(  PutFront("Mettre carte ("+std::to_string(p->player->getHand()[i]->getV())+","+p->player->getHand()[i]->getF()+")", i))  );
            }
        }p->addAction(std::make_shared<PiocheGameDeck>(PiocheGameDeck("Piocher une carte")));
                p->play(p->choose(), component);
    }
    if(p->player->getFront().size()>0){
        auto c = p->player->getFront()[0];
        if(c->getV()==1){
            this->asPose++;
        }else if(c->getV()==2){
            this->deuxPose=true;;
        }else{
            asPose=0;
            deuxPose=false;
        }
        this->poolDeck.push_back(c);
        p->player->getFront().pop_back();
    }
}

void Americain::endOfTurn() {
    for(auto p : component->getTurnManager()){
        std::cout<< "id :"<<p->player->getId()<<"\n";
    }
}

void Americain::endOfLoop() {
    std::cout<<"end of Game \n";
    size_t min = 0;
    std::shared_ptr<PlayerControl> winner;
    int mini=0;
    int i=0;
    for( std::shared_ptr<PlayerControl> p : component->getTurnManager()){
        if(p->player->getHand().size() < min){
            min = p->player->getHand().size();
            winner = p;
            mini=i;
        }
        i++;
    }
    std::cout<<"min : "<<mini<<"\n";
    std::cout << "Winner : Player " << component->getTurnManager()[mini]->player->getId() <<"\n";
}

void Americain::updateDeck(){
    if(component->getDeck().size()==0){
        for(size_t i=0; i<this->poolDeck.size() -1 ; i++){
            component->getDeck().push_back(poolDeck[i]);
            poolDeck.pop_back();
            auto rnd = std::default_random_engine{};
            std::shuffle(std::begin(component->getDeck()), std::end(component->getDeck()), rnd);
        }
    }
}

int Americain::point(std::shared_ptr<PlayerControl> p){
    int res=0;
    for(size_t i=0; i< p->player->getHand().size(); i++){
        res+=p->player->getHand()[i]->getValue();
    }return res;
}