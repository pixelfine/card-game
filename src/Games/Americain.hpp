#ifndef _AMERICAIN_
#define _AMERICAIN_
 
#include "./../BaseGame/Game/TurnGame.hpp"
#include "CarteA.hpp"

class Americain : public TurnGame{
    public:
        int asPose;
        bool deuxPose;

        std::vector<std::shared_ptr<Card>> poolDeck;

        Americain(GameComponent g) : TurnGame(g), poolDeck(std::vector<std::shared_ptr<Card>>()) {
            asPose = 0;
            deuxPose = false;
        }

        void initComponent() override;
        void turnLoop(std::shared_ptr<PlayerControl> p) override;
        void endOfTurn() override;
        bool isEnd() override;
        void endOfLoop() override;

        void updateDeck();

        int point(std::shared_ptr<PlayerControl> p);
};
#endif