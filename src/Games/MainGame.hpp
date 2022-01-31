#ifndef _MAINGAME_
#define _MAINGAME_
 
#include "./../BaseGame/Game/TurnGame.hpp"
#include "Carte52.hpp"

class MainGame : public TurnGame{
    public:
        MainGame(GameComponent g) : TurnGame(g){}

        void initComponent() override;
        void turnLoop(std::shared_ptr<PlayerControl> p) override;
        void endOfTurn() override;
        bool isEnd() override;
        void endOfLoop() override;
};
#endif