//
//  RewardNode.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/19.
//

#include <stdio.h>
#include "RewardNode.h"
#include "RewardManager.h"
#include "MainLobby.h"
#include "SceneManager.h"
#include "SceneManager.h"
RewardNode::RewardNode(GameBackground::RewardType rewardType,int rewardNum)
:BaseLayer("Animation/Node_currency.csb")
,_rewardType(rewardType)
,_rewardNum(rewardNum)
{
    isTouch = false;
}

RewardNode::~RewardNode()
{
    
}

void RewardNode::updateUI()
{
    
}

void RewardNode::initUI()
{
    BaseLayer::initUI();
    showReward();
    
    schedule([this](float dt){
        if(isTouch)
        {
            isTouch = false;
            hideReward();
        }
    },10, "scheduler_update_bar");
}
void RewardNode::initData()
{
    BaseLayer::initData();
}
void RewardNode::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;

    auto btnName = btn->getName();
}

void RewardNode::showReward()
{
    switch (_rewardType) {
        case GameBackground::RewardType::GOLD:
        {
            playAni("GoldJump",false,[this](){
                //playAni("Gold",true);
                isTouch = true;
                hideReward();
            });
        }
            break;
        case GameBackground::RewardType::EXP:
        {
            playAni("ExpJump",false,[this](){
                //playAni("Exp",true);
                isTouch = true;
                hideReward();
            });
        }
            break;
        case GameBackground::RewardType::MAGIC:
        {
            playAni("MagicJump",false,[this](){
                //playAni("Magic",true);
                isTouch = true;
                hideReward();
            });
        }
            break;
        default:
            break;
    }
    
    
}

void RewardNode::hideReward()
{
    isTouch = false;
    //出现奖励
    auto lobby = SCENE_M->getLobby();
    auto startPoi = this->getPosition();
    //startPoi = this->convertToWorldSpace(startPoi);
    switch (_rewardType) {
        case GameBackground::RewardType::GOLD:
        {
            lobby->rewardGold(_rewardNum, startPoi);
        }
            break;
        case GameBackground::RewardType::EXP:
        {
            lobby->rewardExp(_rewardNum, startPoi);
        }
            break;
        case GameBackground::RewardType::MAGIC:
        {
            lobby->rewardMagic(_rewardNum, startPoi);
        }
            break;
        default:
            break;
    }
    //setVisible(false);
    this->removeFromParent();
}

Rect RewardNode::getWorldRect()
{
    auto rect = getRewardRect();
    rect.origin = this->convertToWorldSpace(rect.origin);
    return rect;
}

Rect RewardNode::getRewardRect()
{
    Node* node;
    switch (_rewardType) {
        case GameBackground::RewardType::GOLD:
            node = getNode("Sprite_2");
            break;
        case GameBackground::RewardType::EXP:
            node = getNode("Sprite_3");
            break;
        case GameBackground::RewardType::MAGIC:
            node = getNode("Magic_0_1");
            break;
        default:
            break;
    }
    auto rect = node->getBoundingBox();
    return rect;
}
