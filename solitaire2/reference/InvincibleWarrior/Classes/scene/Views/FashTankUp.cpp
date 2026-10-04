//
//  FashTankUp.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/31.
//

#include <stdio.h>
#include "FashTankUp.h"
#include "SceneManager.h"
#include "GameBackground.h"
#include "ShopManager.h"
#include "PlayerManager.h"
#include "FishShop.h"
#include "MainLobby.h"
#include "FishManager.h"
#include "NpcSprite.h"

#include "FishGuideManager.h"

FashTankUp::FashTankUp()
:BaseLayer("2021sceneup.csb")
{
    effectIdx = -1;
}
FashTankUp::~FashTankUp()
{
    
}


void FashTankUp::initUI()
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
    
    
    peiShiFrameVec.push_back(peiShiNameVec0);
    peiShiFrameVec.push_back(peiShiNameVec1);
    peiShiFrameVec.push_back(peiShiNameVec2);
    peiShiFrameVec.push_back(peiShiNameVec3);

    
    vector<string> imageNameVec{
        "BeiJing11.jpg",
        "BeiJing10.jpg",
        "BeiJing1.jpg",
        "BeiJing2.jpg",
    };
    
    Sprite_complete = getNode<Sprite*>("Sprite_complete");
    Sprite_BG = getNode<Sprite*>("BG");
    Sprite_reward = getNode<Sprite*>("Sprite_reward");
    FileNode_man = getNode("FileNode_man");
    
    auto shopManager = ShopManager::getInstance();
    //看看有没有
    auto fashTankidx = DATA_M->getCurrentFashTankIdx();
    
    auto vec = DATA_M->getFishTypeVec(fashTankidx);
    auto fishManager = FishManager::getInstance();
    int maxLv = 0;
    float num = 0.f;
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
    
    auto fishStr = shopManager->getFashTankFishNum(fashTankidx);
    auto fishVec = UIUtils::split(fishStr,",");
    string aniName = "";
    int frameId = -1,maxId = (int)fishVec.size()-1;
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
    _fashTankIdx = fashTankidx;
    _unlockIdx = frameId;
    
    //初始化进度
    auto LoadingBar_unlock = getNode<LoadingBar*>("LoadingBar_unlock");
    LoadingBar_unlock->setPercent((float)frameId/(float)(maxId-1) * 100);
    auto size = LoadingBar_unlock->getBoundingBox().size;
    //初始化碎片位置
    auto Node_qiPao = getNode("Node_qiPao");
    vector<string> suiPianNameVec{
        "senceicon/icon_fish1_%d.png",
        "senceicon/icon_fish2_%d.png",
        "senceicon/icon_fish3_%d.png",
        "senceicon/icon_ailisi_%d.png",
    };
    for(int i = 0;i < 9;++i)
    {
        auto item = LoadingBar_unlock->getChildByName<ImageView*>(StringUtils::format("Image_%d",i+1));
        item->setVisible(i < maxId);
        
        if(i < maxId)
        {//显示的设置位置
            float x = size.width / (maxId-1) * i;
            item->setPositionX(x);
            
            auto complete = item->getChildByName("Sprite_complete");
            complete->setVisible(i < frameId);
            
            if(i == frameId)
            {
                Node_qiPao->setPositionX(x);
            }
            
            //设置图片
            item->loadTexture(StringUtils::format(suiPianNameVec.at(fashTankidx).c_str(),i),Widget::TextureResType::PLIST);
        }
    }
    
    
    //初始化水族馆
    auto node1 = getNode("fish_Aquarium1_0");
    auto node2 = getNode("fish_Aquarium2_0");
    auto node3 = getNode("fish_Aquarium3_0");
    node1->setLocalZOrder(2000);
    node2->setLocalZOrder(2000);
    node3->setLocalZOrder(0);
    node1->setVisible(fashTankidx == 0);
    node2->setVisible(fashTankidx == 0);
    node3->setVisible(fashTankidx == 0);
    vector<string> strVec{
        "100367",
        "100368",
        "100369",
        "100370",
    };
    for(int i = 0;i < 4;++i)
    {
        auto item = getNode(StringUtils::format("Node_fashTank_%d",i));
        item->setVisible(i == fashTankidx);
        if(i == fashTankidx)
        {
            FIND_NODE(Text*, item, "Text_name")->setString(Lang(strVec.at(i)));
        }
    }
    //初始化Npc
    //人数公式（鱼缸里的所有鱼等级相加）/5.6
    //人数公式（鱼缸里的所有鱼等级相加）/5.6=结果（四舍五入取整得出人数
    
    auto Node_fashTank = getNode("Node_fashTank");
    auto num2 = num;
    if(num2 > 0&& num2 < 1)
    {
        num2 = 1;
    }
    else if(num2 > 13)
    {
        num2 = 13;
    }
    else
    {
        num2 = std::round(num2);
    }
    vector<Vector<Node*>> pathVec;
    for(int i = 0;i < 2;++i)
    {
        auto node_path = getNode(StringUtils::format("Node_path_%d_%d",fashTankidx,i));
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
    bool isHide = num2 > 6;
    int num0 = 0;
    
    for(int i = 0;i < num2;++i)
    {
        auto npc = NpcSprite::getCache()->createCacheNode(Node_fashTank);
        npc->setLocalZOrder(1);
        auto rand = random(0, 1);
        if(rand == 0)
        {
            num0++;
        }
        if(num0 > num2/3)
        {
            rand = 1;
        }
        auto vec = pathVec.at(rand);
        npc->setPath(vec,rand,isHide);
    }
    isTouch = false;
    playAni("Start0",false);
    auto startFrame = _actionManager->getStartFrame();
    auto endFrame = _actionManager->getEndFrame();
    //所需时间
    float actionTime = 1.0f/60.0f * (endFrame-startFrame);
    auto delay = DelayTime::create(actionTime);
    auto func = CallFunc::create([this,num,maxNum](){
        if(num < maxNum)
        {
            playAni("out0",false);
            auto startFrame = _actionManager->getStartFrame();
            auto endFrame = _actionManager->getEndFrame();
            //所需时间
            float actionTime = 1.0f/60.0f * (endFrame-startFrame);
            auto delay = DelayTime::create(actionTime);
            auto func = CallFunc::create([this](){
                isTouch = true;
            });
            auto seq = Sequence::createWithTwoActions(delay,func);
            this->runAction(seq);
        }
        else
        {
            playAni("lock",false);
            auto startFrame = _actionManager->getStartFrame();
            auto endFrame = _actionManager->getEndFrame();
            //所需时间
            float actionTime = 1.0f/60.0f * (endFrame-startFrame);
            auto delay = DelayTime::create(actionTime);
            auto func = CallFunc::create([this](){
                if(!GUIDE_M->isEnd(FishGuideManager::GuideType::getSuiPian))
                {
                    auto btn = getNode("Button_get");
                    auto poi = btn->getPosition();
                    poi = btn->getParent()->convertToWorldSpace(poi);
                    auto scale = getNode("Image_1")->getScale();
                    GUIDE_M->startGuide(FishGuideManager::GuideType::getSuiPian,this,poi,scale);
                }
                isTouch = true;
            });
            auto seq = Sequence::createWithTwoActions(delay,func);
            this->runAction(seq);
        }
    });
    auto seq = Sequence::createWithTwoActions(delay,func);
    this->runAction(seq);
    
    bool isComplete = num >= maxNum;
    if(!isComplete)
    {
        effectIdx = SOUND_M->playEffectMusic(EffectBuild);
    }
    
    UIUtils::playInnerAction(FileNode_man,!isComplete?"loop":"idle",!isComplete);
    Sprite_reward->setSpriteFrame(StringUtils::format(suiPianNameVec.at(fashTankidx).c_str(),frameId));
    auto poi = Sprite_reward->getPosition();
    startPoi = Sprite_reward->getParent()->convertToWorldSpace(poi);
    Sprite_complete->setVisible(isComplete);
    string str = "";
    string maxStr = UIUtils::getFloatStr(maxNum,1);
    if(num >= maxNum)
    {
        num = maxNum;
        str = UIUtils::getFloatStr(num,1);
    }
    else
    {
        str = UIUtils::getFloatStr(num,1);
    }
    
    getNode<TextBMFont*>("BitmapFontLabel_min")->setString(str);
    getNode<TextBMFont*>("BitmapFontLabel_max")->setString(maxStr);
    
    getNode<Text*>("Text_ok")->setString(Lang("100361"));
    getNode<Text*>("Text_get")->setString(Lang("100186"));
    //getNode<Text*>("Text_name")->setString(Lang("100362"));
    getNode<Text*>("Text_miaoshu1")->setString(Lang("100366"));
    getNode<Text*>("Text_miaoshu2")->setString(Lang("100371"));
}
void FashTankUp::initData()
{
    BaseLayer::initData();
    setName("FashTankUp");
}
void FashTankUp::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn || !isTouch)return;
       
    auto btnName = btn->getName();
    if(btnName == "Button_get")
    {//配饰飞出 显示动画
        DATA_M->setFashTankUnlock(_fashTankIdx,_unlockIdx);
        peiShiMove();
        
        if(GUIDE_M->getIsStartGuide(FishGuideManager::GuideType::getSuiPian)&&!GUIDE_M->isEnd(FishGuideManager::GuideType::getSuiPian))
        {
            GUIDE_M->endGuide();
        }
        if(!GUIDE_M->isEnd(FishGuideManager::GuideType::unlockOne)&&GUIDE_M->isEnd(FishGuideManager::GuideType::unlockTipsOne))
        {//解锁引导结束后 才可进行 获得碎片引导
            GUIDE_M->startGuide(FishGuideManager::GuideType::unlockOne);
        }
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_ok")
    {//去买鱼
        auto lobby = SCENE_M->getLobby();
        
        lobby->clickFishShop();
        SCENE_M->addDialog(FishShop::createLayerN());
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_close"||btnName == "Panel_6")
    {//
        SCENE_M->removeLayer(this);
    }
}


void FashTankUp::onEnter()
{
    BaseLayer::onEnter();
}
void FashTankUp::onExit()
{
    BaseLayer::onExit();
    if(effectIdx != -1)
    {
        SOUND_M->stopEffectMusic(effectIdx);
    }
}

void FashTankUp::peiShiMove()
{
    auto shopManager = ShopManager::getInstance();
    auto cuIdx = DATA_M->getCurrentFashTankIdx();
    if(_fashTankIdx == cuIdx)
    {
        auto lobby = SCENE_M->getLobby();
        auto idx = _unlockIdx;
        lobby->unlockFashTankMove(_unlockIdx,Sprite_reward->getSpriteFrame(),startPoi,[idx](){
            auto fashTank = SCENE_M->getGameBackground();
            fashTank->updateBg(idx);
        });
        
    }
}

