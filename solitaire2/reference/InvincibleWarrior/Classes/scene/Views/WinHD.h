//
// Created by Cyutao on 2018/11/25.
//

#ifndef SPACECATSOLITAIREGAME_WINHD_H
#define SPACECATSOLITAIREGAME_WINHD_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class WinHD : public cocos2d::ui::Widget {
public:
    CREATE_FUNC(WinHD);

    bool init() override;

    void show(std::function<void(cocos2d::Ref*)> cb);
    void showWinAction(const cocos2d::Vec2 &pos, int num, int suit, float delay);
private:
    cocos2d::RenderTexture *_renderTex = nullptr;
//    Sequence *leftSeq, *rightSeq;
};


#endif //SPACECATSOLITAIREGAME_WINHD_H
