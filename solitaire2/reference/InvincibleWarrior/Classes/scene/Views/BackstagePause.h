//
//  BackstagePause.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/7.
//

#ifndef BackstagePause_h
#define BackstagePause_h
#include "BaseLayer.h"
#include "Factory.hpp"

class GameViewHD;
class BackstagePause : public BaseLayer, public Factory<BackstagePause> {
public:
    virtual ~BackstagePause();
    BackstagePause(GameViewHD *gameView,bool isPlay = false);
    void setIsPlay(bool isPlay);
    void setMusic(bool isMusic);
    void setEffMusic(bool isMusic);
private:
    void initUI() override;

    void initData() override;
    void dealButtonClick(Ref *pSender) override;
public:
    void onEnter() override;

    void onExit() override;
    
private:
    bool isPause;
    Button *btn_music_on,*btn_effTips;
    GameViewHD *_gameView;
    float _top = 0.f;
    //判断是否是后台切换 并播放视频
    bool _isPlay;
    bool isTouch;
};

#endif /* BackstagePause_h */
