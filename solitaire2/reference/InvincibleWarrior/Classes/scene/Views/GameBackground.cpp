#include <stdio.h>
#include "GameBackground.h"

#include "../../Fish/Fish0.h"
#include "../../Fish/ShadowsFish.h"
#include "DataManager.h"
#include "MainLobby.h"
#include "GameViewHD.hpp"
#include "SoundManager.h"
#include "RewardNode.h"
#include "ShopManager.h"
#include "PlayerManager.h"
#include "FashTankSwitch.h"
#include "FashTankUp.h"
#include "FishManager.h"
#include "FishGuideManager.h"
#include "FanPaiRewardView.h"

GameBackground::~GameBackground()
{
    
}

GameBackground::GameBackground()
:BaseLayer("2021FashTank.csb")
{
    
}

void GameBackground::initUI()
{
    BaseLayer::initUI();
    doLayout();
    _currentFashTankIdx = DATA_M->getCurrentFashTankIdx();
    Sprite_complete = getNode("Sprite_complete");
    Node_weishi = UIUtils::createCSBNode("Animation/Node_weishi.csb");
    Node_siliao = FIND_NODE(Node*, Node_weishi, "FileNode_1");
    getNode("Node_siliao")->addChild(Node_weishi);
    Node_weishi->setVisible(false);
    
    Node_Fish = getNode("Node_Fish");
    Node_Start = getNode("Node_fishStartPoi");
    Node_Shadows = getNode("Node_Shadows");
    Node_build = getNode("Node_bulid");
    Button_build = getNode<Button*>("Button_build");
    Sprite_chuiZi = getNode<Sprite*>("Sprite_chuiZi");
    Sprite_chanZi = getNode<Sprite*>("Sprite_chanZi");
    
    gameBg = Sprite::create();
    createBg();
    auto size = Director::getInstance()->getWinSize();
    gameBg->setContentSize(size);
    
    if (UIUtils::IsPad()) {
        gameBg->setPosition(Vec2(vSize.width/2, vSize.height/2));
    }
    else {
        gameBg->setAnchorPoint(Vec2::ZERO);
    }
    getNode("Node_bg")->addChild(gameBg, -1);
    clearFish();
    createFish();
    
    ceshiId = 0;
    
    schedule([this](float dt){
        updateWeiShi();
    }, 60, "FashTank_updateWeiShi");
    schedule(CC_CALLBACK_1(GameBackground::Update, this),"update");
    
}

void GameBackground::initData()
{
    BaseLayer::initData();
    setName("GameBackground");
}

void GameBackground::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "Button_build")
    {
        playAni("start",false);
        if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::unlockTipsOne)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::unlockTipsOne))
        {
            GUIDE_M->endGuide();
        }
        SCENE_M->addDialog(FashTankUp::createLayerN());
    }
    else if(btnName == "Button_yes")
    {
        
    }
}

void GameBackground::updateUI()
{
    
}

void GameBackground::updateWeiShi()
{
   
    auto lobby = SCENE_M->getLobby();
    if(lobby)
    {
        lobby->showWeiShiBtn(!getIsMaxHp());
    }
}

bool GameBackground::getIsMaxHp()
{
    auto fishArr = Node_Fish->getChildren();
    Vector<Fish0*> maxHpVec;
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        //恢复30点血
        if(!item)continue;
        //满血的就别吃了
        if(item->getIsMaxHp())continue;
        maxHpVec.pushBack(item);
       
    }
    return maxHpVec.size() == 0;
}

void GameBackground::updateDYY()
{
    auto fishArr = Node_Fish->getChildren();
    
    Vector<Fish0*> fishVec;
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        if(!item)continue;
        item->updateDYY();
    }
}

void GameBackground::Update(float dt)
{
    if(FileNode_fitting2_7&&_isAngle)
    {
        auto selfPos = FileNode_fitting2_7->getPosition();
        auto length = (_tempSelfPos-selfPos).length();
        //角度
        Vec2 a(590,1060);
        auto angle = UIUtils::getAngle(_tempSelfPos,selfPos);
        FileNode_fitting2_7->setRotation(angle + 90);

        _tempSelfPos = selfPos;
    }
    
}

void GameBackground::onEnter()
{
    BaseLayer::onEnter();
    
    string musicName = "Ambient/sceneUnderwater.mp3";
    if(-1 != SceneMusicID) {
        SOUND_M->stopEffectMusic(SceneMusicID);
        SceneMusicID = -1;
    }
    if (!musicName.empty())
        SceneMusicID = SOUND_M->playEffectMusic(musicName, true);
}

void GameBackground::onExit()
{
    BaseLayer::onExit();
}

bool GameBackground::onTouchBegan(Touch * touch, Event * e)
{
    auto touchPoi = touch->getLocation();
    
    auto lobby = SCENE_M->getLobby();
    if(!lobby->isVisible()) return true;
    
    auto fishArr = Node_Fish->getChildren();
    
    Vector<Fish0*> fishVec;
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        if(!item)continue;
        if(item->getIsStart())continue;
        if(!item->getIsTouch())continue;
        if(item->getIsJinShi())continue;
        auto rect = item->getWorldRect();
        if(rect.containsPoint(touchPoi))
        {
            fishVec.pushBack(item);
        }
    }
    Fish0* fish = NULL;
    for(int i = 0;i < fishVec.size();++i)
    {
        auto item = fishVec.at(i);
        if(fish == NULL)
        {
            fish = item;
        }
        else
        {
            auto ZOrder0 = item->getLocalZOrder();
            auto ZOrder1 = fish->getLocalZOrder();
            if(ZOrder0 > ZOrder1)
            {//item还要在上边
                fish =item;
            }
        }
    }
    
    if(fish != NULL)
    {
        fish->jiaSu();
        //点击鱼掉落奖励
        _clickFish = fish;
        clickFishReward(touchPoi);
    }
    
//    Vector<RewardNode*> tempVec;
//    for(int i = 0;i < _rewardVec.size();++i)
//    {
//        auto item = _rewardVec.at(i);
//
//        if(!item->getIsTouch()) continue;
//        auto rect = item->getWorldRect();
//        if(rect.containsPoint(touchPoi))
//        {//碰到了 给奖励吧
//            item->hideReward();
//            tempVec.pushBack(item);
//        }
//    }
//    //清理已经领过的奖励
//    for(int i = 0;i < tempVec.size();++i)
//    {
//        auto item = tempVec.at(i);
//        _rewardVec.eraseObject(item);
//        item->removeFromParent();
//    }
    
    return true;
}

void GameBackground::onTouchMoved(Touch * touch, Event * e)
{
    
}

void GameBackground::onTouchEnded(Touch * touch, Event * e)
{
    _clickFish = NULL;
}

void GameBackground::onTouchCancelled(Touch * t, Event * e)
{
    _clickFish = NULL;
}

void GameBackground::weishi()
{
    auto size = Director::getInstance()->getWinSize();
    Vec2 poi = size/2;
    poi.x = random(poi.x - 200, poi.x + 200);
    poi.y = random(poi.y - 200, poi.y + 200);

    
    
    auto fishArr = Node_Fish->getChildren();
    Vector<Fish0*> weiShiVec;
    
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        //恢复30点血
        if(!item)continue;
        //满血的就别吃了
        if(!item->getIsWeiShi())continue;
        weiShiVec.pushBack(item);
        //item->restoreHp(30);
        //item->weiShi(poi);
    }
    
    std::random_shuffle(weiShiVec.begin(), weiShiVec.end(), UIUtils::myrandom);
    for(int i = 0;i < weiShiVec.size();++i)
    {
        auto item = weiShiVec.at(i);
        if(i == 0)
        {
            Node_weishi->setVisible(true);
            Node_weishi->setPosition(poi);
            UIUtils::playInnerAction(Node_siliao,"start",false,[this](){
                Node_weishi->setVisible(false);
            });
            //重置掉落
            DATA_M->setClickFishTime(0);
            item->weiShi(poi,false,Lang("100350"));
        }
        else if(i == weiShiVec.size()-1)
        {
            item->weiShi(poi,true);
        }
        else
        {
            item->weiShi(poi,false);
        }
    }
}

void GameBackground::jiasu()
{
    auto fishArr = Node_Fish->getChildren();
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        item->fishRush();
    }
}
void GameBackground::jiansu()
{
    auto fishArr = Node_Fish->getChildren();
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        item->fishStay();
    }
}
void GameBackground::stop()
{
    auto fishArr = Node_Fish->getChildren();
    for(int i = 0;i < fishArr.size();++i)
    {
        auto item = dynamic_cast<Fish0*>(fishArr.at(i));
        item->fishStop();
    }
}

void GameBackground::addFish(int type,bool isDaily)
{
    if(_fishVec.size() >= 25)  return;
    
    auto poi = Node_Start->getPosition();
    auto fishNum = DATA_M->getFishNum();
    
    DATA_M->addFishTypeData(fishNum,(type == -1 ? ceshiId : type));
    auto fashTankId = DATA_M->getCurrentFashTankIdx();
    DATA_M->setFishNum(fishNum + 1,fashTankId);
    
    
    auto fish = Fish0::createFish(this,NULL,fishNum,(DataManager::FishType)(type == -1 ? ceshiId : type));
    fish->setIsDaily(isDaily);
    auto shadows = ShadowsFish::createLayerN(fish);
    Node_Shadows->addChild(shadows);
    Node_Fish->addChild(fish);
    
    fish->setShadows(shadows);
    //fish->setType((DataManager::FishType)0);
    fish->setPosition(poi);
    fish->fishAdmission();
    
    
    
    _fishVec.pushBack(fish);
    _fishSVec.pushBack(shadows);
    
    
    ceshiId++;
    if(ceshiId > 14)ceshiId = 0;
    
    auto lobby = SCENE_M->getLobby();
    lobby->updateFishNum();
    
    updateBuildComplete();
}

void GameBackground::delateFish()
{
    if(_fishVec.size() == 0) return;
    auto item = _fishVec.at(0);
    deleteFish(item);
}

void GameBackground::deleteFish(Fish0* fish)
{
    if(fish)
    {
        auto id = fish->getFishId();
        ShadowsFish* _shadows = NULL;
        for(int i = 0;i < _fishVec.size();++i)
        {
            auto item = _fishVec.at(i);
            auto shadows = _fishSVec.at(i);
            if(i == id)
            {
                _shadows = shadows;
                item->deleteSelf();
            }
            else if(i > id)
            {//变化id
                item->setFishId(i - 1);
            }
        }
        if(_shadows)
        {
            _fishSVec.eraseObject(_shadows);
        }
        _fishVec.eraseObject(fish);
        
        auto fashTankId = DATA_M->getCurrentFashTankIdx();
        DATA_M->deleteFishTypeData(id,fashTankId);
        DATA_M->setFishNum(DATA_M->getFishNum(fashTankId) - 1,fashTankId);
    }
}

void GameBackground::deleteFish(int fishType,int fashTank)
{
    Fish0* fish = NULL;
//    for(int i = 0;i < _fishVec.size();++i)
//    {
//        auto item = _fishVec.at(i);
//        auto type = (int)item->getFishType();
//        if(type == fishType)
//        {
//            fish = item;
//        }
//    }
    auto idx = DATA_M->getCurrentFashTankIdx();
    if(idx == fashTank)
    {
        fish = _fishVec.at(fishType);
        deleteFish(fish);
    }
    else
    {
        DATA_M->deleteFishTypeData(fishType,fashTank);
        DATA_M->setFishNum(DATA_M->getFishNum(fashTank) - 1,fashTank);
    }
    
}

bool GameBackground::isFishY(Vec2 poi,bool isLeft)
{//让鱼更分散
    int num = 0;
    for(int i = 0;i < _fishVec.size();++i)
    {
        auto item = _fishVec.at(i);
        auto itemPoi = item->getPosition();
        auto itemIsLeft = item->getIsLeft();
        if(itemIsLeft == isLeft&&(itemPoi-poi).length() < 500&&fabsf(poi.y-itemPoi.y) < 100)
        {//离得有点进了 在看看y
            num++;
        }
    }
    
    return num < 3;
}

void GameBackground::updateBg(int unlockLv)
{
    // 当前需要解锁的配饰 unlockLv 0,2,7,9,12,15
    auto node = gameBg->getChildByTag(10086);
    auto aniName = StringUtils::format("start%d",unlockLv);
    auto idleName = StringUtils::format("idle%d",unlockLv);;
//    auto fitting = FIND_NODE(Node *,node,StringUtils::toString(unlockLv));
//    auto FileNode_fitting = FIND_NODE(Node *,node,StringUtils::format("FileNode_%d",unlockLv));
//    if(fitting) fitting->setVisible(true);
//    if(FileNode_fitting) FileNode_fitting->setVisible(true);
    SOUND_M->playEffectMusic(EffectThrophy);
    UIUtils::playInnerAction(node,aniName,false,[this,node,idleName,unlockLv](){
        UIUtils::playInnerAction(node,idleName,false);
        //更新建造
        updateBuild();
        if(_currentFashTankIdx == 2&&unlockLv == 6)
        {
            fishZXMove(true);
        }
    });
}

void GameBackground::updateBg()
{
    auto fashTankIdx = DATA_M->getCurrentFashTankIdx();
    if(_currentFashTankIdx != fashTankIdx)
    {
        
        _currentFashTankIdx = fashTankIdx;
        SCENE_M->addDialog(FashTankSwitch::createLayerN(fashTankIdx));
        createBg();
        clearFish();
        createFish();
    }
}

const int YueLiangTag = 20000;
const int BGTag = 10086;
const int RemoveTag = 10085;
void GameBackground::createBg()
{
    _isBuild = false;
    Node_build->setVisible(false);
    _tempSelfPos = DEFAULTPOS;
    _isAngle = false;
    Node_Fish->removeChildByTag(YueLiangTag);
    FileNode_fitting2_7 = NULL;
    //gameBg->removeAllChildren();
    auto oldNode = gameBg->getChildByTag(BGTag);
    if(oldNode)
    {
        oldNode->setTag(RemoveTag);
        oldNode->setLocalZOrder(-1);
        //0.5s 淡出
        auto fadeOut = FadeOut::create(0.5f);
        auto re = RemoveSelf::create();
        auto seq = Sequence::create(DelayTime::create(0.3f),fadeOut,CallFunc::create([this](){
        }), re,NULL);
        oldNode->runAction(seq);
    }
    auto node = UIUtils::createCSBNode(StringUtils::format("desktop/scene%d",_currentFashTankIdx) + (UIUtils::IsPad()?"_pad.csb":".csb"), "loop", true);
    auto Panel_top = node->getChildByName("Panel_top");
    if(Panel_top)
    {
        Panel_top->setVisible(false);
    }
    
    gameBg->addChild(node,-2,BGTag);
    bool isChanZi = _currentFashTankIdx == 0 || _currentFashTankIdx == 3;
    Sprite_chanZi->setVisible(isChanZi);
    Sprite_chuiZi->setVisible(!isChanZi);
    
    
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    //设置为屏幕大小
    node->setContentSize(safeArea.size);
    node->setPosition(Vec2::ZERO);

    cocos2d::ui::Helper::doLayout(node);
    
    auto lv = PlayerManager::getInstance()->getLevel();
    
    auto num = DATA_M->getFishNum(_currentFashTankIdx);
    auto fishStr = ShopManager::getInstance()->getFashTankFishNum(_currentFashTankIdx);
    auto fishVec = UIUtils::split(fishStr,",");
    auto cishiUnLock = DATA_M->getIsCeShiUnLock();
    string aniName = "loop";
    bool isTemp = false;
    for(int i = 1;i < fishVec.size();++i)
    {
        auto str = fishVec.at(i);
        if(str == "")continue;
        auto fishNum = std::stof(str);
        bool isUnlock = num >= fishNum;
        isUnlock = DATA_M->getFashTankUnlock(_currentFashTankIdx,i-1);
        auto fitting = FIND_NODE(Node *,node,StringUtils::toString(i));
        auto FileNode_fitting = FIND_NODE(Node *,node,StringUtils::format("FileNode_%d",i));
        if(isUnlock&&i != 0)
        {
            aniName = StringUtils::format("idle%d",i - 1);
        }
        //位置
        Vec2 startPoi = DEFAULTPOS;
        if(fitting)
        {
            fitting->setVisible(isUnlock||cishiUnLock);
            auto poi = fitting->getPosition();
            poi = fitting->getParent()->convertToWorldSpace(poi);
            startPoi = poi;
            if(_currentFashTankIdx == 3&&i == 9)
            {
                auto parent = fitting->getParent();
                auto scaleX = parent->getScaleX();
                auto scaleY = parent->getScaleY();
                auto worldPos = fitting->getPosition();
                worldPos = parent->convertToWorldSpace(worldPos);
                fitting->removeFromParentAndCleanup(false);
                Node_Fish->addChild(fitting, -1,YueLiangTag);
                worldPos = Node_Fish->convertToNodeSpace(worldPos);
                fitting->setPosition(worldPos);
                fitting->setScale(scaleX, scaleY);
            }
        }
        else if(FileNode_fitting)
        {
            FileNode_fitting->setVisible(isUnlock||cishiUnLock);
            UIUtils::playInnerAction(FileNode_fitting,"loop",true);
            auto poi = FileNode_fitting->getPosition();
            poi = FileNode_fitting->getParent()->convertToWorldSpace(poi);
            startPoi = poi;
            if(_currentFashTankIdx == 2&&i == 7)
            {
                FileNode_fitting2_7 = FileNode_fitting;
                if(isUnlock||cishiUnLock)
                {
                    fishZXMove();
                }
            }
        }
        if(_currentFashTankIdx == 3&&i == 8)
        {
            auto Node_8_poi = FIND_NODE(Node *,node,"Node_8_poi");
            auto poi = Node_8_poi->getPosition();
            poi = Node_8_poi->getParent()->convertToWorldSpace(poi);
            startPoi = poi;
        }
        
//        if(!isTemp&&!isUnlock&&startPoi != DEFAULTPOS)
//        {
//            _isBuild = true;
//            isTemp = true;
//            Button_build->setEnabled(true);
//            Node_build->setVisible(true);
//            //创建
//            if(!oldNode)
//            {
//
//            }
//
//
//            Node_build->setPosition(startPoi);
//            updateBuildComplete();
//        }
    }
    
    updateBuild();
    
    UIUtils::playInnerAction(node,aniName,false);
    
}

void GameBackground::clearFish()
{
    for(int i = 0;i < _fishVec.size();++i)
    {
        auto fish = _fishVec.at(i);
        fish->removeFromParent();
    }
    for(int i = 0;i < _fishSVec.size();++i)
    {
        auto fishS = _fishSVec.at(i);
        fishS->removeFromParent();
    }
    _fishVec.clear();
    _fishSVec.clear();
}

void GameBackground::createFish()
{
    auto fishTypeVec = DATA_M->getFishTypeVec(_currentFashTankIdx);
    //_fishVec = Vector<Fish0>();
    _fishVec.clear();
    _fishSVec.clear();
    
    //离线时间
    auto offlineTime = DATA_M->getOfflineTime();
    Vector<Fish0*> tempVec;
    for(int i = 0;i < fishTypeVec.size();++i)
    {
        auto type = fishTypeVec.at(i);
        auto fish = Fish0::createFish(this,NULL,i,(DataManager::FishType) type,offlineTime);//
        auto shadows = ShadowsFish::createLayerN(fish);
        Node_Shadows->addChild(shadows);
        Node_Fish->addChild(fish);
        fish->setShadows(shadows);
        
        
        tempVec.pushBack(fish);
        _fishVec.pushBack(fish);
        _fishSVec.pushBack(shadows);
    }
    
    
    auto rand = 10;
    std::random_shuffle(tempVec.begin(), tempVec.end(), UIUtils::myrandom);
    //随便选一个翻白的
    bool isDuiHua = true;
    if(_fishVec.size() >= rand)
    {//随机选几个在中间
        for(int i = 0;i < tempVec.size();++i)
        {
            auto item = tempVec.at(i);
            if(isDuiHua)
            {
                isDuiHua = false;
            }
            if(i < rand)
            {
                item->fishZXMove();
            }
            else
            {
                item->fishMove();
            }
        }
    }
    else
    {//都在中间吧
        for(int i = 0;i < tempVec.size();++i)
        {
            auto item = tempVec.at(i);
            if(isDuiHua)
            {
                isDuiHua = false;
            }
            item->fishZXMove();
        }
    }
}
const int clickTime = 3 * 60;
void GameBackground::clickFishReward(Vec2 poi,Fish0* _fish)
{//第一次点击必定掉落，必定掉落后 60%几率点击掉落，3分钟后重复以上逻辑
    //掉落几率 20%经验 70%金币。10%魔法棒
    bool isReward = false;
    
    if(DATA_M->getClickFishTime() == 0)
    {
        isReward = true;
        DATA_M->setClickFishTime(clickTime);
    }
    else
    {
        auto rand = random(1, 1000);
        if(rand <= 65)
        {//首次掉落后 再次点击 有一定几率出掉落
            isReward = true;
        }
    }
    
    bool isGold = false;
    
    if(isReward)
    {//有掉落奖励 开始分配掉落奖励
        auto rand = random(1, 1000);
        
        int num = random(1,3);
        RewardType rewardType = RewardType::NONE;
        if(rand <= 240)
        {//经验 1-8
            rewardType = RewardType::EXP;
        }
        else if(rand <= 940)
        {//金币 1-5
            num = random(1,5);
            isGold = true;
            rewardType = RewardType::GOLD;
        }
        else if(rand <= 1000)
        {//魔法棒
            rewardType = RewardType::MAGIC;
            num = 1;
        }
        //设置位置
        auto node = RewardNode::createLayerN(rewardType,num);
        
        this->addChild(node);
        node->setPosition(poi);
        //_rewardVec.pushBack(node);
    }
    
    auto rand = random(1, 100);
    if(!_fish)
    {
        if(isGold)
        {//10% money
            if(rand <= 10)
            {
                _clickFish->showDuiHua("",Fish0::EmojiType::money);
            }
        }
        else
        {//10% happy
            if(rand <= 10)
            {
                _clickFish->showDuiHua("",Fish0::EmojiType::happy);
            }
        }
    }
    
}

void GameBackground::fishMove()
{
    _isAngle = true;
    auto moveSpeed = random(30.0f,100.0f);
    auto vec = getRoute();
    int PointCount = 10;//
    auto bezvec = ComputeBezier(vec[0],vec[1],vec[2] ,vec[3],PointCount);
    //求出长度
    int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
    
    auto _time = bezierLen / moveSpeed;
    //阴影高度
    auto y = vec[0].y;
    auto a = y/1920.f;
    y = a * 1920.f / 3.f;
    FileNode_fitting2_7->setPosition(vec[0]);
    ccBezierConfig config;
    config.controlPoint_1 = vec[1];
    config.controlPoint_2 = vec[2];
    config.endPosition = vec[3];
    auto bez = BezierTo::create(_time, config);
    
    
    auto fishNum = DATA_M->getFishNum();

    auto randTime = random(1.0f, 3.0f);
    auto deTime = DelayTime::create(randTime);
    auto func = CallFunc::create([this](){
        fishMove();
    });
    
    auto seq = Sequence::create(deTime,bez,func, NULL);
    auto _fishActionSpeed = Speed::create(seq,1);
    
    FileNode_fitting2_7->runAction(_fishActionSpeed);
}

void GameBackground::fishZXMove(bool isAniEnd)
{
    
    auto moveSpeed = random(30.0f,100.0f);
    if(isAniEnd)
    {
        
        auto poi = FileNode_fitting2_7->getPosition();
        auto rect = FileNode_fitting2_7->getChildByName("qianting0_1")->getBoundingBox();
        auto x = -rect.size.width - 100;
        auto y = poi.y;
        Vec2 endPoi(x,y);
        auto length = (poi-endPoi).getLength();
        auto _time = length / moveSpeed;
        auto moTo = MoveTo::create(_time, endPoi);
        auto func = CallFunc::create([this](){
            fishMove();
        });
        auto seq = Sequence::create(moTo,func, NULL);
        auto _fishActionSpeed = Speed::create(seq,1);
        
        FileNode_fitting2_7->runAction(_fishActionSpeed);
    }
    else
    {
        _isAngle = true;
        //计算起点
        auto vec = getRoute();
        auto randModel = random(0, 1);
        //判定 是否向左移动
        bool isLeft = vec[1].x > vec[2].x;
        
        Vec2 p0,p1,p2,p3;
        if(randModel == 0)
        {//只有一个控制点
            float randX = 0;
            if(isLeft)
            {
                randX = random(vec[2].x + 80,vec[1].x);
            }
            else
            {
                randX = random(vec[1].x,vec[2].x - 80);
            }
            auto y = random(vec[2].y-50, vec[2].y + 50);
            
            p0 = Vec2(randX,y);
            p1 = vec[2];
            p2 = vec[2];
            p3 = vec[3];
        }
        else
        {//有两个控制点
            float randX = 0;
            if(isLeft)
            {
                randX = random(vec[1].x + 80,1000.0f);
            }
            else
            {
                randX = random(80.0f,vec[1].x - 80);
            }
            auto y = random(vec[1].y-50, vec[1].y + 50);
            p0 = Vec2(randX,y);
            p1 = vec[1];
            p2 = vec[2];
            p3 = vec[3];
        }
        
        FileNode_fitting2_7->setPosition(p0);
        
        int PointCount = 10;//
        auto bezvec = ComputeBezier(p0,p1,p2 ,p3,PointCount);
        //求出长度
        int bezierLen = (int)BezierLenth(bezvec, PointCount+1);
        
        auto _time = bezierLen / moveSpeed;
        //阴影高度
        auto y = p0.y;
        auto a = y/1920.f;
        y = a * 1920.f / 3.f;
        FileNode_fitting2_7->setPosition(p0);
        
        ccBezierConfig config;
        config.controlPoint_1 = p1;
        config.controlPoint_2 = p2;
        config.endPosition = p3;
        auto bez = BezierTo::create(_time, config);
        auto randTime = 0;
        
        auto deTime = DelayTime::create(randTime);
        auto func = CallFunc::create([this](){
            fishMove();
        });
        
        auto seq = Sequence::create(deTime,bez,func, NULL);
        auto _fishActionSpeed = Speed::create(seq,1);
        
        FileNode_fitting2_7->runAction(_fishActionSpeed);
    }
    
}


vector<Vec2> GameBackground::getRoute()
{
    vector<Vec2> vecs = vector<Vec2>();
    
    if(!_isLeft)
    {
        scaleY = -1;
    }
    else
    {
        scaleY = 1;
    }
    FileNode_fitting2_7->setScaleY(scaleY);
    auto rect = FileNode_fitting2_7->getChildByName("qianting0_1")->getBoundingBox();
    auto x0 = -rect.size.width - 100;
    auto x1 = random(333-150, 333 + 150);
    auto x2 = random(766-150, 766 + 150);
    auto x3 = 1080 + rect.size.width + 100;
    
    auto tempY = 0;
    auto y0 = 0;
    auto y1 = 0;
    auto y2 = 0;
    auto y3 = 0;
    
    
    auto min = 450.f;
    auto max = 650.f;
    if(UIUtils::IsPad())
    {
        auto scaleMin = min/1920.f;
        auto scaleMax = max/1920.f;
        min = scaleMin * 1440.f;
        max = scaleMax * 1440.f;
    }
    tempY = random(min,max);//1625;
    
    auto dy = UIUtils::IsPad()?70:100;
    y0 = random(tempY-dy, tempY + dy);
    y1 = random(tempY-dy, tempY + dy);
    y2 = random(tempY-dy, tempY + dy);
    y3 = random(tempY-dy, tempY + dy);
    Vec2 poi0;
    if(!_isLeft)
    {//左到右
        poi0 = Vec2(x0,y0);
    }
    else
    {//右到左
        poi0 = Vec2(x3,y3);
    }
    
    if(!_isLeft)
    {//左到右
        vecs.push_back(Vec2(x0,y0));
        vecs.push_back(Vec2(x1,y1));
        vecs.push_back(Vec2(x2,y2));
        vecs.push_back(Vec2(x3,y3));
    }
    else
    {//右到左
        vecs.push_back(Vec2(x3,y3));
        vecs.push_back(Vec2(x2,y2));
        vecs.push_back(Vec2(x1,y1));
        vecs.push_back(Vec2(x0,y0));
    }
    _isLeft = !_isLeft;
    return vecs;
}

Vec2 GameBackground::PointOnCubicBezier(Vec2* cp, float t)
{
    float ax, bx, cx; float ay, by, cy;
    float tSquared, tCubed; Vec2 result;
    /* 计算多项式系数 */
    cx = 3.0 * (cp[1].x - cp[0].x);
    bx = 3.0 * (cp[2].x - cp[1].x) - cx;
    ax = cp[3].x - cp[0].x - cx - bx;
    cy = 3.0 * (cp[1].y - cp[0].y);
    by = 3.0 * (cp[2].y - cp[1].y) - cy;
    ay = cp[3].y - cp[0].y - cy - by;
    /* 计算t位置的点值 */
    tSquared = t * t;
    tCubed = tSquared * t;
    result.x = (ax * tCubed) + (bx * tSquared) + (cx * t) + cp[0].x;
    result.y = (ay * tCubed) + (by * tSquared) + (cy * t) + cp[0].y;
    return result;
}
 
 
std::vector<Vec2> GameBackground::ComputeBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments)
{
    std::vector<Vec2> vertices;

    float t = 0;
    for (unsigned int i = 0; i < segments; i++)
    {
        vertices.push_back(Vec2(powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x, powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y));
//        vertices[i].x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
//        vertices[i].y = powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
        t += 1.0f / segments;
    }
//    vertices[segments].x = destination.x;
//    vertices[segments].y = destination.y;
    vertices.push_back(Vec2(destination.x, destination.y));
    return vertices;
}

float GameBackground::BezierLenth(const std::vector<Vec2> &points, int points_count)
{
    float len = 0;
    for (int i = 0; i<points_count; i++) {
 
        Vec2 nowP = points[i];
        Vec2 preP;
        if (i != 0) {
            preP = points[i - 1];
 
            Vec2 dis = nowP - preP;
            //distance就是两点距离
            float distance = sqrt(pow(dis.x, 2) + pow(dis.y, 2));
 
            len += distance;
        }
        else {
            preP = Point(0,0);
        }
    }
 
    return len;
}

Vec2 GameBackground::getPeiShiWorldPoi(int idx)
{
    auto node = gameBg->getChildByTag(10086);
    
    auto fitting = FIND_NODE(Node *,node,StringUtils::toString(idx));
    auto FileNode_fitting = FIND_NODE(Node *,node,StringUtils::format("FileNode_%d",idx));
    auto rect = Director::getInstance()->getSafeAreaRect();
    Vec2 poi = Vec2(rect.getMidX(),rect.getMidY());
    if(fitting)
    {
        poi = fitting->getPosition();
        poi = fitting->getParent()->convertToWorldSpace(poi);
    }
    else if(FileNode_fitting)
    {
        poi = FileNode_fitting->getPosition();
        poi = FileNode_fitting->getParent()->convertToWorldSpace(poi);
    }
    if(_currentFashTankIdx == 3&&idx == 8)
    {
        auto Node_8_poi = FIND_NODE(Node *,node,"Node_8_poi");
        poi = Node_8_poi->getPosition();
        poi = Node_8_poi->getParent()->convertToWorldSpace(poi);
    }
    else if(_currentFashTankIdx == 3&&idx == 9)
    {
        auto node9 = Node_Fish->getChildByTag(YueLiangTag);
        poi = node9->getPosition();
        poi = node9->getParent()->convertToWorldSpace(poi);
        
    }
    
    return poi;
}

void GameBackground::showBuild(bool isShow)
{
    Node_build->setVisible(_isBuild&&isShow);
    if(_isBuild&&isShow)
    {
        playAni(_isComplete?"start1":"in",false);
    }
}

void GameBackground::updateBuild()
{
    _isBuild = false;
    auto lobby = SCENE_M->getLobby();
    Button_build->setEnabled(true);
    Node_build->setVisible(false);
    auto node = gameBg->getChildByTag(BGTag);
    auto fishStr = ShopManager::getInstance()->getFashTankFishNum(_currentFashTankIdx);
    auto fishVec = UIUtils::split(fishStr,",");
    string aniName = "";
    bool isTemp = false;
    for(int i = 1;i < fishVec.size();++i)
    {
        auto str = fishVec.at(i);
        if(str == "")continue;
        bool isUnlock = DATA_M->getFashTankUnlock(_currentFashTankIdx,i-1);
        auto fitting = FIND_NODE(Node *,node,StringUtils::toString(i));
        auto FileNode_fitting = FIND_NODE(Node *,node,StringUtils::format("FileNode_%d",i));
        //位置
        Vec2 startPoi = DEFAULTPOS;
        if(fitting)
        {
            auto poi = fitting->getPosition();
            poi = fitting->getParent()->convertToWorldSpace(poi);
            startPoi = poi;
        }
        else if(FileNode_fitting)
        {
            auto poi = FileNode_fitting->getPosition();
            poi = FileNode_fitting->getParent()->convertToWorldSpace(poi);
            startPoi = poi;
        }
        
        if(_currentFashTankIdx == 3&&i == 8)
        {
            auto Node_8_poi = FIND_NODE(Node *,node,"Node_8_poi");
            auto poi = Node_8_poi->getPosition();
            poi = Node_8_poi->getParent()->convertToWorldSpace(poi);
            startPoi = poi;
        }
        else if(_currentFashTankIdx == 3&&i == 9)
        {
            auto node9 = Node_Fish->getChildByTag(YueLiangTag);
            auto poi = node9->getPosition();
            poi = node9->getParent()->convertToWorldSpace(poi);
            startPoi = poi;
        }
        
        if(!isTemp&&!isUnlock&&startPoi != DEFAULTPOS)
        {
            _isBuild = true;
            isTemp = true;
            //创建
            //判断大厅
            
            if(lobby&&!lobby->getIsGoGameView())
            {
                Node_build->setVisible(true);
                playAni("in",false);
            }
            else if(!lobby)
            {
                Node_build->setVisible(true);
            }
            
            Node_build->setPosition(startPoi);
            updateBuildComplete();
            break;
        }
    }
}

void GameBackground::hideBuild()
{
    Button_build->setEnabled(false);
    playAni("start",false,[this](){
        Node_build->setVisible(false);
    });
}

void GameBackground::updateBuildComplete()
{
    auto shopManager = ShopManager::getInstance();
    auto fashTankidx = DATA_M->getCurrentFashTankIdx();
    
    auto vec = DATA_M->getFishTypeVec(fashTankidx);
    auto fishManager = FishManager::getInstance();
    int maxLv = 0;
    float num = 0.f;
    for(int i = 0;i < vec.size();++i)
    {
        auto fishId = vec.at(i);
        auto lv = fishManager->getUnlockLv(fishId);
        float f = (float)lv/NPC_NUM;
        auto str = UIUtils::getFloatStr(f,1);
        f = std::stof(str);
        num = num + f;
    }
    

    bool isChanZi = fashTankidx == 0 || fashTankidx == 3;
    Sprite_chanZi->setVisible(isChanZi);
    Sprite_chuiZi->setVisible(!isChanZi);
    auto fishStr = shopManager->getFashTankFishNum(fashTankidx);
    auto fishVec = UIUtils::split(fishStr,",");
    string aniName = "";
    int frameId = -1;
    float maxNum = 0;
    for(int i = 1;i < fishVec.size();++i)
    {
        auto str = fishVec.at(i);
        if(str == "")continue;
        auto fishNum = std::stof(str);
        bool isUnlock = num >= fishNum;
        isUnlock = DATA_M->getFashTankUnlock(fashTankidx,i-1);
        
        if(!isUnlock)
        {
            frameId = i-1;
            maxNum = fishNum;
            break;
        }
    }
    _isComplete = num >= maxNum;
    Sprite_complete->setVisible(_isComplete);
    if(_isComplete)
    {
        playAni("start1",false);
        showGuide();
    }
    
}

vector<int> GameBackground::getFishIsDaily()
{
    vector<int> vec;
    for(int i = 0;i < _fishVec.size();++i)
    {
        auto item = _fishVec.at(i);
        vec.push_back(item->getIsDaily()?1:0);
    }
    return vec;
}

void GameBackground::showGuide()
{
    auto fanpai = SCENE_M->getFanPaiRewardView();
    auto seven =SCENE_M->getSevenDayView();
    if(fanpai&&fanpai->isVisible())
    {
        return;
    }
    if(seven)
    {
        return;
    }
    if(_isComplete)
    {//
        auto lobby = SCENE_M->getLobby();
        if(lobby&&lobby->isVisible()&&!GUIDE_M->isEnd(FishGuideManager::GuideType::unlockTipsOne))
        {
            auto poi = Button_build->getPosition();
            poi = Button_build->getParent()->convertToWorldSpace(poi);
            GUIDE_M->startGuide(FishGuideManager::GuideType::unlockTipsOne,this,poi);
        }
    }
}
