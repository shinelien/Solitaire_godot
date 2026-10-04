//
//  DrawPropsView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/6.
//

#include <stdio.h>
#include "DrawPropsView.h"
#include "AtlasManager.h"
#include "MainLobby.h"
#include "TeachManager.h"
#include "EventObserver.h"
#include "TaskManager.h"
#include "SpriteManager.h"
#include "SoundManager.h"
#include "DataManager.h"
#include "GameBackground.h"

DrawPropsView::DrawPropsView(std::vector<int> idxVec,DrawPropsView::ViewType type)
:BaseLayer("2020Draw_Props.csb")
,_idxVec(idxVec)
,_type(type)
{
    
}
DrawPropsView::~DrawPropsView()
{
    
}

void DrawPropsView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    getNode("Button_go")->setVisible(true);
    
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    
    this->setPosition(safeArea.size*0.5);
    playAni("Start0",false);
    
    tag = _idxVec.at(_idxVec.size()-1);
    _idxVec.pop_back();;
    auto shoptype = tag /100000;
    shoptype = shoptype%10;
    auto index = tag / 1000;
    index = index%100;
    auto randNum = tag%100000;
    randNum = randNum%1000;
    
    //是金币还是钻石
    auto a = tag /1000000;
    auto b = a/10;
    a = a%10;
    
    isGold = true;//(a) == 1;
    isBuy = false;
    if(shoptype != 6)
    {
        //isBuy = b == 1;
    }
    
    auto card_show = getNode<Sprite*>("card_show");
    auto Text_title = getNode<Text*>("Text_title");
    SpriteFrame* frameA = nullptr;
    if(shoptype == 1)
    {
        if(index > 13)
        {//动态
            if(index<=16)
            {
                frameA = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", 14-12),"car_new_0_1.atlas");
            }
            else
            {
                frameA = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", index-14),"car_new_0_1.atlas");
            }
            
        }
        else
        {
            frameA = AtlasManager::getInstance()->getSF(1, 0, 0, index);
        }
        Text_title->setString(Lang("100123"));
    }
    else if(shoptype == 2)
    {
        auto num = randNum % 13 + 1;
        auto col = (int)(randNum / 13);
        frameA = SPRITE_M->getCardSpriteFrameByNumAndColor(num,col,index);
        Text_title->setString(Lang("100124"));
    }
    else if(shoptype == 3)
    {
        frameA = SPRITE_M->getCardBgSpriteFrame(index);
        Text_title->setString(Lang("100125"));
    }
    else if(shoptype == 5)
    {
        frameA = SpriteFrameCache::getInstance()->getSpriteFrameByName("Ui_music.png");
        Text_title->setString(Lang("100240"));
    }
    else if(shoptype == 6)
    {
        frameA = SpriteFrameCache::getInstance()->getSpriteFrameByName("Magic_0.png");
        getNode<Text*>("Text_magicNum")->setString(StringUtils::format("x%d",randNum));
        Text_title->setString(Lang("100179"));
    }
    if(shoptype == 6)
    {
        getNode<Text*>("Text_magicNum")->setVisible(shoptype == 6);
        getNode("Button_go")->setVisible(shoptype == 6);
        getNode("Panel_button")->setVisible(shoptype != 6);
        getNode("Button_ChuShow")->setVisible(shoptype != 6);
        
        
        getNode("Button_ChuShow")->setVisible(false);
        getNode("Text_content0")->setVisible(false);
        getNode("Text_3_0")->setVisible(false);
        auto FileNode_baoshi = getNode("FileNode_baoshi");
        auto FileNode_baoshi_0 = getNode("FileNode_baoshi_0");
        FileNode_baoshi->setVisible(false);
        FileNode_baoshi_0->setVisible(false);
    }
    else if(isBuy)
    {
        getNode<Text*>("Text_magicNum")->setVisible(!isBuy);
        getNode("Button_go")->setVisible(!isBuy);
        getNode("Panel_button")->setVisible(!isBuy);
        getNode<Text*>("Text_content")->setVisible(false);
        getNode("Button_ChuShow")->setVisible(isBuy);
        getNode("Text_content0")->setVisible(isBuy);
        getNode("Text_3_0")->setVisible(true);
        auto FileNode_baoshi = getNode("FileNode_baoshi");
        auto FileNode_baoshi_0 = getNode("FileNode_baoshi_0");
        FileNode_baoshi->setVisible(isBuy);
        FileNode_baoshi_0->setVisible(isBuy);
        UIUtils::playInnerAction(FileNode_baoshi, isGold?"Gold":"Baoshi", true);
        UIUtils::playInnerAction(FileNode_baoshi_0, isGold?"Gold":"Baoshi", true);
    }
    else
    {
        getNode<Text*>("Text_magicNum")->setVisible(false);
        getNode("Button_go")->setVisible(false);
        auto FileNode_baoshi = getNode("FileNode_baoshi");
        auto FileNode_baoshi_0 = getNode("FileNode_baoshi_0");
        FileNode_baoshi->setVisible(false);
        FileNode_baoshi_0->setVisible(false);
        getNode("Panel_button")->setVisible(true);
        getNode("Button_ChuShow")->setVisible(false);
        getNode("Text_content0")->setVisible(false);
        getNode<Text*>("Text_content")->setVisible(true);
        getNode("Text_3_0")->setVisible(false);
    }
    
    
    
    card_show->setSpriteFrame(frameA);
    
    if(shoptype == 2)
    {
        auto num = randNum % 13 + 1;
        auto col = (int)(randNum / 13);
        auto card_1 = UIUtils::createCSBNode("card/CardFace.csb");
        auto _sprite1 = card_1->getChildByName<Sprite*>("Sprite_face");
        auto _sprite2 = _sprite1->getChildByName<Sprite*>("Sprite_num");
        auto _sprite3 = _sprite1->getChildByName<Sprite*>("Sprite_color");
        _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, col, index));
        _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, col, index));
        _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, col, index));
        _sprite2->setColor(UIUtils::getCardColor(col));
        card_show->addChild(card_1);
        card_1->setPosition(card_show->getContentSize()*0.5f);
        auto size2 = _sprite2->getContentSize();
        _sprite2->setPositionX(size2.width*0.5f);
    }
    
    if (TEACH_M->isTeaching("win_times1")) {
        goaway();
    }
    
    UIUtils::textAdaptiveSize(Text_title,380);
    
    getNode<Text*>("Text_70_0")->setString("+70");
    getNode<Text*>("Text_70_1")->setString("+70");
    getNode<Text*>("Text_content")->setString(Lang("100261"));
    getNode<Text*>("Text_content0")->setString(Lang("100276"));
    getNode<Text*>("Text_ChuShow")->setString(Lang("100278"));
    auto Text_3_0 = getNode<Text*>("Text_3_0");
    Text_3_0->setString(Lang("100277"));
    UIUtils::textAdaptiveSize(Text_3_0,240);
    
    getNode<Text*>("Text_NameNo")->setString(Lang("100260"));
    getNode<Text*>("Text_NameNo2")->setString(Lang("100260"));
    auto Text_NameYes = getNode<Text*>("Text_NameYes");
    Text_NameYes->setString(Lang("yihuode"));
    UIUtils::textAdaptiveSize(Text_NameYes,220);
}
void DrawPropsView::initData()
{
    BaseLayer::initData();
    
    setName("DrawPropsView");
}

void DrawPropsView::goaway()
{
    playAni("Out",false,[](){
        
    });
    initSprite();
}

void DrawPropsView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(btnName == "Button_close"||btnName == "Button_go"||btnName == "Button_go_0")
    {
        if(isBuy)
        {
            nodeAni();
            SCENE_M->removeLayer(this);
        }
        else
        {
            goaway();
        }
        
        //this->setVisible(false);
    }
    else if(btnName == "Button_go_0_0")
    {
        auto shopType = tag /100000;
        shopType = shopType%10;
        auto index = tag / 1000;
        index = index%100;
        
        if(shopType == 1||shopType == 3)
        {
            DATA_M->setCardPicType(shopType, index);
            SPRITE_M->changeCardSkin(shopType);
        }
        else if(shopType == 2)
        {
            auto randNum = tag%100000;
            randNum = randNum%1000;
            DATA_M->setCardPicType(shopType, index,randNum);
            SPRITE_M->changeCardSkin(shopType);
        }
        else if(shopType == 5)
        {
            //累计使用音乐任务数 新手
            TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::MUSIC);
            //使用音乐的话 解除关闭音乐
            DATA_M->setIsMusic(true);
            SOUND_M->playGameBgMusic(StringUtils::format(BGM.c_str(), index));
            DATA_M->setCardPicType(shopType, index);
        }
        
        playAni("Out",false,[](){
            
        });
        initSprite();
        //this->setVisible(false);
    }
    else if(btnName == "Button_ChuShow")
    {
        nodeAni();
    }
}

void DrawPropsView::initSprite()
{
    auto card_show = getNode<Sprite*>("card_show");
    auto poi = card_show->getPosition();
    poi = card_show->getParent()->convertToWorldSpace(poi);
    if(_type == DrawPropsView::ViewType::Home||_type == DrawPropsView::ViewType::Daily)
    {//星星宝箱与皇冠宝箱
        auto lobby = SCENE_M->getLobby();
        lobby->spriteAni(this,(int)_type,[this](){
            if(!_idxVec.empty())
            {
                SCENE_M->addDialog(DrawPropsView::createLayerN(_idxVec,_type));
            }
            SCENE_M->removeLayer(this);
        });
    }
    else if(_type == DrawPropsView::ViewType::SevenGold||_type == DrawPropsView::ViewType::SevenDiamond)
    {//签到宝箱
        auto lobby = SCENE_M->getLobby();
        lobby->spriteAni(this,(int)_type,[this,lobby](){
            if(!_idxVec.empty())
            {
                SCENE_M->addDialog(DrawPropsView::createLayerN(_idxVec,_type));
            }
            else
            {
                lobby->showGuide();
            }
            if(_type == DrawPropsView::ViewType::SevenDiamond)
            {
                auto fishBg = SCENE_M->getGameBackground();
                fishBg->updateBuildComplete();
            }
            SCENE_M->removeLayer(this);
        });
    }
    else
    {
        auto lobby = SCENE_M->getLobby();
        lobby->stroeBoxAni(this,(int)_type,[this](){
            if(!_idxVec.empty())
            {
                SCENE_M->addDialog(DrawPropsView::createLayerN(_idxVec,_type));
            }
            SCENE_M->removeLayer(this);
        });
    }
}

void DrawPropsView::nodeAni()
{
    auto lobby = SCENE_M->getLobby();
    //出现金币
    if(isGold)
    {
        auto coinNum = 70;
        lobby->goldAni(70,nullptr,Vec2(2000,2000),[lobby,this,coinNum](){
            DATA_M->setCoinNum(coinNum, true, 123);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            
        },[lobby,this](){
            //home
           
            lobby->playGoldAni(1,true);
            
            
        },[lobby,this](){
            //home
            
            lobby->playGoldAni(1,false);
            
        });
    }
//    else
//    {
//        auto diamondNum = 70;
//        lobby->diamondAni(70,nullptr,Vec2(2000,2000),[lobby,this,diamondNum](){
//            DATA_M->setDiamond(diamondNum);
//            ValueMap valueMap{
//                {"isTime",Value{true}}
//            };
//            //更新有金币显示
//            EVENT_M->sendEvent("event_game_update_diamond",valueMap);
//           
//        },[lobby,this](){
//            //home
//            
//            lobby->playDiamondAni(1,true);
//            
//            //SOUND_M->playEffectMusic(EffectGetGem);
//            
//        },[lobby,this](){
//            
//                
//            lobby->playDiamondAni(1,false);
//            
//        });
//    }
    if(!_idxVec.empty())
    {
        SCENE_M->addDialog(DrawPropsView::createLayerN(_idxVec,_type));
    }
    SCENE_M->removeLayer(this);
}

void DrawPropsView::onExit()
{
    BaseLayer::onExit();
}
