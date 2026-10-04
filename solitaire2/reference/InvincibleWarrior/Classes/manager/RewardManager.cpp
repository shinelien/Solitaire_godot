//
// Created by Cyutao on 2019-07-12.
//

#include "RewardManager.h"
#include "base/CCUserDefault.h"
#include "Currency.h"
#include "EventObserver.h"
#include <ctime>
#include "UIUtils.h"
#include "DataManager.h"
#include "NpcSprite.h"
#include "StarNode.h"
using namespace std;
USING_NS_CC;

RewardManager* RewardManager::s_instance = nullptr;
RewardManager *RewardManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new RewardManager();
        s_instance->init();
    }
    return s_instance;
}

RewardManager::RewardManager() {
    multipleNum = GETINTEGER("multipleNum",0);
    isLianXu = GETBOOL("isLianXuMultiple",true);
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, [this](void*){
        Currency::getCache()->myInit(150);
        NpcSprite::getCache()->myInit(100);
        StarNode::getCache()->myInit(5);
    }, nullptr, []{});
    
    //金币与钻石音效id
    effGId = -1;
    effDId = -1;
}
RewardManager::~RewardManager()
{
    Currency::deleteCache();//清空
    
    NpcSprite::deleteCache();
    StarNode::deleteCache();
}

void RewardManager::init() {

}

void RewardManager::getReward(RewardManager::RewardType type, int count, bool notify) {
    if (type == RewardType::Gold) {
        DATA_M->setCoinNum(count,false,104);
        //更新有金币显示
        EVENT_M->sendEvent("event_game_update_coin");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("event_game_update_coin",(void*)false);
    }
//    else if(type == RewardType::ZuanShi)
//    {
//        DATA_M->setDiamond(count,false);
//    }
    else if (type == RewardType::PokerFace) {
        DATA_M->unLockShopItemStatus(3,random(4, CARD_BG_NUM-1));
    }
    else if(type == RewardType::Magic)
    {//50个上限
        auto cnt = getCNT(type);
        auto num = MIN(cnt + count,50);
        UserDefault::getInstance()->setIntegerForKey(getKey(type).c_str(), num);
    }
    else {
        auto cnt = getCNT(type);
        UserDefault::getInstance()->setIntegerForKey(getKey(type).c_str(), cnt+count);
    }
    if (notify)
        EVENT_M->sendEvent("reward_item_update");
        //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("reward_item_update");
}

int RewardManager::getCNT(RewardManager::RewardType type) {
    return MAX(0, UserDefault::getInstance()->getIntegerForKey(getKey(type).c_str(), 3));
}

int RewardManager::useItem(RewardManager::RewardType type, int count) {
    auto cnt = getCNT(type);
    auto lastCNT = MAX(0, cnt-count);
    UserDefault::getInstance()->setIntegerForKey(getKey(type).c_str(), lastCNT);
    EVENT_M->sendEvent("reward_item_update");
    //Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("reward_item_update");
    return lastCNT;
}

std::string RewardManager::getKey(RewardManager::RewardType type) {
    return StringUtils::format("reward_%d_key", (int)type);
}

void RewardManager::updateMultipleNum()
{
    multipleNum--;
    if(multipleNum < 0)
    {
        multipleNum = random(3, 6);
        //重置了 第一次还是7倍
        isLianXu = true;
    }
    else
    {
        isLianXu = false;
    }
    SETBOOL("isLianXuMultiple",isLianXu);
    SETINTEGER("multipleNum",multipleNum);
    FLUSH();
}

int RewardManager::getMultipleNum()
{
    return multipleNum;
}

bool RewardManager::getis7Multiple()
{
    return isLianXu;
}


void RewardManager::rewardItemAction(int num,Vec2 targetPoi,Vec2 startPoi,std::vector<Vec2> itemVec,std::function<void()> itemCB,std::string aniName,Node* parent,std::function<void()> itemEnd,std::function<void()> itemEnd2)
{//node的个数。目标点坐标 自身出现的坐标
    if(num <= 0)return;
    //判断数目
    bool is = true;
    
    if(num > 14)
    {
        is = false;
    }
    float gdTime = 0;
    float timeMax = 0.75;
    
    float time = gdTime;
    //auto time2 = 0;
    for(int i= 0;i<num;++i)
    {
        time+=0.05;//13 65  14 7 15 7.5  num == 14时间最多
        if(time >= timeMax)
        {
            time = gdTime;
        }
        int z = random(102, 105);
        auto expNode =Currency::getCache()->createCacheNode(parent);//UIUtils::createCSBNode("Animation/Node_currency.csb");
        //parent->addChild(expNode,z);
        expNode->setLocalZOrder(z);
        expNode->setPosition(startPoi);//目前在屏幕中心
        expNode->setVisible(false);
        auto delay = DelayTime::create(time);//0.75 0.2 1.5
        auto delay2 = DelayTime::create(0);
        auto moBy = MoveBy::create(0.4f, itemVec[i]);
        auto cubicOut = EaseCubicActionOut::create(moBy);
        auto moTo = MoveTo::create(1.5, targetPoi);
        auto quarticIn = EaseQuarticActionIn::create(moTo);

        auto remo = RemoveSelf::create();
        
        auto func = CallFunc::create(itemCB);
        auto func2 = CallFunc::create([expNode,aniName](){
            expNode->setVisible(true);
//            auto ani = dynamic_cast<cocostudio::timeline::ActionTimeline*>(expNode->getActionByTag(10086));
//            ani->play(aniName, true);
            expNode->playAni(aniName, true);
            //经验跳出
            if(aniName == "Exp")
            {
                SOUND_M->playEffectMusic(EffectGetFly);
            }
        });
        
        auto funcEffe = CallFunc::create([this,aniName](){
            //金币与钻石音效
            //15个声音
            
            if(aniName == "Gold")
            {
                if(effDId != -1)
                {
                    SOUND_M->stopEffectMusic(effDId);
                }
                effDId = SOUND_M->playEffectMusic(EffectGetCoin);
            }
            else if(aniName == "Baoshi"||aniName == "Activity")
            {
                if(effGId != -1)
                {
                    SOUND_M->stopEffectMusic(effGId);
                }
                effGId = SOUND_M->playEffectMusic(EffectGetGem);
            }
        });
        
        auto funcjump = CallFunc::create([this,aniName](){
            
            if(aniName == "Gold"||aniName == "Baoshi")
            {
                SOUND_M->playEffectMusic(EffectGetAll);
            }
            
        });
        auto funcEnd = CallFunc::create(itemEnd);
        auto funcEnd2 = CallFunc::create(itemEnd2);
        
        if(i == 0)
        {
            Sequence* seq = nullptr;
            if(is||i%2 == 0)
            {//有音效
                seq = Sequence::create(delay,func2,funcjump,cubicOut,delay2, quarticIn,func,funcEnd,funcEffe,remo, NULL);
            }
            else
            {//无音效
                seq = Sequence::create(delay,func2,funcjump,cubicOut,delay2, quarticIn,func,funcEnd,remo, NULL);
            }
            auto speed = Speed::create(seq, FLYSPEED);
            expNode->runAction(speed);
        }
        else if((i == num - 1&&num < 15)||i == 13)
        {
            Sequence* seq = nullptr;
            
            seq = Sequence::create(delay,func2,cubicOut,delay2, quarticIn,funcEnd2,remo, NULL);
            auto speed = Speed::create(seq, FLYSPEED);
            expNode->runAction(speed);
        }
        else
        {
            Sequence* seq = nullptr;
            if(aniName == "Gold")
            {
                if(i <= 30&&(i%2 == 0||is))
                {//有音效
                    seq = Sequence::create(delay,func2,cubicOut,delay2, quarticIn,funcEnd,funcEffe,remo, NULL);
                }
                else
                {//无音效
                    seq = Sequence::create(delay,func2,cubicOut,delay2, quarticIn,funcEnd,remo, NULL);
                }
            }
            else if(aniName == "Baoshi"||aniName == "Activity")
            {
                if(i <= 30&&(i%2 == 1||is))
                {//有音效
                    seq = Sequence::create(delay,func2,cubicOut,delay2, quarticIn,funcEnd,funcEffe,remo, NULL);
                }
                else
                {//无音效
                    seq = Sequence::create(delay,func2,cubicOut,delay2, quarticIn,funcEnd,remo, NULL);
                }
            }
            else
            {
                
                seq = Sequence::create(delay,func2,cubicOut,delay2, quarticIn,funcEnd,remo, NULL);
                
            }
            
            auto speed = Speed::create(seq, FLYSPEED);
            expNode->runAction(speed);
        }
    }
}
