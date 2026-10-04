//
//  StarBoxView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/25.
//

#include <stdio.h>
#include "StarBoxView.h"
#include "MainLobby.h"
#include "GameViewHD.hpp"
#include "HomeView.h"
#include "DailyView.h"
#include "MissionView.h"
const string BOX = "box";
StarBoxView::StarBoxView(StarBoxView::Type type)
:BaseLayer("2020StarBox.csb")
,_type(type)
{
    
}
StarBoxView::~StarBoxView()
{
    
}
  

void StarBoxView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    _gameView = SCENE_M->getGameView();
    _mainLobby = SCENE_M->getLobby();
    playAni("Start0",false);
    FileNode_box = getNode("FileNode_box");
    
    
    //需要判断全部语言
    auto languageCode = DATA_M->getAllDyyStr();
    
    this->enumerateChildren("//Text_StarNum_..", [](Node *node){
        node->setVisible(false);
        return false;
    });
    auto Text_StarNum = getNode<Text*>(StringUtils::format("Text_StarNum_%s",languageCode.c_str()));
    if (Text_StarNum)
        Text_StarNum->setVisible(true);
    if(_type == StarBoxView::Type::Home||_type == StarBoxView::Type::Level)
    {
        auto num1 = DATA_M->getStarBoxNum();
        auto num2 = DATA_M->getStarBoxNumMax();
        getNode<Text*>("Text_5_0")->setString(Lang("100236"));
        if (Text_StarNum)
            Text_StarNum->setString(StringUtils::format(Lang("100238").c_str(),num2));
        getNode<Text*>("Text_10")->setString(Lang("100234"));
        string name = "";
        if(num2 <= 2)
        {
            name = "Box_0.png";
        }
        else if(num2 <= 4)
        {
            name = "Box2_0.png";
        }
        else if(num2 <= 6)
        {
            name = "Box3_0.png";
        }
        else if(num2 <= 8)
        {
            name = "Box4_0.png";
        }
        else
        {
            name = "Box4_0.png";
        }
        auto Sprite_Box = FileNode_box->getChildByName<Sprite*>("Sprite_Box");
        Sprite_Box->setSpriteFrame(name);
        
    }
    else if(_type == StarBoxView::Type::Daily)
    {
        auto num1 = DATA_M->getDailyStarBoxNum();
        auto num2 = DATA_M->getDailyStarBoxNumMax();
        getNode<Text*>("Text_5_0")->setString(Lang("100237"));
        if (Text_StarNum)
            Text_StarNum->setString(StringUtils::format(Lang("100239").c_str(),num2));
        getNode<Text*>("Text_10")->setString(Lang("100235"));
        string name = "";
        
        if(num2 <= 3) {
            name = "Box_0.png";
        }
        else if(num2 <= 5) {
            name = "Box2_0.png";
        }
        else if(num2 <= 19) {
            name = "Box3_0.png";
        }
        else if(num2 == 20) {
            name = "Box6_0.png";
        }
        else {
            name = "Box6_0.png";
        }
        auto Sprite_Box = FileNode_box->getChildByName<Sprite*>("Sprite_Box");
        Sprite_Box->setSpriteFrame(name);
        
    }
    
    auto animanager = dynamic_cast<ActionTimeline*>(FileNode_box->getActionByTag(FileNode_box->getTag()));
    animanager->setFrameEventCallFunc([this](Frame* f){
        auto e = dynamic_cast<EventFrame*>(f);
        auto msg = e->getEvent();
        if(msg.find(BOX) != string::npos)
        {
            auto idstr = msg[3];
            auto Sprite_Box = FileNode_box->getChildByName<Sprite*>("Sprite_Box");
            if(idstr == '1')
            {
                SOUND_M->playEffectMusic(EffectBoxOpen);
            }
            if(_type == StarBoxView::Type::Home||_type == StarBoxView::Type::Level)
            {
                auto max = DATA_M->getStarBoxNumMax();
                string name = "";
                
                if(max <= 2)
                {
                    name = "Box_%c.png";
                }
                else if(max <= 4)
                {
                    name = "Box2_%c.png";
                }
                else if(max <= 6)
                {
                    name = "Box3_%c.png";
                }
                else if(max <= 8)
                {
                    name = "Box4_%c.png";
                }
                else
                {
                    name = "Box4_%c.png";
                }
                Sprite_Box->setSpriteFrame(StringUtils::format(name.c_str(),idstr));
            }
            else if(_type == StarBoxView::Type::Daily)
            {
                auto max = DATA_M->getDailyStarBoxNumMax();
                string name = "";
                if(max <= 3)
                {
                    name = "Box_%c.png";
                }
                else if(max <= 5)
                {
                    name = "Box2_%c.png";
                }
                else if(max <= 19)
                {
                    name = "Box3_%c.png";
                }
                else if(max == 20)
                {
                    name = "Box6_%c.png";
                }
                else
                {
                    name = "Box6_%c.png";
                }
                Sprite_Box->setSpriteFrame(StringUtils::format(name.c_str(),idstr));
            }
        }
    });
    
    
    if (Text_StarNum)
        Text_StarNum->setVisible(true);
    getNode("Button_Start")->setVisible(true);
    getNode("Button_Open")->setVisible(false);
    
 
    auto Text_5_0_0 = getNode<Text*>("Text_5_0_0");
    Text_5_0_0->setString(Lang("100288"));
    UIUtils::textAdaptiveSize(Text_5_0_0,880);
    getNode<Text*>("Text_Start")->setString(Lang("100172"));
        
}
void StarBoxView::initData()
{
    BaseLayer::initData();
    setName("StarBoxView");
}
void StarBoxView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto name = btn->getName();
    if(name == "Button_close"||name == "Panel_top_0")
    {
        SCENE_M->removeLayer(this);
    }
    else if(name == "Button_Start")
    {
        auto lobby = SCENE_M->getLobby();
        auto gameView = SCENE_M->getGameView();
        
        if(!gameView->isVisible())
        {
            lobby->startGame();
        }
        
        SCENE_M->removeLayer(this);
//        if(_type == StarBoxView::Type::Home)
//        {
////            auto home = dynamic_cast<HomeView*>(_mainLobby->setTab(MainLobby::Tab::Home));
////            home->setHard(true);
////            home->setMode(true);
////            DATA_M->setGameType(DataManager::GameType::Huo);
////            DATA_M->setIsThreeModel(false);
//            //更新ui。 单张三张 困难简单
//            bool is = _mainLobby->getIsNewGame();
//            _mainLobby->startGame(is);
//            //播放音效
//            //恢复音效
//            //SOUND_M->resumeDTEffect();
//            //_mainLobby->setVisible(false);
//        }
//        else if(_type == StarBoxView::Type::Daily)
//        {
//            auto daily = dynamic_cast<DailyView*>(_mainLobby->setTab(MainLobby::Tab::Daily));
//            //筛选简单的日期
//            daily->filterSimpleDate();
//            daily->showSelectDialog();
//        }
//        else if(_type == StarBoxView::Type::Level)
//        {
//            auto level = dynamic_cast<MissionView*>(_mainLobby->setTab(MainLobby::Tab::Level));
//            level->startLevel();
//        }
    }
}

void StarBoxView::onExit()
{
    BaseLayer::onExit();
}
