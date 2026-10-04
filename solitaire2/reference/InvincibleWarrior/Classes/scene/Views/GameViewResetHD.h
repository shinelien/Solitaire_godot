
#ifndef SpacecatSolitaireGame_GameViewResetHD_H
#define SpacecatSolitaireGame_GameViewResetHD_H

#include "BaseLayer.h"
#include "Factory.hpp"

class GameViewHD;
class GameViewResetHD : public BaseLayer, public Factory<GameViewResetHD> {
public:
    virtual ~GameViewResetHD();
    GameViewResetHD(GameViewHD *gameView);

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    GameViewHD *_gameView;
};

#endif //SpacecatSolitaireGame_GameViewResetHD_H
