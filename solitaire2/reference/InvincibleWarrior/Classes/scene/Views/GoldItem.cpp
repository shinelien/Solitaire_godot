//
//  GoldItem.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/25.
//

#include <stdio.h>
#include "GoldItem.h"
#include "RewardManager.h"
#include "MainLobby.h"
#include "DataManager.h"
#include "GameViewHD.hpp"
#include "RankFashTank.h"
#include "ScoreManager.h"
#include "RankManager.hpp"
#include "GoldShop.h"
#include "PlayerManager.h"
#include "ShopManager.h"
#include "TaskManager.h"
#include "SubscriptionView.h"

GoldItem::GoldItem(GoldShop* goldShop)
:BaseLayer("2021GoldItem.csb")
,_goldShop(goldShop)
{
    
}

GoldItem::~GoldItem()
{
    
}
    
GoldItem * GoldItem::createBagNode(int idx,GoldShop* goldShop)
{
    auto bagNode = GoldItem::createLayerN(goldShop);
    bagNode->setShopNodeState(idx);
    return bagNode;
}
void GoldItem::setShopNodeState(int idx)
{
    _idx = idx;
    auto noAds = false; // !DATA_M->isVipNoAds();

    vector<string> textVec{
        "100355",
        "100286",
        "100286",
        "100356",
        "100356",
        "100356",
        "100357",
        "100357",
    };

    if(!noAds)
    {
        Image_Gold->setVisible(true);
        Sprite_HOT->setVisible(idx >= 0&&idx <= 4);
        if(idx+1 < textVec.size())
        {
            getNode<Text*>("Text_miaoShu")->setString(Lang(textVec.at(idx+1)));
        }
        if(idx+1 < _nodeVec.size())
        {
            _nodeVec.at(idx+1)->setVisible(true);
        }
    }
    else
    {
        _nodeVec.at(idx)->setVisible(true);
        Image_Gold->setVisible(idx != 0);
        Sprite_HOT->setVisible(idx >= 1&&idx <= 5);
        getNode<Text*>("Text_miaoShu")->setString(Lang(textVec.at(idx)));
    }

    updateUI();
}

void GoldItem::initUI()
{
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);
    Image_Gold = getNode("Image_Gold");
    Sprite_HOT = getNode<Sprite*>("Sprite_HOT");
    
    for(int i = 0;i < 8;++i)
    {
        if(i == 0)
        {
            auto node = getNode("Node_noAds");
            node->setVisible(false);
            _nodeVec.pushBack(node);
        }
        else
        {
            auto node = getNode(StringUtils::format("Node_gold_%d",i));
            node->setVisible(false);
            _nodeVec.pushBack(node);
        }
    }
    
    //setContentSize(Size(640, 200));
}
void GoldItem::initData()
{
    BaseLayer::initData();
    
}

void GoldItem::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;

    auto btnName = btn->getName();
    
    if(btnName == "Button_goldItem" || btnName == "Button_buy")
    {//
//        auto noAds = !DATA_M->isVipNoAds();
//        if(_idx == 0&&noAds)
//        {
//            SCENE_M->addDialog(SubscriptionView::createLayerN());
//            _goldShop->removeFromParent();
//        }
//        else
//        {
            UIUtils::calIAP(_product->getID());
//        }
    }
}

void GoldItem::updateUI()
{
    vector<int> goldNumVec{
        0,
        240,
        720,
        1320,
        2880,
        6240,
        13440,
        28800,
    };
    
    vector<string> priceNumVec{
        "4.99",
        "0.99",
        "2.99",
        "4.99",
        "9.99",
        "19.99",
        "39.99",
        "79.99",
    };
    const auto& products = RankManager::getInstance()->getProducts();
    _product = products.at(_idx);
    getNode<TextBMFont*>("BitmapFontLabel_num")->setString(toString(_product->getPrice()));
    getNode<TextBMFont*>("BitmapFontLabel_buy")->setString(_product->getShowStr());
    getNode<Text*>("Text_fuHao")->setString(_product->getCurrencyCode());
}

