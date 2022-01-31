#ifndef _BELOTE_
#define _BELOTE_
 
#include "./../BaseGame/Game/TurnGame.hpp"
#include "CarteB.hpp"

#include <random>

class Belote : public TurnGame{
    public:
        Belote(GameComponent g) : TurnGame(g), der(0), atout(""){
            rd();
            rnd=std::default_random_engine{ rd() };
        }

        void start() override;
        void init();
        int distribution();
        int oneTurn(int current);
        void turnLoop(std::shared_ptr<PlayerControl> p);

        int bestPlayerFront();

        int compareAtout(Card &c, Card &d);
        int getAtout(Card &c);

    private : 
        size_t der;
        std::string atout;
        std::random_device rd;
        std::default_random_engine rnd;
};
#endif