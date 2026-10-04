//
//  FashTankItem.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/18.
//

#include <stdio.h>
#include "FashTankItem.h"
#include "RewardManager.h"
#include "MainLobby.h"
#include "DataManager.h"
#include "GameViewHD.hpp"
#include "RankFashTank.h"
#include "ScoreManager.h"
#include "RankManager.hpp"
#include "FashTankShop.h"
#include "PlayerManager.h"
#include "ShopManager.h"
#include "TaskManager.h"
#include "NpcSprite.h"
#include "FishManager.h"
#include "FishGuideManager.h"

FashTankItem::FashTankItem(FashTankShop* fishShop)
:BaseLayer("2021FashTankItem.csb")
,_fishShop(fishShop)
{
    
}

FashTankItem::~FashTankItem()
{
    
}
    
FashTankItem * FashTankItem::createBagNode(int idx,FashTankShop* fishShop)
{
    auto bagNode = FashTankItem::createLayerN(fishShop);
    bagNode->setShopNodeState(idx);
    return bagNode;
}
void FashTankItem::setShopNodeState(int idx)
{
    _idx = idx;
    _isTouch = true;
    if(_idx == 1&&!GUIDE_M->isEnd(FishGuideManager::GuideType::UseFashTank,0)&&GUIDE_M->isEnd(FishGuideManager::GuideType::ClickFashTank,0))
    {//正在进行买鱼引导
        _isTouch = false;
    }
    auto node1 = getNode("fish_Aquarium1_0");
    auto node2 = getNode("fish_Aquarium2_0");
    auto node3 = getNode("fish_Aquarium3_0");
    node1->setLocalZOrder(2000);
    node2->setLocalZOrder(2000);
    node3->setLocalZOrder(0);
    node1->setVisible(idx == 0);
    node2->setVisible(idx == 0);
    node3->setVisible(idx == 0);
    //展示图
    Node* node;
    for(int i = 0;i < 4;++i)
    {
        auto item = getNode(StringUtils::format("Node_fashTank_%d",i));
        item->setVisible(i == idx);
        if(i == idx)
        {
            node = item->getChildByName("fish_Aquarium");
        }
    }
    auto isNew = DATA_M->getFashTankNew(idx);
    getNode("img_new_bg")->setVisible(isNew);
    auto lv = PlayerManager::getInstance()->getLevel();
    auto unLockLv = ShopManager::getInstance()->getFashTankUnlockLv(idx);
    isUnlock = lv >= unLockLv;
    //35%透明度
    //纯黑
    
    auto isUse = DATA_M->getCurrentFashTankIdx() == idx;
    //锁着的时候或者没有被使用
    auto isE = !isUnlock||!isUse;
    
    getNode<Button*>("Button_fashTank")->setEnabled(isE);
    getNode("BitmapFontLabel_npc_num")->setVisible(isUnlock);
    getNode("Text_name")->setVisible(isUnlock);
    getNode("Image_fish")->setVisible(isUnlock);
    //UIUtils::playInnerAction(node,StringUtils::format("idle%d",(int)lvVec.size()-2),false);
    getNode("ui_Lock0_Changjing_0_0")->setVisible(!isUnlock);
    //getNode<Button*>("Button_fashTank")->setEnabled(isUnlock);
    getNode<Button*>("Button_goFashTank")->setVisible(isUnlock);
    getNode<Button*>("Button_guanLi_0")->setVisible(isUnlock);
    
    //Panel_unlock->setVisible(!isUnlock);
    
    auto num = DATA_M->getFishNum(idx);
    getNode<TextBMFont*>("BitmapFontLabel_fishNum")->setString(StringUtils::toString(unLockLv));
    getNode<TextBMFont*>("BitmapFontLabel_min")->setString(StringUtils::toString(num));
    getNode<TextBMFont*>("BitmapFontLabel_max")->setString(StringUtils::toString(FISH_MAX_NUM));
    
    auto Text_unlock = getNode<Text*>("Text_lv_miaoshu");
    Text_unlock->setString(StringUtils::format(Lang("100347").c_str(),unLockLv));
    UIUtils::textAdaptiveSize(Text_unlock, 410);
    getNode<Text*>("Text_lv_str")->setString(Lang("100200"));
    vector<string> strVec{
        "100367",
        "100368",
        "100369",
        "100370",
    };
    getNode<Text*>("Text_name")->setString(Lang(strVec.at(idx)));
    getNode<TextBMFont*>("Text_unlockLv")->setString(StringUtils::toString(unLockLv));
    getNode<Text*>("Text_2")->setString(Lang("100354"));
    
    updateUI();
    
    //得到三个路径
    if(isUnlock)
    {
        //人数公式（鱼缸里的所有鱼等级相加）/5.6
        //人数公式（鱼缸里的所有鱼等级相加）/5.6=结果（四舍五入取整得出人数
        auto vec = DATA_M->getFishTypeVec(_idx);
        auto fishManager = FishManager::getInstance();
        int maxLv = 0;
        float num = 0;
        for(int i = 0;i < vec.size();++i)
        {
            auto fishId = vec.at(i);
            auto lv = fishManager->getUnlockLv(fishId);
            maxLv += lv;
            float f = fishManager->getNpcNum(fishId);
            auto str = UIUtils::getFloatStr(f,1);
            f = std::stof(str);
            num = num + f;
        }
        //auto num = (float)maxLv/NPC_NUM;
        float num2 = num;
        if(num > 0&& num < 1)
        {
            num = 1;
        }
        else if(num > 13)
        {
            num = 13;
        }
        else
        {
            num = std::round(num);
        }
        vector<Vector<Node*>> pathVec;
        for(int i = 0;i < 2;++i)
        {
            auto node_path = getNode(StringUtils::format("Node_path_%d_%d",_idx,i));
            auto size = node_path->getChildren().size();
            Vector<Node*> vec;
            for(int j = 0;j < size;++j)
            {
                auto path = node_path->getChildByName(StringUtils::format("Node_path%d",j));
                vec.pushBack(path);
            }
            pathVec.push_back(vec);
        }
        //随便选一条给他
        bool isHide = num > 6;
        int num0 = 0;
        auto parent = getNode("Node_fashTank");
        for(int i = 0;i < num;++i)
        {
            auto npc = NpcSprite::getCache()->createCacheNode(parent);
            npc->setLocalZOrder(1);
            auto rand = random(0, 1);
            if(rand == 0)
            {
                num0++;
            }
            if(num0 > num/3)
            {
                rand = 1;
            }
            auto vec = pathVec.at(rand);
            npc->setPath(vec,rand,isHide);
        }
        auto str = UIUtils::getFloatStr(num2,1);
        getNode<TextBMFont*>("BitmapFontLabel_npc_num")->setString(str);
    }
    else
    {
        node->setColor(Color3B::BLACK);
        node->setOpacity(255*0.35f);
    }
}

void FashTankItem::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    
    Sprite_used_bg = getNode("Sprite_used_bg");
    //Panel_unlock = getNode("Panel_unlock");
}
void FashTankItem::initData()
{
    BaseLayer::initData();
    
    
    addEvent("shop_item_fashTank_select", [this](EventCustom* event){
        auto obj = event->getUserData();
        if(obj == this)
        {
        }
        
        selected(obj == this);
    });
    
}

void FashTankItem::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn||!_isTouch)return;

    auto btnName = btn->getName();
    
    if(btnName == "Button_fashTank"||btnName == "Button_goFashTank")
    {//
        if(isUnlock)
        {
            if(_idx == 1&&GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::UseFashTank)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::UseFashTank,0))
            {//正在进行买鱼引导
                //GUIDE_M->nextGuide(FishGuideManager::GuideType::GetFishOne);
                GUIDE_M->endGuide(FishGuideManager::GuideType::None,NULL,0);
            }
            _fishShop->setFashTankIdx(_idx);
        }
        
        //getEventDispatcher()->dispatchCustomEvent("shop_item_fashTank_select", (void*)this);
    }
    else if(btnName == "Button_guanLi_0")
    {
        _fishShop->toFish(_idx);
    }
}

void FashTankItem::updateUI()
{
    auto isUse = DATA_M->getCurrentFashTankIdx() == _idx;
    Sprite_used_bg->setVisible(isUse);
}

void FashTankItem::selected(bool flag)
{
    if(flag)
    {
        TASK_M->addTaskNum((int)TaskManager::NewbieTaskType::GAMEBG);
    }
    updateUI();
}
void FashTankItem::setIsTouch(bool isTouch)
{
    _isTouch = isTouch;
}
