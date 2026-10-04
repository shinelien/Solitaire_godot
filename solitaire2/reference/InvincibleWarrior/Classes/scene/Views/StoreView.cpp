//
//  StoreView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/2/25.
//

#include <stdio.h>
#include "StoreView.h"
#include "ShopNode.h"
#include "MainLobby.h"
#include "PlayerManager.h"
#include "FanPaiRewardView.h"
#include "BagView.h"
#include "GrowupNode.h"
#include "UIUtils.h"
#include "FreeCoinLayer.h"
#include "TeachManager.h"
#include "AtlasManager.h"
#include "SpriteManager.h"

const string TAB_PRFIX = "Button_tab";
const string SHOPDYY = "Shop_fnt_%s";

StoreView::StoreView(MainLobby*mainLobby)
:BaseLayer("2020Store_0.csb")
,_mainLobby(mainLobby)
,goldBS(1)
,diamondBS(1)
,isGold(true)
,isDiamond(true)
{
    
}
StoreView::~StoreView()
{
    
}

void StoreView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    FileNode_MyBag = getNode("FileNode_MyBag");
    auto FileNode_bag_A = getNode("FileNode_bag_A");
    UIUtils::playInnerAction(FileNode_bag_A, "KingLoop", true);
    Node_dyy = getNode("Node_dyy");
    
    FileNode_Gold_btn = getNode("FileNode_Gold_btn");
    FileNode_Diamond_btn = getNode("FileNode_Diamond_btn");
    Text_btnGold = getNode<TextBMFont*>("BitmapFontLabel_Gold_store");
    Text_btnDiamond = getNode<TextBMFont*>("BitmapFontLabel_Diamond_store");
    
    FileNode_MiaoShu = getNode("FileNode_MiaoShu");
    getNode("Image_GoldMiaoShu")->setVisible(true);
    getNode("Image_DiamondMiaoShu")->setVisible(true);
    
    
    Text_gold_front = getNode<Text*>("Text_gold_front");
    Text_gold_bg = getNode<Text*>("Text_gold_bg");
    Text_gold_magic = getNode<Text*>("Text_gold_magic");
    Text_gold_bigwin = getNode<Text*>("Text_gold_bigwin");
    Text_diamond_front = getNode<Text*>("Text_diamond_front");
    Text_diamond_bg = getNode<Text*>("Text_diamond_bg");
    Text_diamond_magic = getNode<Text*>("Text_diamond_magic");
    Text_diamond_bigwin = getNode<Text*>("Text_diamond_bigwin");
    Text_diamonnd_scene = getNode<Text*>("Text_diamonnd_scene");
    Text_diamond_music = getNode<Text*>("Text_diamond_music");
    
    
    card_gold_fronts = getNode<Sprite*>("card_gold_fronts");
    card_gold_bg = getNode<Sprite*>("card_gold_bg");
    card_diamond_front = getNode<Sprite*>("card_diamond_front");
    card_diamond_bg = getNode<Sprite*>("card_diamond_bg");
    scene_diamond_bg = getNode<Sprite*>("scene_diamond_bg");
    
    card_1 = UIUtils::createCSBNode("card/CardFace.csb");
    card_2 = UIUtils::createCSBNode("card/CardFace.csb");
    card_gold_fronts->addChild(card_1);
    card_diamond_front->addChild(card_2);
    
    
    if(goldBS == 1)
    {
        UIUtils::playInnerAction(FileNode_Gold_btn, "Loop_L0", true);
    }
    else
    {
        UIUtils::playInnerAction(FileNode_Gold_btn, "Loop_R0", true);
    }
    
    if(diamondBS == 1)
    {
        UIUtils::playInnerAction(FileNode_Diamond_btn, "Loop_L0", true);
    }
    else
    {
        UIUtils::playInnerAction(FileNode_Diamond_btn, "Loop_R0", true);
    }
    
    //多语言
    updateDYY();
    
    
    updateUI();
}
void StoreView::initData()
{
    BaseLayer::initData();
    setName("StoreView");
}
void StoreView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(btnName == "Button_close")
    {
        //_mainLobby->setVisible(true);
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_Gold_btn"&&isGold)
    {//金币
        SOUND_M->playEffectMusic(EffectButtonStart);
        isGold = false;
        if(goldBS == 1)
        {
            goldBS = 5;
            UIUtils::playInnerAction(FileNode_Gold_btn, "Start_L0", false,[this](){
                UIUtils::playInnerAction(FileNode_Gold_btn, "Loop_R0", false);
                isGold = true;
            });
        }
        else
        {
            goldBS = 1;
            UIUtils::playInnerAction(FileNode_Gold_btn, "Start_R0", false,[this](){
                UIUtils::playInnerAction(FileNode_Gold_btn, "Loop_L0", false);
                isGold = true;
            });
        }
        updateBtnGold();
    }
    else if(btnName == "Button_Diamond_btn"&&isDiamond)
    {//钻石
        SOUND_M->playEffectMusic(EffectButtonStart);
        isDiamond = false;
        if(diamondBS == 1)
        {
            diamondBS = 5;
            UIUtils::playInnerAction(FileNode_Diamond_btn, "Start_L0", false,[this](){
                UIUtils::playInnerAction(FileNode_Diamond_btn, "Loop_R0", false);
                isDiamond = true;
            });
        }
        else
        {
            diamondBS = 1;
            UIUtils::playInnerAction(FileNode_Diamond_btn, "Start_R0", false,[this](){
                UIUtils::playInnerAction(FileNode_Diamond_btn, "Loop_L0", false);
                isDiamond = true;
            });
        }
        updateBtnDiamond();
    }
    else if(btnName == "Button_gold")
    {
        //抽奖
        auto num = DATA_M->getCoinNum();
        if(num >= goldBS*100)
        {
            SOUND_M->playEffectMusic(EffectCashregister);
            DATA_M->setCoinNum(-goldBS*100,false,203);
            //更新有金币显示
            _mainLobby->updateCoin();
            
            auto fanpai = SCENE_M->getFanPaiRewardView();
            if(!fanpai)
            {
                fanpai = FanPaiRewardView::createLayerN(goldBS,FanPaiRewardView::Type::None);
                SCENE_M->addDialog(fanpai);
            }
            fanpai->setRewardNum(goldBS);
            fanpai->setType(FanPaiRewardView::Type::None);
            fanpai->setConsumptionType(FanPaiRewardView::ConsumptionType::Gold);
            fanpai->startFanPai();
            if (TEACH_M->isTeaching())
                UIUtils::FIRAnalyticsEventWithPrefix(string("goldBox_") + TEACH_M->getCurrentTeachKey(), "teach");
        }
        else
        {
            
            SCENE_M->showTips(Lang("100096"),false,[this](){
                
            });
            if(!SCENE_M->getFreeCoinLayer())
            {//弹窗
                SCENE_M->addDialog(FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Gold));
            }
        }
    }
    else if(btnName == "Button_diamond")
    {//抽奖
        //抽奖
        
//        auto num = DATA_M->getDiamond();
//        if(num >= diamondBS*100)
//        {
//            SOUND_M->playEffectMusic(EffectCashregister);
//            DATA_M->setDiamond(-diamondBS*100,false);
//            //更新有金币显示
//            _mainLobby->updateDiamond();
//            
//            auto fanpai = SCENE_M->getFanPaiRewardView();
//            if(!fanpai)
//            {
//                fanpai = FanPaiRewardView::createLayerN(diamondBS,FanPaiRewardView::Type::None);
//                SCENE_M->addDialog(fanpai);
//            }
//            fanpai->setRewardNum(diamondBS);
//            fanpai->setType(FanPaiRewardView::Type::None);
//            fanpai->setConsumptionType(FanPaiRewardView::ConsumptionType::Diamond);
//            fanpai->startFanPai();
//        }
//        else
//        {
//            
//            SCENE_M->showTips(Lang("100293"),false,[this](){
//                
//            });
//            
//            if(!SCENE_M->getFreeCoinLayer())
//            {//弹窗
//                SCENE_M->addDialog(FreeCoinLayer::createLayerN(FreeCoinLayer::Type::Diamond));
//            }
//        }
    }
    else if(btnName == "Button_Mybag")
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
        UIUtils::playInnerAction(FileNode_MyBag,"Start",false);
        //背包
        SCENE_M->addDialog(BagView::createLayerN(BagView::BagType::CARD));
        auto lobby = SCENE_M->getLobby();
        if(lobby)
        {
            lobby->isShowTop(false);
        }
    }
    else if(btnName == "Button_GoldMiaoShu")
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
        FileNode_MiaoShu->setVisible(true);
        updateMiaoShu();
        UIUtils::playInnerAction(FileNode_MiaoShu,"Start",false);
    }
    else if(btnName == "Button_DiamondMiaoShu")
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
        FileNode_MiaoShu->setVisible(true);
        updateMiaoShu();
        UIUtils::playInnerAction(FileNode_MiaoShu,"Start",false);
    }
    else if(btnName == "Panel_out")
    {
        FileNode_MiaoShu->setVisible(false);
    }
}


void StoreView::onEnter()
{
    BaseLayer::onEnter();
    updateUI();
    UIUtils::FIRAnalyticsEventWithPrefix("StoreView");
}

void StoreView::onExit()
{
    BaseLayer::onExit();
//    SCENE_M->getGameView()->showNode("Panel_top", true);
}

void StoreView::updateUI()
{
//    getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
//    getNode<Text*>("Text_level")->setString(toString(PlayerManager::getInstance()->getLevel()));
//    getNode<LoadingBar*>("LoadingBar_level")->setPercent(PlayerManager::getInstance()->getPercent());
//    updateCoin();
//    updateDiamond();
    updataBagNew();
    updateMiaoShu();
}

Vec2 StoreView::getBagWorldPoi()
{
    auto poi = FileNode_MyBag->getPosition();
    poi = FileNode_MyBag->getParent()->convertToWorldSpace(poi);
    return poi;
}

void StoreView::updateDYY()
{
    //只需要判断部分语言
    auto languageCode = DATA_M->getSectionDyyStr();
    
    //清空
    auto vec = Node_dyy->getChildren();
    for(auto child : vec)
    {
        child->setVisible(false);
    }
    
    auto dyyNode = getNode(StringUtils::format(SHOPDYY.c_str(),languageCode.c_str()));
    if (dyyNode)
        dyyNode->setVisible(true);
    
    Text_gold_front->setString(Lang("100245"));
    Text_gold_bg->setString(Lang("100067"));
    UIUtils::textAdaptiveSize(Text_gold_bg,150);
    Text_gold_magic->setString(Lang("100179"));
    UIUtils::textAdaptiveSize(Text_gold_magic,170);
    Text_gold_bigwin->setString(Lang("100244"));
    Text_diamond_front->setString(Lang("100245"));
    Text_diamond_bg->setString(Lang("100067"));
    UIUtils::textAdaptiveSize(Text_diamond_bg,150);
    Text_diamond_magic->setString(Lang("100179"));
    UIUtils::textAdaptiveSize(Text_diamond_magic,170);
    Text_diamond_bigwin->setString(Lang("100244"));
    Text_diamonnd_scene->setString(Lang("100123"));
    UIUtils::textAdaptiveSize(Text_diamonnd_scene,120);
    Text_diamond_music->setString(Lang("100240"));
    
    getNode<Text*>("Text_GoldBox")->setString(Lang("100241"));
    getNode<Text*>("Text_DiamondBox")->setString(Lang("100242"));
    auto Text_Allreward = getNode<Text*>("Text_Allreward");
    Text_Allreward->setString(Lang("100243"));
    
    getNode<Text*>("Text_MyBag")->setString(Lang("100284"));
    getNode<Text*>("Text_x5_miaoShu")->setString(Lang("100322"));
    
    languageCode = DATA_M->getAllDyyStr();
    if(languageCode == "ru")
    {
        Text_Allreward->setFontSize(30);
    }
    else
    {
        Text_Allreward->setFontSize(34);
    }
}


void StoreView::updateBtnGold()
{
    //Text_btnGold
    int num = 0;
    int num2 = 0;
    
    if(goldBS == 1)
    {
        num = 500;
        num2 = 100;
    }
    else if(goldBS == 5)
    {
        num = 100;
        num2 = 500;
    }
    auto grouwup = GrowupNode::create();
    Text_btnGold->addChild(grouwup);
    grouwup->startGrouwup(Text_btnGold, num, num2, 0.2, "",[this, grouwup](){
        //UIUtils::playInnerAction(FileNode_gold, "jump", false);
        grouwup->removeFromParent();
    });
}
void StoreView::updateBtnDiamond()
{
    //Text_btnDiamond
    int num = 0;
    int num2 = 0;
    
    if(diamondBS == 1)
    {
        num = 500;
        num2 = 100;
    }
    else if(diamondBS == 5)
    {
        num = 100;
        num2 = 500;
    }
    ;
    auto grouwup = GrowupNode::create();
    Text_btnDiamond->addChild(grouwup);
    grouwup->startGrouwup(Text_btnDiamond, num, num2, 0.2, "",[this, grouwup](){
        //UIUtils::playInnerAction(FileNode_gold, "jump", false);
        grouwup->removeFromParent();
    });
}

void StoreView::updataBagNew()
{
    auto isPropNew = DATA_M->getIsPropNew();
    getNode("img_new_Bag")->setVisible(isPropNew);
}

void StoreView::showMiaoShu(bool isShow)
{
    FileNode_MiaoShu->setVisible(isShow);
}

void StoreView::updateMiaoShu()
{
    
    auto frontIdx = random(0, CARD_FACE_NUM-1); // DATA_M->getCardPicType(2);
    card_gold_fronts->setSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(13, 0, frontIdx));
    auto num =  13;
    auto _sprite1 = card_1->getChildByName<Sprite*>("Sprite_face");
    auto _sprite2 = _sprite1->getChildByName<Sprite*>("Sprite_num");
    auto _sprite3 = _sprite1->getChildByName<Sprite*>("Sprite_color");
    _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, 0, frontIdx));
    _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, 0, frontIdx));
    _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, 0, frontIdx));
    _sprite2->setColor(UIUtils::getCardColor(0));
    card_1->setPosition(card_gold_fronts->getContentSize()*0.5f);
    auto size2 = _sprite2->getContentSize();
    _sprite2->setPositionX(size2.width*0.5f);
    
    auto backIdx = random(0, CARD_BG_NUM-1); //DATA_M->getCardPicType(3);
    card_gold_bg->setSpriteFrame(SPRITE_M->getCardBgSpriteFrame(backIdx));
    
    //frontIdx = random(0, CARD_FACE_NUM-1);
    card_diamond_front->setSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(13, 0, frontIdx));
    
    

    _sprite1 = card_2->getChildByName<Sprite*>("Sprite_face");
    _sprite2 = _sprite1->getChildByName<Sprite*>("Sprite_num");
    _sprite3 = _sprite1->getChildByName<Sprite*>("Sprite_color");
    _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, 0, frontIdx));
    _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, 0, frontIdx));
    _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, 0, frontIdx));
    _sprite2->setColor(UIUtils::getCardColor(0));
    card_2->setPosition(card_diamond_front->getContentSize()*0.5f);
    size2 = _sprite2->getContentSize();
    _sprite2->setPositionX(size2.width*0.5f);
    
    //backIdx = random(0, CARD_BG_NUM-1);
    card_diamond_bg->setSpriteFrame(SPRITE_M->getCardBgSpriteFrame(backIdx));
    SpriteFrame* frame = nullptr;
    
    auto bgIdx = random(0, GAME_BG_NUM-1);//DATA_M->getCardPicType(1);
    if(bgIdx > 13)
    {//动态
        if(bgIdx<=16)
        {
            frame = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", 14-12),"car_new_0_1.atlas");
        }
        else
        {
            frame = AtlasManager::getInstance()->getSF(StringUtils::format("Map_%d", bgIdx-14),"car_new_0_1.atlas");
        }
    }
    else
    {
        frame = AtlasManager::getInstance()->getSF(1, 0, 0, bgIdx);
    }
    scene_diamond_bg->setSpriteFrame(frame);
}
