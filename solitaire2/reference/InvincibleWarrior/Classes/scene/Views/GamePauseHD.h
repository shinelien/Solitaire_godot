//
// Created by Cyutao on 2018/10/13.
//

#ifndef SPACECATSOLITAIREGAME_GAMEPAUSEHD_H
#define SPACECATSOLITAIREGAME_GAMEPAUSEHD_H

#include "BaseLayer.h"
#include "Factory.hpp"

class GameViewHD;
class GamePauseHD : public BaseLayer, public Factory<GamePauseHD> {
public:
    virtual ~GamePauseHD();
    GamePauseHD(GameViewHD *gameView,bool isPlay = false);
    void setIsPlay(bool isPlay);
private:
    void initUI() override;

    void initData() override;

public:
    void onEnter() override;

    void onExit() override;
    
private:
    void dealButtonClick(Ref *pSender) override;

    void testWinAction();

    GameViewHD *_gameView;
    RenderTexture *_renderTex;
    
    float _top = 0.f;
    //判断是否是后台切换 并播放视频
    bool _isPlay;
    bool isTouch;
    Node*pause_fish_tips;
};


#endif //SPACECATSOLITAIREGAME_GAMEPAUSEHD_H
