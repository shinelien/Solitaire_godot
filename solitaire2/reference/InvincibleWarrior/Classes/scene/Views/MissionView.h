//
//  MissionView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/11.
//

#ifndef MissionView_h
#define MissionView_h

#include "BaseLayer.h"
#include "Factory.hpp"
class GameViewHD;
class MainLobby;
class MissionView : public BaseLayer, public Factory<MissionView> {
public:
    virtual ~MissionView();
    MissionView(MainLobby* lobby);
    void updateUI();
    void updateDYY();
    void startLevel();
private:
    void initUI() override;

    void initData() override;
    void dealButtonClick(Ref *pSender) override;
public:
    void onEnter() override;

    void onExit() override;
    
private:
    MainLobby* _lobby;
    int _sub,_group;//当前关卡
    Text *Text_Mission,*Text_start;
    TextBMFont* Text_level;
    Sprite*Sprite_level_icon;
    std::shared_ptr<rapidjson::Document> _LevelData = nullptr;
    GameViewHD* _gameView;
};

#endif /* MissionView_h */
