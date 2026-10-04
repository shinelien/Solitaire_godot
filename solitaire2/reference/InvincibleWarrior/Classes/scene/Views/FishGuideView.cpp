//
//  FishGuideView.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/30.
//

#include <stdio.h>

#include "FishGuideView.h"
#include "FishGuideManager.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"
#include "SoundManager.h"
#include "BagGameBg.h"
#include "FashTankItem.h"

FishGuideView::FishGuideView()
:BaseLayer("2021FishTips.csb")
{
    _isPlayText = false;
    _duiHuaIndex = 0;
    _isTouch = false;
    
    shouPoi = DEFAULTPOS;
    _fishMoveType = FishMoveType::None;
    clickBtn = nullptr;
    clickBtnParent = nullptr;
    isHide = false;
}

FishGuideView::~FishGuideView()
{
    
}

void FishGuideView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    FileNode_tips = getNode("FileNode_tips");
    FileNode_tips->setLocalZOrder(1);
    FileNode_shou = getNode("FileNode_shou");
    FileNode_shou->setLocalZOrder(3);
    Text_miaoshu = getNode<Text*>("Text_miaoshu");
    Text_name = getNode<Text*>("Text_name");
    Image_1 = getNode<ImageView*>("Image_1");
    Image_2 = getNode<ImageView*>("Image_2");
    Panel_1 = getNode("Panel_1");
    particle = getNode<ParticleSystemQuad*>("Particle_1");
    FileNode_JianTou = getNode("FileNode_JianTou");
    FileNode_JianTou->setVisible(false);
    Node_btn = getNode("Node_btn");
    Text_name->setString(Lang("100390"));
    FileNode_tips->setVisible(false);
    FileNode_shou->setVisible(false);
    auto Node_spine = getNode("Node_spine");
    Node_spine->setLocalZOrder(2);
    _fishWinSkeletonNode = spine::SkeletonAnimation::createFromCache("fishwin");
    Node_spine->addChild(_fishWinSkeletonNode);
    _fishWinSkeletonNode->setLocalZOrder(-1);
    _fishWinSkeletonNode->setCompleteListener([this](spTrackEntry* entry) {
        if(_fishMoveType == FishMoveType::loop)
        {
            fishPlayAni("loop",true);
            _fishMoveType = FishMoveType::None;
        }
        else if(_fishMoveType == FishMoveType::aniNum)
        {
            if(_aniNum == 2)
            {
                fishPlayAni("loop",true);
                _fishMoveType = FishMoveType::None;
            }
            _aniNum++;
        }
        else
        {
            _fishMoveType = FishMoveType::None;
        }
    });
    
    schedule(CC_CALLBACK_1(FishGuideView::updateText, this),0.05f,"updateText");
}

void FishGuideView::initData()
{
    BaseLayer::initData();
}

void FishGuideView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn||!_isTouch)return;

    auto btnName = btn->getName();
    
    if(btnName == "Panel_1")
    {//
        GUIDE_M->endGuide((FishGuideManager::GuideType)_guideType,this,_idx);
    }
}

void FishGuideView::onEnter()
{
    BaseLayer::onEnter();
}

void FishGuideView::onExit()
{
    BaseLayer::onExit();
}

void FishGuideView::setGuideType(int type)
{
    _guideType = type;
}

void FishGuideView::startGuide(string tips)
{
    vector<string> miaoShuVec{
        Lang("100380"),
        Lang("100381"),
        Lang("100382"),
        Lang("100383"),
                "",
        Lang("100384"),
                "",
        Lang("100385"),
        Lang("100386"),
        Lang("100387"),
        Lang("100388"),
        Lang("100402"),
        "",
        "",
        "",
        Lang("100403"),
    };
    vector<string> miaoShuEnVec{
        "Welcome to the Solitaire Aquarium.Let’s start playing the first level!",
        "Wow! 4 times bonus!",
        "Try the magic!",
        "Look! Have a gift.",
        "",
        "See what’s in the store.",
        "",
        "Got a clown fish.",
        "Wow,look this.",
        "Wow! The workers built an ornament. Take it.",
        "The aquarium looks better Buy more beautiful fish!",
        "You have a new scene",//"你有新的场景",
        "",
        "",
        "",
        "Welcome to the new venue. You need to buy fish again to attract more tourists.",//"欢迎来到新的场馆，需要重新购买鱼吸引更多游客喔",
    };
    string miaoShuEn = "";
    bool isTouch = true;
    bool isTipsShow = true;
    
    _fishMoveType = FishMoveType::None;
    string fishAni = "loop";
    bool isLoop = false;
    bool isPlayText = false;
    _aniNum = 0;
    if(_guideType == (int) FishGuideManager::GuideType::StartOne)
    {
        playAni("start",false);
        
        isPlayText = true;
        //No down happy loop think up yes
        _fishMoveType = FishMoveType::loop;
        fishAni = "happy";
        isLoop = false;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::WinOne)
    {
        auto node = dynamic_cast<BaseLayer*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_doubleWin");
            isTouch = false;
        }
        
        playAni("win",false);
        
        isPlayText = true;
        _fishMoveType = FishMoveType::aniNum;
        fishAni = "up";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::NoMove)
    {
        auto node = dynamic_cast<BaseLayer*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_Shuffle");
            
        }
        
        playAni("nomove",false);
        
        isPlayText = true;
        _fishMoveType = FishMoveType::aniNum;
        
        fishAni = "down";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::Three||_guideType == (int) FishGuideManager::GuideType::unlockFashTank)
    {
        
        auto node = dynamic_cast<BaseLayer*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_pause");
            
        }
        playAni("three",false);
        
        isPlayText = true;
        _fishMoveType = FishMoveType::aniNum;
        fishAni = "down";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::LobbyOne||_guideType == (int) FishGuideManager::GuideType::gotoLobby)
    {
        auto node = dynamic_cast<BaseLayer*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_Lobby");
            
        }
        isPlayText = false;
        isTipsShow = false;
        playAni("Lobby",false);
        _fishMoveType = FishMoveType::aniNum;
        fishAni = "yes";
        isLoop = true;
        
    }
    else if(_guideType == (int) FishGuideManager::GuideType::ClickFishShop)
    {
        auto node = dynamic_cast<BaseLayer*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_shopping");
            
        }
        
        isPlayText = true;
        playAni("clickShop",false);
        _fishMoveType = FishMoveType::aniNum;
        fishAni = "down";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::FishShopOne)
    {
        auto node = dynamic_cast<BagGameBg*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_gameBg");
            node->setIsTouch(true);
            isTouch = false;
        }
        isPlayText = false;
        isTipsShow = false;
        playAni("buyFish",false);
        _fishMoveType = FishMoveType::aniNum;
        fishAni = "up";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::GetFishOne)
    {
        
        isPlayText = true;
        playAni("getFish",false);
        _fishMoveType = FishMoveType::loop;
        fishAni = "happy";
        isLoop = false;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::unlockTipsOne)
    {
        auto node = dynamic_cast<BaseLayer*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Node_bulid");
        }
        
        
        isPlayText = true;
        playAni("unlockTips",false);
        _fishMoveType = FishMoveType::aniNum;
        
        fishAni = "up";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::getSuiPian)
    {
        auto node = dynamic_cast<BaseLayer*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_get");
        }
        
        
        isPlayText = true;
        playAni("unlockTips",false);
        _fishMoveType = FishMoveType::aniNum;
        
        fishAni = "up";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::unlockOne)
    {
        
        
        isPlayText = true;
        playAni("unlock",false);
        _fishMoveType = FishMoveType::loop;
        fishAni = "happy";
        isLoop = false;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::ClickFashTank)
    {
        auto node = dynamic_cast<BaseLayer*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_shopping_fish");
            
        }
        
        isPlayText = false;
        isTipsShow = false;
        playAni("Lobby",false);
        _fishMoveType = FishMoveType::aniNum;
        fishAni = "down";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::UseFashTank)
    {
        auto node = dynamic_cast<FashTankItem*>(targetNode);
        if(node)
        {
            clickBtn = node->getNode("Button_goFashTank");
            node->setIsTouch(true);
            //isTouch = false;
        }
        isPlayText = false;
        isTipsShow = false;
        playAni("buyFish",false);
        _fishMoveType = FishMoveType::aniNum;
        fishAni = "up";
        isLoop = true;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::UseFashTankTipsOne)
    {
        
        isPlayText = true;
        playAni("getFish",false);
        _fishMoveType = FishMoveType::loop;
        fishAni = "happy";
        isLoop = false;
    }
    else if(_guideType == (int) FishGuideManager::GuideType::None)
    {
        miaoShuEn = "The fish tank is full, and you need to sell the fish or replace the new venue.";
        isPlayText = true;
        playAni("getFish",false);
        _fishMoveType = FishMoveType::loop;
        fishAni = "No";
        isLoop = false;
    }
    _isTipsShow = isTipsShow;
    if(clickBtn)
    {
        //jiaohuan(true);
        
    }
    auto str = _guideType == (int) FishGuideManager::GuideType::None?tips:miaoShuVec.at(_guideType);
    auto l1 = (int)str.length();
    Text_miaoshu->setString(str);
    _duiHuaVec.clear();
    str = _guideType == (int) FishGuideManager::GuideType::None?miaoShuEn:miaoShuEnVec.at(_guideType);
    auto l2 = (int)str.length();
    auto languageCode = DATA_M->getAllDyyStr();
    int num = l2,tempNum = 0;
    if(languageCode == "zh"||languageCode == "tw"||languageCode == "ja"||languageCode == "ko")
    {
        num = l1 / 2;
    }
    _duiHuaIndex = 0;
    for(int i = 0;i < str.length();++i)
    {
        char c = str[i];
        if(c == ','||c == '\''||c == '!'||c == '.'||c == ' ') continue;
        if(tempNum >= num)break;
        _duiHuaVec.push_back(c);
        tempNum++;
    }
    
    _isTempTouch = isTouch;
    
    float fishTime = 0.0f;
    float textTime = 0.0f;

    //鱼
    _fishWinSkeletonNode->setScale(0.5f);
    _fishWinSkeletonNode->setVisible(false);
    auto fishDelayTime = DelayTime::create(fishTime);
    auto fishFunc = CallFunc::create([this,fishAni,isLoop](){
        //粒子
        particle->resetSystem();
        //鱼
        _fishWinSkeletonNode->setVisible(true);
        fishPlayAni(fishAni, isLoop);
        float time = 1.0f;
        auto scale = ScaleTo::create(time, 1.0f);
        auto back = EaseBackOut::create(scale);
        _fishWinSkeletonNode->runAction(back);
        
    });
    auto fishSeq = Sequence::create(fishDelayTime, fishFunc, NULL);
    
    //文本
    auto textDelayTime = DelayTime::create(textTime);
    auto textFunc = CallFunc::create([this,isTipsShow,isTouch,isPlayText,fishAni,isLoop](){
        FileNode_tips->setVisible(isTipsShow);
        //文本
        auto actionManager = UIUtils::playInnerAction(FileNode_tips,"start",false,[this,isTipsShow](){
            
        });
        actionManager->setFrameEventCallFunc([this,fishAni,isLoop](Frame* frame){
            auto e = dynamic_cast<EventFrame*>(frame);
            auto msg = e->getEvent();
            if(msg == "event_eff")
            {
                //开始语音
                _isPlayText = true;//isPlayText;
            }
        });
    });
    
    auto textSeq = Sequence::create(textDelayTime,textFunc, NULL);
    
    
    auto seq = Sequence::create(textSeq,fishSeq, NULL);
    this->runAction(seq);
    
    auto textSize = Text_miaoshu->getContentSize();
    auto imageSize = Image_1->getContentSize();
    auto width = textSize.width + 100.0f;
    imageSize.width = width > 600?width:600;
    imageSize.height = textSize.height + 130.0f;
    Image_1->setContentSize(imageSize);
    //300 - 100 230 - 220;
    Text_miaoshu->setPosition(imageSize/2);
    Image_2->setPosition(Vec2(100,imageSize.height-10));
    FileNode_JianTou->setPosition(Vec2(imageSize.width/2,5));
}

void FishGuideView::updateText(float dt)
{
    if(_isPlayText)
    {
        if(_duiHuaIndex >= _duiHuaVec.size())
        {
            //FileNode_tips->setVisible(false);
            _isTouch = _isTempTouch;
            FileNode_JianTou->setVisible(true);
            UIUtils::playInnerAction(FileNode_JianTou,"start",true);
            if(shouPoi != DEFAULTPOS)
            {
                FileNode_shou->setVisible(true);
                if(_guideType == (int) FishGuideManager::GuideType::Three)
                {
                    auto parent = clickBtn->getParent();
                    auto poi = clickBtn->getPosition();
                    shouPoi = parent->convertToWorldSpace(poi);
                }
                shouPoi = FileNode_shou->getParent()->convertToNodeSpace(shouPoi);
                FileNode_shou->setPosition(shouPoi);
                UIUtils::playInnerAction(FileNode_shou,"Start0",true);
                if(clickBtn)
                {
                    jiaohuan(true);
                }
            }
            _isPlayText = false;
            return;
        }
        char c = _duiHuaVec.at(_duiHuaIndex);
        _duiHuaIndex++;
        
        
        
        //音效
        SOUND_M->playTextEffect(c);
    }
}

void FishGuideView::fishPlayAni(string aniName,bool loop,float speed)
{
    auto spTrackEntry = _fishWinSkeletonNode->setAnimation(0, aniName, loop);
    spTrackEntry->timeScale = speed;
}

void FishGuideView::jiaohuan(bool isJiaoHuan)
{
    if(isJiaoHuan)
    {
        //计算缩放
        auto node2 = getNode("Node_1");
        if(node2)
        {
            auto scale = node2->getScale();
            auto sc = _btnScale/scale;
            Node_btn->setScale(sc);
        }
 
        clickBtnParent = clickBtn->getParent();
        clickBtnPoi = clickBtn->getPosition();
        localZOder = clickBtn->getLocalZOrder();
        clickBtn->retain();
        clickBtn->removeFromParentAndCleanup(false);
        Node_btn->addChild(clickBtn);
        clickBtn->release();
        auto poi = clickBtnParent->convertToWorldSpace(clickBtnPoi);
        poi = Node_btn->convertToNodeSpace(poi);
        clickBtn->setPosition(poi);
        clickBtn->setLocalZOrder(0);
    }
    else if(clickBtnParent)
    {
        clickBtn->retain();
        clickBtn->removeFromParentAndCleanup(false);
        clickBtnParent->addChild(clickBtn);
        clickBtn->release();
        clickBtn->setPosition(clickBtnPoi);
        clickBtn->setLocalZOrder(localZOder);
    }
}

void FishGuideView::hide()
{
    if(isHide) return;
    isHide = true;
    if(clickBtn)
        jiaohuan(false);
    _fishWinSkeletonNode->setVisible(false);
    FileNode_shou->setVisible(false);
    FileNode_JianTou->setVisible(false);
    Node_btn->setVisible(false);
    UIUtils::playInnerAction(FileNode_tips,"hide",false,[this](){
        this->removeFromParent();
    });
}

void FishGuideView::setIdx(int idx)
{
    _idx = idx;
}
