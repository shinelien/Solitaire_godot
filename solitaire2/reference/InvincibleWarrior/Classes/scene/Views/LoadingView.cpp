//
// Created by  on 2020/5/16.
//

#include "LoadingView.h"
#include "GameBackground.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#include "AtlasManager.h"
#include "BureauTestManager.h"

#include "DataManager.h"
#include "FishGuideManager.h"
#include "ScoreManager.h"
#include "PlayerManager.h"

static long LoadCNT = 0;
void LoadingView::initUI() {
    BaseLayer::initUI();
    doLayout();
    setLocalZOrder(1);
    playAni("idle",false);
    /*auto winSize = Director::getInstance()->getWinSize();
    this->removeAllChildren();
    auto sprite = Sprite::create("ui/imgs/Ui_Task2.png");
    Texture2D *etcTexture = _director->getTextureCache()->addImage("img/etc1-alpha.pkm");
    sprite->setTexture(etcTexture);
    this->addChild(sprite);
    sprite->setPosition(winSize/2);
    return;*/
//    this->runAction(Sequence::create(DelayTime::create(5), RemoveSelf::create())); // 5s后自动消失
    auto loadingbar = getNode<LoadingBar*>("LoadingBar_percent");
    auto sprite = Sprite::create("Default/Slider_PressBar.png");
    sprite->setColor(loadingbar->getColor());
    auto size = loadingbar->getContentSize();
    sprite->setContentSize(size);
    auto ProgressTimer_percent = ProgressTimer::create(sprite);
    
    loadingbar->setPercent(0);
    loadingbar->addChild(ProgressTimer_percent);
    
    ProgressTimer_percent->setPosition(loadingbar->getContentSize()/2);
//    loadingbar->getParent()->addChild(sp);
    //设置进度条的模式
    //kCCProgressTimerTypeBar表示条形模式
    //默认的模式是kCCProgressTimerTypeRadial(圆圈模式)
    ProgressTimer_percent->setType(ProgressTimer::Type::BAR);
    //设置进度条变化的方向
    //setMidpoint默认在左边
    //ccp(1,0)表示在X轴方向上有变化,在y轴方向上没变化
    //ccp(0,1)表示在X轴方向上没有变化,在y轴方向上有变化
    ProgressTimer_percent->setBarChangeRate(Vec2(1,0));
    //从哪个方向开始变化
    //ccp(0,0)表示从左边开始变化
    ProgressTimer_percent->setMidpoint(Vec2(0,0));
    auto Text_percent = getNode<TextBMFont*>("Text_percent");
    Text_percent->setString("1");
    getNode<Text*>("Text_2")->setString("%");
    // 隐藏 banner
    DATA_M->setBannerVisible(false);
    
    vector<std::tuple<std::string, std::string, std::string>> ImageNames{{"ui", "png", "plist"}, {"ui1", "png", "plist"}, {"ui", "png", "plist"}, {"Gamebox", "png", "plist"}, {"dynamicScene", "png", "plist"}, {"time_0", "png", "plist"}, {"car_new_0_1", "png", "atlas"}, {"car_new_0_6", "png", "atlas"},{"challenge","png","plist"}};
    LoadCNT = ImageNames.size();
    auto TotalLoadCNT = ImageNames.size();
    for (auto t:ImageNames) {
        string name = std::get<0>(t);
        string pngName = std::get<1>(t);
        string plistName = std::get<2>(t);
        Director::getInstance()->getTextureCache()->addImageAsync(name+"."+pngName, [this,ProgressTimer_percent,loadingbar, Text_percent, name, plistName, TotalLoadCNT](Texture2D *texture2D){
            if (texture2D != nullptr) {
                auto fullName = name+"."+plistName;
                if (plistName == "plist")
                    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fullName, texture2D);
                else
                    AtlasManager::getInstance()->load(fullName, fullName, texture2D);
            }
            --LoadCNT;
            float currentPercent = (TotalLoadCNT-LoadCNT)*1.0f/TotalLoadCNT * 100;
            
            ProgressTimer_percent->runAction(Sequence::create(ProgressTo::create(.05f, currentPercent), CallFunc::create([currentPercent, Text_percent](){
                Text_percent->setString(StringUtils::format("%.0f", currentPercent));
            }), DelayTime::create(0.01) ,LoadCNT == 1?DelayTime::create(0.03):DelayTime::create(0),LoadCNT == 1?CallFunc::create([this,Text_percent,currentPercent](){
                //Text_percent->setString(StringUtils::format("%.0f", currentPercent));
                AtlasManager::getInstance();
                BureauTestManager::getInstance()->moveFileToWriteablPath();
                SOUND_M->preloadEffect();
                SCENE_M->addDialog(GameBackground::createLayerN());
                SCENE_M->addDialog(GameViewHD::createLayerN());
            }):CallFunc::create([](){}),LoadCNT == 0?DelayTime::create(0.1):nullptr, LoadCNT == 0?CallFunc::create([this,loadingbar,Text_percent](){
                
//                AtlasManager::getInstance();
//                BureauTestManager::getInstance()->moveFileToWriteablPath();
//                SOUND_M->preloadEffect();
//                SCENE_M->addDialog(GameBackground::createLayerN());
//                SCENE_M->addDialog(GameViewHD::createLayerN());
                Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
                    SCENE_M->addDialog(MainLobby::createLayerN());
                });
                getNode("Text_2")->setVisible(false);
                loadingbar->setVisible(false);
                Text_percent->setVisible(false);
                playAni("out",false,[this](){
                    auto gameView = SCENE_M->getGameView();
                    auto delayTime = DelayTime::create(3.15f);
                    auto func = CallFunc::create([gameView](){
                        auto winNum = ScoreManager::getInstance()->getWinTotalCNT();
                        auto lv = PlayerManager::getInstance()->getLevel();
                        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::Three)&&winNum == 1)
                        {
                            auto poi = gameView->getPauseWorldPoi();
                            auto scale = gameView->getNode("FileNode_2020Menu")->getScale();
                            GUIDE_M->startGuide(FishGuideManager::GuideType::Three,gameView,poi,scale);
                        }
                        else if(!GUIDE_M->isEnd(FishGuideManager::GuideType::unlockFashTank,0)&&lv == 18)
                        {//18级了 可以提示了
                            auto poi = gameView->getPauseWorldPoi();
                            auto scale = gameView->getNode("FileNode_2020Menu")->getScale();
                            GUIDE_M->startGuide(FishGuideManager::GuideType::unlockFashTank,gameView,poi,scale,0);
                        }
                    });
                    auto seq = Sequence::create(delayTime,func, NULL);
                    gameView->runAction(seq);
                    SCENE_M->removeLayer(this);
                });
            #if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
                UIUtils::appStartEnd(true);
            #endif
            }):nullptr, NULL));
//            ProgressTimer_percent->setPercentage(currentPercent);
        });
    }

//    SOUND_M->preloadEffect();
}

void LoadingView::initData() {
    BaseLayer::initData();
    setName("LoadingView");
    
    UIUtils::FIRFirestoreAdd("update", {}, [](HttpClient* client, HttpResponse* response){
        if (response->getResponseCode() == 200) {
            auto dataVec = response->getResponseData();
            
            string data(dataVec->begin(), dataVec->end());
            DATA_M->setPlayerVer(data);
        }
    });
}

void LoadingView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
}

LoadingView::LoadingView()
:BaseLayer("Loading0.csb")
{
}

LoadingView::~LoadingView() {

}

void LoadingView::onEnter()
{
    BaseLayer::onEnter();
}

void LoadingView::onExit()
{
    BaseLayer::onExit();
}
