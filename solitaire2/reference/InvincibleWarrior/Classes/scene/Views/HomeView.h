
#ifndef NewSpaceCatSolitaire_HomeView_H
#define NewSpaceCatSolitaire_HomeView_H

#include "BaseLayer.h"
#include "Factory.hpp"

class MainLobby;
class CardSprite;
class HomeView : public BaseLayer, public Factory<HomeView> {
public:
    virtual ~HomeView();
    HomeView(MainLobby *lobby);

    void updateUI();
    void onEnter() override;

    void onExit() override;
    
    void setIsStart(bool is);
    bool getIsStart();
    void updateDYY();
    void setHard(bool isHuo);
    void setMode(bool isOne);
    
    bool getIsNewGame();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    int _hardSelectIDX, _modeSelectIDX;
    MainLobby *_lobby;
    bool isStart;
    Sprite* _sprite1,*_sprite2,*_sprite3,*_spriteBg;
};

#endif //NewSpaceCatSolitaire_HomeView_H
