//
//  GameRewardsView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/4.
//

#include <stdio.h>
#include "GameRewardsView.h"
#include "ScoreManager.h"
#include "SoundManager.h"
#include <spine/spine-cocos2dx.h>
#include "spine/spine.h"

std::string nameArr[] = {"Fristscore_","Wintimes_","Bestscore0_","Bestscore1_"};

GameRewardsView::GameRewardsView()
:BaseLayer("2020Gamerewards.csb")
{
    
    _yday = GETINTEGER("GameRewardsyDay",0);
    initDayData();//内部判断是否初始化
    oneOldScore = GETINTEGER("oneOldScore",0);
    threeOldScore = GETINTEGER("threeOldScore",0);;
    for(int i = 0;i<4;++i)
    {
        if(i == (int)GameRewardsView::Type::MaxScore)
        {
            auto one = ScoreManager::getInstance()->getScore(1,ScoreManager::Type::BESTSCORE);
            auto three = ScoreManager::getInstance()->getScore(1,ScoreManager::Type::BESTSCORE);
            oneCardScores.push_back(GETINTEGER(StringUtils::format("oneRewards%d",i).c_str(),one));
            threeCardScores.push_back(GETINTEGER(StringUtils::format("threeRewards%d",i).c_str(),three));
        }
        else
        {
            oneCardScores.push_back(GETINTEGER(StringUtils::format("oneRewards%d",i).c_str(),0));
            threeCardScores.push_back(GETINTEGER(StringUtils::format("threeRewards%d",i).c_str(),0));
        }
    }
}
GameRewardsView::~GameRewardsView()
{
    
}

void GameRewardsView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    BitmapFontLabel_1 = getNode<TextBMFont*>("BitmapFontLabel_1");
    Panel_zh = getNode("Panel_zh");
    Panel_tw = getNode("Panel_tw");
    Panel_en = getNode("Panel_en");
    Panel_ja = getNode("Panel_ja");
    Panel_ko = getNode("Panel_ko");
    Panel_level = getNode("Panel_level");
    
    auto Node_spine = getNode("Node_spine");
    _fishWinSkeletonNode = spine::SkeletonAnimation::createFromCache("fishwin");
    Node_spine->addChild(_fishWinSkeletonNode);
    //No down happy loop think up yes
}

void GameRewardsView::hideUI()
{
    Panel_zh->setVisible(false);
    Panel_tw->setVisible(false);
    Panel_en->setVisible(false);
    Panel_ja->setVisible(false);
    Panel_ko->setVisible(false);
    
    auto vec_zh = Panel_zh->getChildren();
    for(auto node:vec_zh)
    {
        node->setVisible(false);
    }
    
    auto vec_tw = Panel_tw->getChildren();
    for(auto node:vec_tw)
    {
        node->setVisible(false);
    }
    
    auto vec_en = Panel_en->getChildren();
    for(auto node:vec_en)
    {
        node->setVisible(false);
    }
    
    auto vec_ja = Panel_ja->getChildren();
    for(auto node:vec_ja)
    {
        node->setVisible(false);
    }
    
    auto vec_ko = Panel_ko->getChildren();
    for(auto node:vec_ko)
    {
        node->setVisible(false);
    }
    
    Panel_level->setVisible(false);
}

void GameRewardsView::initData()
{
    BaseLayer::initData();
    setName("GameRewardsView");
}
void GameRewardsView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto name = btn->getName();
    if(name == "")
    {
        
    }
}

void GameRewardsView::updateUI(int score,int exp,std::function<void()> cb)
{
    //如果是第二天的第一局，在游戏中更新数据，
    initDayData();
    
    hideUI();
    SOUND_M->playEffectMusic(EffectGetWin);
    getNode<TextBMFont*>("BitmapFontLabel_exp")->setString(StringUtils::format("+%d",exp));
    
    getNode<Text*>("Text_1_0")->setString(Lang("100290"));
    getNode<Text*>("Text_1_0_level")->setString(Lang("100290"));
//   auto Text_1_0 = getNode("Text_1_0");
//    auto Money_Star_1_1 = getNode("Money_Star_1_1");
//    auto text_2 = getNode("Text_2");
//    //适配位置
//    auto size = Text_1_0->getContentSize();
//    auto spsize = Money_Star_1_1->getContentSize();
//    Money_Star_1_1->setPositionX(size.width);
//    text_2->setPositionX(size.width + spsize.width);
    
    auto Text_1_0_level = getNode("Text_1_0_level");
    auto Money_Star_1_1_level = getNode("Money_Star_1_1_level");
    auto Text_2_level = getNode("Text_2_level");
    //适配位置
    auto levelsize = Text_1_0_level->getContentSize();
    auto levelspsize = Money_Star_1_1_level->getContentSize();
    Money_Star_1_1_level->setPositionX(levelsize.width);
    Text_2_level->setPositionX(levelsize.width + levelspsize.width);
    
    
    getNode<Text*>("Text_30_level")->setString(Lang("100298"));
    
    //只需要判断部分语言
    std::string languageCode = DATA_M->getSectionDyyStr();
    
    isThree = DATA_M->getIsThreeModel();
    auto &scoreVec = !isThree?oneCardScores:threeCardScores;
    
    //关卡
    if(score == 0)
    {
        getNode("Panel_1")->setVisible(false);
        getNode<Text*>("Text_2_level")->setString(StringUtils::format("x%d",exp));
        Panel_level->setVisible(true);
        playAni("Start0",false,cb);
        auto FileNode_Level = getNode("FileNode_Level");
        UIUtils::playInnerAction(FileNode_Level, "KingLoop", true);
        return;
    }
    getNode("Panel_1")->setVisible(true);
    //历史最高分
    auto maxScore = scoreVec[(int)Type::MaxScore];
    if(score > maxScore)
    {
        auto panelname = StringUtils::format("Panel_%s",languageCode.c_str());
        auto name = nameArr[(int)GameRewardsView::Type::MaxScore] + languageCode;
        auto panel = getNode(panelname);
        if (panel)
            panel->setVisible(true);
        auto child = panel->getChildByName(name);
        if (child)
            child->setVisible(true);
        
        BitmapFontLabel_1->setVisible(true);
        BitmapFontLabel_1->setString(StringUtils::toString(score));
        this->setVisible(true);
        getNode("Particle_crownlight")->setVisible(true);
        playAni("Start0",false,cb);
        _fishWinSkeletonNode->setAnimation(0, "happy", true);
        return;
    }
    
    //首胜
    auto firstNum = scoreVec[(int)Type::First];
    if(firstNum == 0)
    {//是首胜
        auto panelname = StringUtils::format("Panel_%s",languageCode.c_str());
        auto name = nameArr[(int)GameRewardsView::Type::First] + languageCode;
        auto panel = getNode(panelname);
        if (panel)
            panel->setVisible(true);
        auto child = panel->getChildByName(name);
        if (child)
            child->setVisible(true);
        
        
        BitmapFontLabel_1->setVisible(false);
        this->setVisible(true);
        getNode("Particle_crownlight")->setVisible(true);
        playAni("Start0",false,cb);
        _fishWinSkeletonNode->setAnimation(0, "happy", true);
        return;
    }
    
    //今日最高分
    auto dayScore = scoreVec[(int)Type::DayScore];
    if(score > dayScore)
    {
        auto panelname = StringUtils::format("Panel_%s",languageCode.c_str());
        auto name = nameArr[(int)GameRewardsView::Type::DayScore] + languageCode;
        auto panel = getNode(panelname);
        if (panel)
            panel->setVisible(true);
        auto child = panel->getChildByName(name);
        if (child)
            child->setVisible(true);
        BitmapFontLabel_1->setVisible(true);
        BitmapFontLabel_1->setString(StringUtils::toString(score));
        this->setVisible(true);
        getNode("Particle_crownlight")->setVisible(true);
        playAni("Start0",false,cb);
        _fishWinSkeletonNode->setAnimation(0, "happy", true);
        return;
    }
    
    //连胜
    auto win = scoreVec[(int)Type::Win];
    if(win >= 1)
    {
        auto panelname = StringUtils::format("Panel_%s",languageCode.c_str());
        auto name = nameArr[(int)GameRewardsView::Type::Win] + languageCode;
        auto panel = getNode(panelname);
        panel->setVisible(true);
        auto child = panel->getChildByName(name);
        if (child)
            child->setVisible(true);
        TextBMFont* text = child? child->getChildByName<TextBMFont*>(StringUtils::format("BitmapFontLabel_%s",languageCode.c_str())):nullptr;
        if (text)
            text->setString(StringUtils::toString(win + 1));
        BitmapFontLabel_1->setVisible(false);
        this->setVisible(true);
        auto st =  StringUtils::format("%s",languageCode.c_str());
        if(text && (st == "zh"||st == "tw"||st == "en"))
        {
            
            auto Ci = text->getChildByName(StringUtils::format("yuyan_Win0_%s",languageCode.c_str()));
            auto size = text->getContentSize();
            if (Ci)
                Ci->setPositionX(size.width+11);
        }
        
        
        
        getNode("Particle_crownlight")->setVisible(true);
        playAni("Start0",false,cb);
        _fishWinSkeletonNode->setAnimation(0, "happy", true);
        return;
    }
    
    
    
    getNode("Particle_crownlight")->setVisible(false);
    BitmapFontLabel_1->setVisible(false);
    //在此中断。不是关卡，没有连胜，没有最高分，不是首胜，不是今日最高分，
    //用户更新后的第一局，所有信息都是0 ，应该在历史最高分就return，不是第一局的问题
    //更新数据在第二天再次登陆，除历史最高分外，全部归零 应该在首胜return
    //没有更新时再次完成对局
    this->setVisible(true);
    playAni("Start0",false,cb);
    _fishWinSkeletonNode->setAnimation(0, "happy", true);
}

void GameRewardsView::setScore(int gameType,bool isWin,int score)
{
    auto &scoreVec = gameType==1?oneCardScores:threeCardScores;
    auto &scoreVec2 = !(gameType==1)?oneCardScores:threeCardScores;

    if(isWin)
    {
        //记录今日胜利次数一直累计 单张三张一起算
        auto firstNum = scoreVec[(int)Type::First];
        firstNum++;
        scoreVec[(int)Type::First] = firstNum;
        
        auto firstNum2 = scoreVec2[(int)Type::First];
        firstNum2++;
        scoreVec2[(int)Type::First] = firstNum2;
        
        
        //记录连胜 失败的话归零  单张三张一起算
        auto win = scoreVec[(int)Type::Win];
        win++;
        scoreVec[(int)Type::Win] = win;
        
        auto win2 = scoreVec2[(int)Type::Win];
        win2++;
        scoreVec2[(int)Type::Win] = win;
        
        
        //记录历史最高分
        auto maxScore = scoreVec[(int)Type::MaxScore];
        if(maxScore < score)
        {
            scoreVec[(int)Type::MaxScore] = score;
        }
        //记录今日最高分
        auto dayScore = scoreVec[(int)Type::DayScore];
        if(dayScore < score)
        {
            scoreVec[(int)Type::DayScore] = score;
        }
    }
    updateData();
}

void GameRewardsView::updateData()
{
    for(int i =0;i<4;++i)
    {
        auto onedata = oneCardScores.at(i);
        SETINTEGER(StringUtils::format("oneRewards%d",i).c_str(),onedata);
        auto threedata = threeCardScores.at(i);
        SETINTEGER(StringUtils::format("threeRewards%d",i).c_str(),threedata);
    }
}

void GameRewardsView::initDayData()
{//判断 如果是新的一天 初始化数据
    auto yday = DATA_M->getYDay();
    if(_yday != yday)
    {
        _yday = yday;
        SETINTEGER("GameRewardsyDay",yday);
        for(int i =0;i<4;++i)
        {
            if(i == (int)GameRewardsView::Type::MaxScore)
            {//最高分不清空
                continue;
            }
            SETINTEGER(StringUtils::format("oneRewards%d",i).c_str(),0);
            SETINTEGER(StringUtils::format("threeRewards%d",i).c_str(),0);
        }
    }
}

void GameRewardsView::initDayWin()
{
    auto &vec = oneCardScores;
    auto &vec2 = threeCardScores;
    vec[(int)GameRewardsView::Type::Win] = 0;
    vec2[(int)GameRewardsView::Type::Win] = 0;
    SETINTEGER(StringUtils::format("oneRewards%d",(int)GameRewardsView::Type::Win).c_str(),0);
    SETINTEGER(StringUtils::format("threeRewards%d",(int)GameRewardsView::Type::Win).c_str(),0);
}
