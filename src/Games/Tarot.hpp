#ifndef _TAROT_
#define _TAROT_
 
#include "./../BaseGame/Game/TurnGame.hpp"
#include "CarteT.hpp"

#include <random>

class Tarot : public TurnGame{
    public:
        Tarot(GameComponent g) : TurnGame(g), preneur(-1){
            rd();
            rnd=std::default_random_engine{ rd() };
        }

        void start() override;
        void init();
        void distribution();
        int oneTurn(int current);
        void turnLoop(std::shared_ptr<PlayerControl> p);

        int bestPlayerFront();

    private : 
        int preneur;
        std::random_device rd;
        std::default_random_engine rnd;
};
#endif