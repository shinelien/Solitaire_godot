//
//  LevelUpView.cpp
//  
//
//  Created by lien on 2020/3/29.
//

#include <stdio.h>
#include "LevelUpView.h"
#include "SceneManager.h"
#include "GameBackground.h"
#include "PlayerManager.h"
#include "FishManager.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#include "ShopManager.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "FishGuideManager.h"
#include "ScoreManager.h"
#include "PlayerManager.h"
LevelUpView::LevelUpView()
:BaseLayer("2020Levelup.csb")
{
    isQieHuan = false;
    isBar = false;
    lv = 0;
    oldLv = 0;
    dLv = 0;
    percent1 = 0;
    percent2 = 0;
    percentDx = 0;
    unlockLv = -1;
    isUnlock = false;
    isUp = false;
}
LevelUpView::~LevelUpView()
{
    
}
    
void LevelUpView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    vector<string> peiShiNameVec0{
        "scence1_1.png",
        "scence1_2.png",
        "scence1_3.png",
        "scence1_5.png",
        "scence1_4.png",
    };
    
    vector<string> peiShiNameVec1{
        "scence2_01.png",
        "scence2_02.png",
        "scence2_03.png",
        "scence2_06.png",
        "scence2_04.png",
        "scence2_05.png",
    };
    
    vector<string> peiShiNameVec2{
        "qianting1.png",
        "lunzi/0002.png",
        "qianting2.png",
        "qianting3.png",
        "qianting4.png",
        "qianting5.png",
        "qianting0.png",
    };
    
    vector<string> peiShiNameVec3{
        "sce4/ailisi1.png",
        "sce4/ailisi0.png",
        "sce4/ailisi3.png",
        "sce4/ailis2.png",
        "sce4/ailisi5.png",
        "sce4/ailisi4.png",
        "sce4/ailisi6.png",
        "sce4/ailisi8.png",
        "sce4/ailisi7.png",
    };
    
    peishiVec.push_back(peiShiNameVec0);
    peishiVec.push_back(peiShiNameVec1);
    peishiVec.push_back(peiShiNameVec2);
    peishiVec.push_back(peiShiNameVec3);
    
    Node_jianTou = getNode("Node_jianTou");
    Node_fish = getNode("Node_fish");
    loadingBar_percent = getNode<LoadingBar*>("LoadingBar_1");
    LoadingBarWidth = loadingBar_percent->getBoundingBox().size.width;
    
    Sprite_BG = getNode<Sprite*>("BG");
    //当前等级
    Label_Lv0 = getNode<TextBMFont*>("Label_Lv0");
    Label_Lv1 = getNode<TextBMFont*>("Label_Lv1");
    Label_Lv2 = getNode<TextBMFont*>("Label_Lv2");
    Label_Lv3 = getNode<TextBMFont*>("Label_Lv3");
    //等级
    for(int i = 0;i < 4;++i)
    {
        _LvBgVec.pushBack(getNode(StringUtils::format("LevelBg_%d",i)));
        _LabelVec.pushBack(getNode<TextBMFont*>(StringUtils::format("Label_Lv%d",i)));
    }
    
    //经验
    schedule([this](float dt){
        if(isBar)
        {
            if(lv > oldLv)
            {// lv > oldLv 从percent2涨到100;再从0涨到percent1
                percent2+=percentDx/0.03f * dt;
                if(percent2 > percent1)
                {
                    percent2 = percent1;
                    isBar = false;
                    //升级了，看看解没解锁
                    if(_idx != -1)//fishId != -1&&lv >= unlockLv)
                    {//解锁啦
                        playAni("lock",false);
                    }
                    else
                    {
                        //显示按钮
                        playAni("out0",false);
                    }
                }
                loadingBar_percent->setPercent(percent2);
            }
        }
        else
        {
            dLv = 0;
        }
    },0.03f, "scheduler_update_bar");
    
    
    updateDYY();
    updateUI();
}
void LevelUpView::initData()
{
    BaseLayer::initData();
    
}
void LevelUpView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "Button_get")
    {//
        if(_cb) _cb();
        auto lobby = SCENE_M->getLobby();
        auto gameView = SCENE_M->getGameView();
        gameView->showChallenge();
        if(_rewardType == RewardType::Fish)
        {
            fishMove();
            auto winNum = ScoreManager::getInstance()->getWinTotalCNT(true);
            auto num = ScoreManager::getInstance()->getWinTotalCNT();
            if(!GUIDE_M->isEnd(FishGuideManager::GuideType::Three)&&winNum == 1&&num != 4)
            {
                auto poi = gameView->getPauseWorldPoi();
                auto scale = gameView->getNode("FileNode_2020Menu")->getScale();
                GUIDE_M->startGuide(FishGuideManager::GuideType::Three,gameView,poi,scale);
            }
            else if(isUp&&DATA_M->getIsFashTankNuw())
            {
                
                lobby->updateFashTankNewTips();
                auto lv = PlayerManager::getInstance()->getLevel();
                auto isFishNew = DATA_M->getIsFashTankNuw();
                if(!GUIDE_M->isEnd(FishGuideManager::GuideType::unlockFashTank,0)&&lv == 18&&isFishNew)
                {//18级了 可以提示了
                    auto gameView = SCENE_M->getGameView();
                    auto poi = gameView->getPauseWorldPoi();
                    auto scale = gameView->getNode("FileNode_2020Menu")->getScale();
                    GUIDE_M->startGuide(FishGuideManager::GuideType::unlockFashTank,gameView,poi,scale,0);
                }
            }
        }
        if(isUp&&DATA_M->getIsFashTankNuw()&&!DATA_M->getIsFishNuw())
        {
            
            lobby->updateFashTankNewTips();
        }
        if(isUp&&DATA_M->getIsPropNew())
        {
            
            lobby->updataBagNew();
        }
        
        this->setVisible(false);
    }
    else if(btnName == "Button_ok")
    {//直接隐藏了
        if(_cb) _cb();
        auto gameView = SCENE_M->getGameView();
        gameView->showChallenge();
        if(isUp&&DATA_M->getIsPropNew())
        {
            auto lobby = SCENE_M->getLobby();
            lobby->updataBagNew();
        }
        this->setVisible(false);
    }
}

void LevelUpView::updateReward(int ulv)
{
    vector<string> imageNameVec{
        "BeiJing11.jpg",
        "BeiJing10.jpg",
        "BeiJing1.jpg",
        "BeiJing2.jpg",
    };
    auto shopManager = ShopManager::getInstance();
    //看看有没有
    
    //Sprite_BG->setSpriteFrame(Sprite::create(imageNameVec.at(maxidx))->getSpriteFrame());
    
    //找一下 该到那条鱼了
    fishId = -1;
    Node_fish->removeAllChildren();
    
    auto rewardIdx = -1;
    
    if(false&&_idx != -1)
    {
        rewardIdx = _idx / 10000;
    }
    else
    {
        if(_lvVec.size() > 0)
        {
            auto lv = -1;
            for(int i = 0;i < _lvVec.size();++i)
            {
                auto tempLv = _lvVec.at(i);
                if(lv < tempLv)
                {
                    lv = tempLv;
                }
            }
            //ulv - lv
            int maxLv = -1;
            int i = ulv > lv?lv:ulv;
            for(;i <= lv;++i)
            {
                auto vec = shopManager->getLvUnlock(i);
                if(vec.size() != 0&&vec.at(0) == 0)
                {
                    rewardIdx = vec.at(0);
                    maxLv = i;
                    break;
                }
            }
            
            if(maxLv != -1)
            {
                
            }
        }
    }
    
    if(rewardIdx == 0)
    {//是鱼
        //得到前一个鱼的解锁等级
        auto oldUnlockLv = 0;
        //得到目前需要解锁鱼的等级
        auto currentUnlockLv = 1;
        
        for(int i = 0;i < FISH_NUM;++i)
        {
            auto idx = newShopIdx[i];
            unlockLv = FISH_M->getUnlockLv(idx);
            if(unlockLv <= oldLv)
            {
                oldUnlockLv = unlockLv;
            }
            else if(unlockLv > oldLv)
            {//嗯 这个没解锁呢
                currentUnlockLv = unlockLv;
                fishId = idx;
                break;
            }
        }
        
        if(fishId != -1)
        {
            _rewardType = RewardType::Fish;
            _skeletonNode = FISH_M->getFishSpine(fishId);
            Node_fish->addChild(_skeletonNode);
            string aniName = "Run";
            
            _skeletonNode->setAnimation(0, aniName, true);
            if(fishId == 14)
            {
                _skeletonNode->setPositionX(466.55f * 0.1f);
                _skeletonNode->setScale(0.85f);
            }
            if(unlockLv > lv)
            {
                _skeletonNode->setColor(FishUnlockColor);
            }
        }
    }
//    else if(rewardIdx == 1)
//    {//鱼缸
//        if(lockLv > oldLockLv)
//        {
//            _rewardType = RewardType::FashTank;
//            Sprite_reward->setVisible(true);
//            Sprite_reward->setSpriteFrame(peishiVec.at(maxidx).at(lockLv-1));
//        }
//    }
    
}

void LevelUpView::updateReward()
{
    
}

void LevelUpView::setData(int lv,int oldLv,float percent1,float percent2,float percentDx,std::function<void()> cb)
{
    if(lv == oldLv) return;
    Node_jianTou->setVisible(true);
    isQieHuan = false;
    //isBar = false;
    this->lv = lv;
    this->oldLv = oldLv;
    dLv = 0;
    
    
    _idxVec.clear();
    _rewardType = RewardType::None;
    
    auto shopManager = ShopManager::getInstance();
    auto playerManager = PlayerManager::getInstance();
    
    auto str = playerManager->getPartLv(oldLv);
    auto strVec = UIUtils::split(str, "-");
    
    _lvVec.clear();
    //给进度条分段
    auto num = strVec.size()-1;//currentUnlockLv-oldUnlockLv;
    auto tempMaxLv = -1;
    for(int i = 0;i < 4;++i)
    {
        auto templv = 0;
        if(i < strVec.size())
        {
            templv = std::stoi(strVec.at(i));
        }
        if(templv > tempMaxLv)
        {
            tempMaxLv = templv;
        }
        _lvVec.push_back(templv);
    }
    
    int minLv = lv > tempMaxLv?tempMaxLv:lv;
    rewardVec = shopManager->getLvUnlock(minLv);
    //添加当前奖励
    for(int i = rewardVec.size() - 1;i >= 0;--i)
    {
        auto type = rewardVec.at(i);
        
        if(type == 2)continue;
        auto rewardIdx = type * 10000;
        auto rewardLv = lv;
        auto idx = rewardIdx + rewardLv;
        _idxVec.push_back(idx);
    }
    _idx = -1;
    
    if(_idxVec.size() > 0)
    {
        _idx = _idxVec.at(_idxVec.size()-1);
        if(_idx >= 10000)
        {
            _idx = -1;
        }
        _idxVec.pop_back();
    }
    updateReward(lv);
    for(int i = 0;i < rewardVec.size();++i)
    {
        auto type = rewardVec.at(i);
        if(type == 0&&fishId != -1)
        {//有解锁的鱼
            //type 转商店idx
            auto shopIdx = newShopTipsIdx[fishId];
            DATA_M->setFishNew(shopIdx,1);
        }
        else if(type == 1)
        {//有解锁的鱼缸
            auto maxidx = shopManager->getMaxFashTankIdx(lv);
            DATA_M->setFashTankNew(maxidx,1);
        }
        else if(type == 2)
        {//有解锁的道具
            auto cardBgId = shopManager->getlvProp(3,lv);
            auto musicId = shopManager->getlvProp(5,lv);
            if(cardBgId!=-1)
            {
                DATA_M->setPropNew(3, cardBgId,1);
            }
            if(musicId != -1)
            {
                DATA_M->setPropNew(5, musicId,1);
            }
        }
    }
    
//    if(oldLv < 3)
//    {
//        _lvVec.push_back(0);
//        _lvVec.push_back(1);
//        _lvVec.push_back(2);
//        _lvVec.push_back(3);
//    }
//    else
//    {
//        auto n = oldLv % 3;
//
//        if(n == 0)
//        {
//            _lvVec.push_back(oldLv + 0);
//            _lvVec.push_back(oldLv + 1);
//            _lvVec.push_back(oldLv + 2);
//            _lvVec.push_back(oldLv + 3);
//        }
//        else if(n == 1)
//        {
//            _lvVec.push_back(oldLv - 1);
//            _lvVec.push_back(oldLv + 0);
//            _lvVec.push_back(oldLv + 1);
//            _lvVec.push_back(oldLv + 2);
//        }
//        else if(n == 2)
//        {
//            _lvVec.push_back(oldLv - 2);
//            _lvVec.push_back(oldLv - 1);
//            _lvVec.push_back(oldLv + 0);
//            _lvVec.push_back(oldLv + 1);
//        }
//    }

    
    for(int i = 0;i < 4;++i)
    {
        auto node = _LvBgVec.at(i);
        auto label = _LabelVec.at(i);
        auto lv = _lvVec.at(i);
        for(int j = 0;j < 3;++j)
        {
            
            auto vec = shopManager->getLvUnlock(lv);
            auto sprite = node->getChildByName(StringUtils::format("reward_%d",j));
            if(i != 0&&vec.size() != 0&&j == 0)
            {
                
                sprite->setVisible(vec.at(0) == j);
            }
            else
            {
                sprite->setVisible(false);
            }
            
        }
        
        if(i <= num)
        {
            node->setVisible(true);
            //设置位置
            
            auto x = LoadingBarWidth/num * i;
            node->setPositionX(x);
            //等级文本
            label->setString(StringUtils::format("%d",lv));
        }
        else
        {
            node->setVisible(false);
        }
        
    }
    
    //当前在哪段
    float percent = 0;
    float fn = 1.0f;
    int dn = _lvVec.at(1) - _lvVec.at(0);
    int dn2 = 0;
    int lv0 = _lvVec.at(0);
    int lv1 = _lvVec.at(1);
    int lv2 = _lvVec.at(2);
    int lv3 = _lvVec.at(3);
    if(num == 1)
    {
        percent = 0;
        fn = 1.0f;
    }
    else if(num == 2)
    {
        fn = 2.0f;
        if(oldLv >= _lvVec.at(0)&&oldLv < _lvVec.at(1))
        {
            dn = lv1-lv0;
            dn2 = oldLv - lv0;
            percent = 0;
        }
        else if(oldLv >= _lvVec.at(1)&&oldLv < _lvVec.at(2))
        {
            dn = lv2-lv1;
            dn2 = oldLv - lv1;
            percent = 100.0f / fn;
        }
        if(dn > 1)
        {//当前等级在哪个分段
            float f = 100.0f / fn;
            auto p = dn2 * f / dn;
            percent += p;
        }
        
    }
    else if(num == 3)
    {
        fn = 3.0f;
        //12 - 14 - 16 - 18
        if(oldLv >= _lvVec.at(0)&&oldLv < _lvVec.at(1))
        {
            dn = lv1-lv0;
            dn2 = oldLv - lv0;
            percent = 0;
        }
        else if(oldLv >= _lvVec.at(1)&&oldLv < _lvVec.at(2))
        {
            dn = lv2-lv1;
            dn2 = oldLv - lv1;
            percent = 100.0f / fn;
        }
        else if(oldLv >= _lvVec.at(2)&&oldLv < _lvVec.at(3))
        {
            dn = lv3-lv2;
            dn2 = oldLv - lv2;
            percent = 100.0f * 2.0f / fn;
        }
        if(dn > 1)
        {//当前等级在哪个分段
            float f = 100.0f / fn;
            auto p = dn2 * f / dn;
            percent += p;
        }
    }
    auto p2 = percent2 / fn;
    p2 = p2 / (float)dn;
    percent = percent + p2;
    //记录当前进度条
    percent3 = percent;
    _cb = cb;
    
    
    
    
    //
    auto dp1 = (lv-oldLv)*100 - percent2;
    dp1 = dp1 / 100.0f;
    dp1 = dp1 * 100.0f / fn;
    dp1 = dp1 / (float)dn;
    if(lv >= _lvVec.at(0)&&lv < _lvVec.at(1))
    {
        dn = lv1-lv0;
    }
    else if(lv >= _lvVec.at(1)&&lv < _lvVec.at(2))
    {
        dn = lv2-lv1;
    }
    else if(lv >= _lvVec.at(2)&&lv < _lvVec.at(3))
    {
        dn = lv3-lv2;
    }
    auto dp2 = percent1;
    if(lv >= _lvVec.at(3)&&_lvVec.at(3) != 0)
    {
        dp2 = percent1 + (lv - oldLv) * 100;
    }
    dp2 = dp2 / 100.0f;
    dp2 = dp2 * 100.0f / fn;
    dp2 = dp2 / (float)dn;
    this->percent1 = percent + dp1 + dp2;
    this->percent2 = percent;
    loadingBar_percent->setPercent(this->percent2);
    auto maxPercent = this->percent1 - this->percent2;
    
    //速度
    //0.3s完成 s
    percentDx = maxPercent/0.2;//m/s
    percentDx *= 0.017;
    this->percentDx = percentDx / fn;

    
    
    getNode<Text*>("Text_level_up")->setString(StringUtils::format("%d",lv));
}

void LevelUpView::setIsBar(bool isBar)
{
    this->isBar = isBar;
}

void LevelUpView::playUpAni()
{
    isUp = true;
    isUnlock = fishId != -1&&lv == unlockLv;
    playAni("Start0",false,[this](){
        isBar = true;
//        if(fishId != -1&&lv == unlockLv)
//        {//解锁啦
//            playAni("lock",false);
//        }
//        else
//        {
//            //显示按钮
//            playAni("out0",false);
//        }
    });
}

Vec2 LevelUpView::getFishWorldPoi()
{
    auto poi = Node_fish->getPosition();
    poi = Node_fish->getParent()->convertToWorldSpace(poi);
    return poi;
}

bool LevelUpView::getIsUnlock()
{
    return isUnlock;
}

void LevelUpView::fishMove()
{
    auto gameView = SCENE_M->getGameView();
    auto lobby = SCENE_M->getLobby();
    auto poi = Node_fish->getPosition();
    poi = Node_fish->getParent()->convertToWorldSpace(poi);
    if(_type == Type::Game)
    {
        gameView->unlockFishMove(fishId,poi,[this,gameView](){
            //刷新GameView
            gameView->updateFishNewTips();
            
        });
    }
    else if(_type == Type::Lobby)
    {
        lobby->unlockFishMove(fishId,poi,[this,lobby](){
            lobby->updateFishNewTips();
            
        });
    }
}



void LevelUpView::updateDYY()
{
    
    getNode<Text*>("Text_ok")->setString(Lang("100162"));
    getNode<Text*>("Text_get")->setString(Lang("100186"));
    auto Text_miaoshu1 = getNode<Text*>("Text_miaoshu1");
    Text_miaoshu1->setString(Lang("100331"));
    auto Text_miaoshu2 = getNode<Text*>("Text_miaoshu2");
    Text_miaoshu2->setString(Lang("100332"));
    UIUtils::textAdaptiveSize(Text_miaoshu1,700);
    UIUtils::textAdaptiveSize(Text_miaoshu2,700);
    
    getNode<Text*>("Text_level_up_lv")->setString(Lang("100376"));
    
}

void LevelUpView::setType(Type type)
{
    _type = type;
}

void LevelUpView::updateBg()
{
    //判断是否有新的解锁
    auto shopManager = ShopManager::getInstance();
    auto idx = shopManager->getMaxFashTankIdx(oldLv);
    auto cuIdx = DATA_M->getCurrentFashTankIdx();
    if(idx == cuIdx)
    {//嗯 是用的一个场景
        //判断解锁情况
//        auto lvStr = shopManager->getFashTankUnlockLv(cuIdx);
//        auto lvStrVec = UIUtils::split(lvStr,",");
//        int oldLockLv = 0,lockLv = 0;
//        for(int i = 0;i < lvStrVec.size();++i)
//        {
//            auto str = lvStrVec.at(i);
//            if(str == "")continue;
//            auto unlocklv = std::stoi(str);
//            bool isUnlock = oldLv >= unlocklv;
//            if(isUnlock)
//            {
//                oldLockLv = i;
//            }
//            else
//            {//超过以前等级了。看看现在等级有没有解锁
//                if(lv >= unlocklv)
//                {
//                    lockLv = i;
//                }
//                break;
//            }
//        }
//        
//        if(lockLv > oldLockLv)
//        {//有新的解锁 通知背景刷新
//            auto fashTank = SCENE_M->getGameBackground();
//            fashTank->updateBg(oldLockLv,lockLv);
//        }
        
    }
    
}

void LevelUpView::updateUI()
{
    Node_jianTou->setVisible(false);
    isUp = false;
    auto shopManager = ShopManager::getInstance();
    auto playerManager = PlayerManager::getInstance();
    lv = playerManager->getLevel();
    oldLv = lv;
    auto percentDx = 0;
    auto percent1 = playerManager->getPercent();
    auto percent2 = percent1;
    auto maxlv = lv + 1;
    if(maxlv > playerLvMax) maxlv = playerLvMax;
    rewardVec = shopManager->getLvUnlock(maxlv);
    //添加当前奖励
    for(int i = rewardVec.size() - 1;i >= 0;--i)
    {
        auto type = rewardVec.at(i);
        
        if(type != 0)continue;
        auto rewardIdx = type * 10000;
        auto rewardLv = maxlv;
        auto idx = rewardIdx + rewardLv;
        _idxVec.push_back(idx);
    }
    _idx = -1;
    Node_fish->removeAllChildren();
    if(_idxVec.size() > 0)
    {
        _idx = _idxVec.at(_idxVec.size()-1);
        if(_idx >= 10000)
        {
            _idx = -1;
        }
        _idxVec.pop_back();
    }
    
    auto str = playerManager->getPartLv(oldLv);
    auto strVec = UIUtils::split(str, "-");
    
    _lvVec.clear();
    //给进度条分段
    auto num = strVec.size()-1;//currentUnlockLv-oldUnlockLv;
    for(int i = 0;i < 4;++i)
    {
        auto templv = 0;
        if(i < strVec.size())
        {
            templv = std::stoi(strVec.at(i));
        }
        _lvVec.push_back(templv);
    }
    updateReward(maxlv);
//    if(lv < 3)
//    {
//        _lvVec.push_back(0);
//        _lvVec.push_back(1);
//        _lvVec.push_back(2);
//        _lvVec.push_back(3);
//    }
//    else
//    {
//        auto n = lv % 3;
//
//        if(n == 0)
//        {
//            _lvVec.push_back(lv + 0);
//            _lvVec.push_back(lv + 1);
//            _lvVec.push_back(lv + 2);
//            _lvVec.push_back(lv + 3);
//        }
//        else if(n == 1)
//        {
//            _lvVec.push_back(lv - 1);
//            _lvVec.push_back(lv + 0);
//            _lvVec.push_back(lv + 1);
//            _lvVec.push_back(lv + 2);
//        }
//        else if(n == 2)
//        {
//            _lvVec.push_back(lv - 2);
//            _lvVec.push_back(lv - 1);
//            _lvVec.push_back(lv + 0);
//            _lvVec.push_back(lv + 1);
//        }
//    }
    
    for(int i = 0;i < 4;++i)
    {
        auto node = _LvBgVec.at(i);
        auto label = _LabelVec.at(i);
        auto lv = _lvVec.at(i);
        for(int j = 0;j < 3;++j)
        {
            
            auto vec = shopManager->getLvUnlock(lv);
            auto sprite = node->getChildByName(StringUtils::format("reward_%d",j));
            if(i != 0&&vec.size() != 0&&j == 0)
            {
                sprite->setVisible(vec.at(0) == j);
            }
            else
            {
                sprite->setVisible(false);
            }
            
        }
        
        
        
        if(i <= num)
        {
            node->setVisible(true);
            //设置位置
            
            auto x = LoadingBarWidth/num * i;
            node->setPositionX(x);
            //等级文本
            label->setString(StringUtils::format("%d",lv));
        }
        else
        {
            node->setVisible(false);
        }
        
    }
    
    //当前在哪段
    float percent = 0;
    float fn = 1.0f;
    int dn = _lvVec.at(1) - _lvVec.at(0);
    int dn2 = 0;
    int lv0 = _lvVec.at(0);
    int lv1 = _lvVec.at(1);
    int lv2 = _lvVec.at(2);
    int lv3 = _lvVec.at(3);
    if(num == 1)
    {
        percent = 0;
        fn = 1.0f;
    }
    else if(num == 2)
    {
        fn = 2.0f;
        if(oldLv >= _lvVec.at(0)&&oldLv < _lvVec.at(1))
        {
            dn = lv1-lv0;
            dn2 = oldLv - lv0;
            percent = 0;
        }
        else if(oldLv >= _lvVec.at(1)&&(oldLv < _lvVec.at(2)||oldLv == 100))
        {
            dn = lv2-lv1;
            dn2 = oldLv - lv1;
            percent = 100.0f / fn;
        }
        if(dn > 1)
        {//当前等级在哪个分段
            float f = 100.0f / fn;
            auto p = dn2 * f / dn;
            percent += p;
        }
    }
    else if(num == 3)
    {
        fn = 3.0f;
        //12 - 14 - 16 - 18
        if(oldLv >= _lvVec.at(0)&&oldLv < _lvVec.at(1))
        {
            dn = lv1-lv0;
            dn2 = oldLv - lv0;
            percent = 0;
        }
        else if(oldLv >= _lvVec.at(1)&&oldLv < _lvVec.at(2))
        {
            dn = lv2-lv1;
            dn2 = oldLv - lv1;
            percent = 100.0f / fn;
        }
        else if(oldLv >= _lvVec.at(2)&&oldLv < _lvVec.at(3))
        {
            dn = lv3-lv2;
            dn2 = oldLv - lv2;
            percent = 100.0f * 2.0f / fn;
        }
        if(dn > 1)
        {//当前等级在哪个分段
            float f = 100.0f / fn;
            auto p = dn2 * f / dn;
            percent += p;
        }
    }
    auto p2 = percent2 / fn;
    p2 = p2 / (float)dn;
    percent = percent + p2;
    //记录当前进度条
    percent3 = percent;
    
    isQieHuan = false;
    //isBar = false;
    this->lv = lv;
    this->oldLv = oldLv;
    dLv = 0;
    
    
    
    auto dp1 = 100 - percent2;
    dp1 = dp1 / 100.0f;
    dp1 = dp1 * 100.0f / fn;
    dp1 = dp1 / (float)dn;
    if(lv >= _lvVec.at(0)&&lv < _lvVec.at(1))
    {
        dn = lv1-lv0;
    }
    else if(lv >= _lvVec.at(1)&&lv < _lvVec.at(2))
    {
        dn = lv2-lv1;
    }
    else if(lv >= _lvVec.at(2)&&lv < _lvVec.at(3))
    {
        dn = lv3-lv2;
    }
    auto dp2 = percent1;
    if(lv >= _lvVec.at(3)&&_lvVec.at(3) != 0)
    {
        dp2 = percent1 + (lv - oldLv) * 100;
    }
    dp2 = dp2 / 100.0f;
    dp2 = dp2 * 100.0f / fn;
    dp2 = dp2 / (float)dn;
    this->percent1 = percent + dp1 + dp2;
    this->percent2 = percent;
    if(lv == playerLvMax)
    {
        loadingBar_percent->setPercent(100);
    }
    else
    {
        loadingBar_percent->setPercent(this->percent2);
    }
    
    auto maxPercent = this->percent1 - this->percent2;
    
    //速度
    //0.3s完成 s
    percentDx = maxPercent/0.3;//m/s
    percentDx *= 0.017;
    this->percentDx = percentDx / fn;

    
    
    getNode<Text*>("Text_level_up")->setString(StringUtils::format("%d",lv));
}

void LevelUpView::setVisible(bool visible)
{
    BaseLayer::setVisible(visible);
    if (visible) onRecordEnter();
    else onRecordExit();
    if(!visible)
    {
        if(!isUp)
        {
            if(LevelUpView::Type::Game == _type)
            {
                auto _gameView = SCENE_M->getGameView();
                if(_gameView)
                {
                    _gameView->gamePause(false);//解除暂停
                    _gameView->setIsOpenTipsTime(true);
                }
            }
        }
    }
    isUp = false;
}
