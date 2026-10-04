//
//  RankView.cpp
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/11.
//

#include <cstdio>
#include "RankView.h"
#include "MainLobby.h"
#include "GameViewHD.hpp"
#include "EventObserver.h"
#include "RankItem.h"
#include "external/json/document.h"
#include "ScoreManager.h"
#include "RankManager.hpp"
#include "RankFashTank.h"
#include  <regex.h>
const int OneDaySec = 60*60*24;
RankView::RankView(RankType type)
:BaseLayer("2021Rank.csb")
{
    _type = type;
    
}
RankView::~RankView()
{
    
}

void RankView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    _scrollView = getNode<ScrollView*>("ScrollView_1");
    getNode("Button_look_one")->setVisible(false);
    getNode("Button_look_0")->setVisible(false);
    getNode("Button_setName")->setVisible(false);
    
    timeParent = getNode("time0_bg0_1");
    timeParent->setVisible(false);
    auto Text_hour = getNode<TextBMFont*>("BitmapFontLabel_hour");
    auto Text_min = getNode<TextBMFont*>("BitmapFontLabel_min");
    Text_hour->setString(StringUtils::format("%02d",0));
    Text_min->setString(StringUtils::format("%02d",0));
    auto Sprite_JiangBei = getNode<Sprite*>("Sprite_JiangBei");
    Sprite_JiangBei->setVisible(false);
    playAni("Start0",false);
        
    Panel_setName = getNode("Panel_setName");
    TextField_name = getNode<TextField*>("TextField_1");
    //设置占位文本 setPlaceHolder
    //设置占位文本颜色 setPlaceHolderColor
    //设置输入文本颜色 void setTextColor(const Color4B& textColor);
    //设置输入文本大小 setFontSize(int size);
    //得到输入文本 getString()
    //设置输入文本长度 setMaxLength(int length);
    //回调addEventListener std::function<void(Ref*, EventType)>
    TextField_name->setMaxLengthEnabled(true);
    TextField_name->setMaxLength(10);
    TextField_name->addEventListener([this](Ref* ref, TextField::EventType evenType){
        if(evenType == TextField::EventType::ATTACH_WITH_IME)
        {
            log("ATTACH_WITH_IME");
            Panel_setName->setVisible(true);
        }
        else if(evenType == TextField::EventType::DETACH_WITH_IME)
        {
            log("DETACH_WITH_IME");
            Panel_setName->setVisible(false);
        }
        else if(evenType == TextField::EventType::INSERT_TEXT)
        {
            auto text = dynamic_cast<TextField*>(ref);
            if(text)
            {
                string str = text->getString();
                
                bool  isCorrect= true;
                char  ss[200] = {0};
                regmatch_t pmatch[4];
                regex_t match_regex;
                sprintf(ss,  "%s" , str.c_str());
                regcomp(&match_regex, "^[A-Za-z0-9]+$" , REG_EXTENDED);
                //regcomp(&match_regex, "^[\u4E00-\u9FA5A-Za-z0-9_]+$" ,REG_EXTENDED);
                
                if  (regexec(&match_regex, ss, 4, pmatch, 0) != 0)
                {
                    isCorrect= false;
                }

                if(!isCorrect)
                {
                    text->setString(oldStr);
                    str = oldStr;
                }
                regfree(&match_regex);
                int len = str.length();
                string textStr = "";
                int strNum = 0;
                for(int i = 0;i < len;++i)
                {
                    auto c = str[i];
                    bool  isCorrect= true;
                    char  ss[200] = {0};
                    int j = c;
                    if(j < 0)
                    {
                        string s = "aaa";//str.substr(i,i+2);
                        s[0] = c;
                        for(int k = 1;k < 3;++k)
                        {
                            auto c1 = str[i+k];
                            s[k] = c1;
                        }
                        i = i + 2;
                        sprintf(ss,  "%s" , s.c_str());
                        textStr = textStr + ss;
                    }
                    else
                    {
                        sprintf(ss,  "%c" , c);
                        textStr = textStr + c;
                    }
                    
                    
                    //sprintf(ss,  "%s" , str.c_str());
                    
                    regmatch_t pmatch[4];
                    regex_t match_regex;

                    regcomp(&match_regex, "[\u4e00-\u9fa5]$" , REG_EXTENDED);//中文
                    //regcomp(&match_regex, "^[\u4E00-\u9FA5A-Za-z0-9_]+$" ,REG_EXTENDED);
                    //
                    if  (regexec(&match_regex, ss, 4, pmatch, 0) != 0)
                    {
                        isCorrect= false;
                    }
                    regfree(&match_regex);
                    if(isCorrect)
                    {
                        strNum += 2;
                    }
                    else
                    {
                        strNum++;
                    }
                    if(strNum <= 10)
                    {
                        oldStr = textStr;
                    }
                }
                auto si = oldStr.size();
                if(strNum > 10&&!oldStr.empty())
                {
                    text->setString(oldStr);
                }
                
                log("INSERT_TEXT");
            }
        }
        else if(evenType == TextField::EventType::DELETE_BACKWARD)
        {
            auto text = dynamic_cast<TextField*>(ref);
            if(text)
            {
                oldStr = text->getString();
            }
            log("DELETE_BACKWARD");
        }
    });
    
    
}
void RankView::initData()
{
    BaseLayer::initData();
    setName("RankView");
    EVENT_M->addListener("msg_rank_update", [this](ValueMap valueMap, void *obj){
        updateUI();
        unschedule("cancel_loading_key");
    }, this);
    EVENT_M->addListener("msg_rank_update_cancel", [this](ValueMap valueMap, void *obj){
        SCENE_M->showTips(Lang("100078"));
        SCENE_M->removeLoading();
        unschedule("cancel_loading_key");
    }, this);
    scheduleOnce([](float){
        SCENE_M->showTips(Lang("100078"));
        SCENE_M->removeLoading();
    }, 10, "cancel_loading_key");
}
void RankView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
       
    auto btnName = btn->getName();
    if(btnName == "Button_close"||btnName == "Panel_top_0")
    {
        SCENE_M->removeLayer(this);
        SCENE_M->removeLoading();
        auto gameView = SCENE_M->getGameView();
        if(_type == RankView::RankType::GameView)
        {
            
            gameView->gamePause(false);//解除暂停
            gameView->setIsOpenTipsTime(true);
        }
        else if(_type == RankView::RankType::WinLayer)
        {
            gameView->updateRank();
        }
    }
    else if(btnName == "Button_look_one")
    {
        auto size = _scrollView->getInnerContainerSize();
        auto node = RankFashTank::createLayerN();
        SCENE_M->addDialog(node);
        node->initRankFashTank(NULL,this);
    }
    else if(btnName == "Button_setName")
    {
        oldStr = "";
        TextField_name->setString("");
        playAni("name",false);
    }
    else if(btnName == "Button_set")
    {
        auto str = TextField_name->getString();
        if(str.find(" ") != string::npos)
        {
            
        }
        else
        {
            UIUtils::RequestCK("ck", {{"w", Value(str)}}, [this, str](HttpClient* client, HttpResponse* response){
                if (response->getResponseCode() == 200) {
                    auto dataVec = response->getResponseData();
                    
                    string data(dataVec->begin(), dataVec->end());
                    rapidjson::Document d;
                    d.Parse<0>(data.c_str());
                    if (d.HasParseError()) return;
                    if (d.HasMember("r") && d["r"].GetInt() == 1) {
                        DATA_M->setMyName(str);
                        updateName();
                        UIUtils::updateScore(0, 0);
                    }
                    else {
                        SCENE_M->showTips(Lang("100379"));
                    }
                }
                else
                {
                    SCENE_M->showTips(Lang("100078"));
                }
            });
        }
        
        playAni("idle",false);
    }
    else if(btnName == "Button_no")
    {
        playAni("idle",false);
    }
    else if(btnName == "Button_look_0")
    {//领取奖励
        DATA_M->resetRank();
        auto lobby = SCENE_M->getLobby();
        auto gameView = SCENE_M->getGameView();
        auto rankType = _type;
        auto goldPoi = gameView->getGoldWorldPoi();
        if(rankType == RankView::RankType::Lobby)
        {
            goldPoi = lobby->getGoldWorldPoi();
        }
        if(rankType == RankView::RankType::GameView)
        {
            goldPoi = gameView->getGoldWorldPoi();
            gameView->playAni("top0",false);
        }
        gameView->updateRandReward();
        auto poi = Director::getInstance()->getWinSize()*0.5;
        lobby->goldAni(_rankPrice,nullptr,poi,[this,lobby](){
            DATA_M->setCoinNum(_rankPrice, true, 125);
            ValueMap valueMap{
                {"isTime",Value{true}}
            };
            //更新有金币显示
            EVENT_M->sendEvent("event_game_update_coin",valueMap);
            //SCENE_M->getLobby()->updateCoin(true);

        },[lobby](){
            //home
            //SOUND_M->playEffectMusic(EffectGetCoin);
            lobby->playGoldAni(1,true);
        },[lobby,gameView](){
            
            lobby->playGoldAni(1,false);
            gameView->playAni("in",false);
        },goldPoi);
        getNode("Button_look_0")->setVisible(false);
    }
}


void RankView::onEnter()
{
    BaseLayer::onEnter();
    
    //getNode<Text*>("text_title")->setString(Lang("100038"));
//    updateUI();
    SCENE_M->showLoading();
    UIUtils::updateRank(1);
//    SCENE_M->getGameView()->showNode("Panel_top", false);
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("OpenRankView")},
    });
}

void RankView::onExit()
{
    BaseLayer::onExit();
    //窗口关闭
    auto lobby = SCENE_M->getLobby();
    auto gameview = SCENE_M->getGameView();
    if(gameview->isVisible())
    {//恢复游戏 取消暂停
        gameview->gamePause(false);
    }
    else if(lobby)
    {
        lobby->isShowTop(true);
    }
    if(lobby)
    {
        lobby->updataBagNew();
    }
    
    EVENT_M->removeListener("msg_rank_update",this);
    EVENT_M->removeListener("msg_rank_update_cancel",this);
    
//    SCENE_M->getGameView()->showNode("Panel_top", true);
}

void RankView::updateUI() {
    _myRankItem = NULL;
    auto gameView = SCENE_M->getGameView();
    rankArr = gameView->getRankArr();
    auto rank = gameView->getMyRank();
    _myRank = rank;

    DATA_M->setRank(rank);
    updateName();
    getNode<Text*>("Text_myRank")->setString(rank==MAX_RANK?"300+":StringUtils::format("%d",rank));
    getNode<Text*>("Text_myScore")->setString(StringUtils::toString(UIUtils::getP1()));
    
    //getNode<Text*>("Text_rank")->setString(Lang("100327"));
    getNode<Text*>("Text_name")->setString(Lang("100328"));
    getNode<Text*>("Text_fish")->setString(Lang("100329"));
    getNode<Text*>("Text_score")->setString(Lang("100103"));
    
    getNode<Text*>("Text_set")->setString(Lang("100343"));
    getNode<Text*>("Text_no")->setString(Lang("100344"));
    getNode<Text*>("Text_name_miaoshu")->setString(Lang("100377"));
    
    auto Sprite_JiangBei = getNode<Sprite*>("Sprite_JiangBei");
    Sprite_JiangBei->setVisible(rank <= 3);
    if(rank <= 3)
    {
        Sprite_JiangBei->setSpriteFrame(StringUtils::format("JiangBei_%d.png",103-rank));
    }

    const auto list = RankManager::getInstance()->getRankList();
    auto &rankItem = list.at(0);
    _lv = rankItem.getLv();
    _name = rankItem.getName();
    _score = rankItem.getP1();
    _fashTankId = rankItem.getFishTankIdx();
    _fishVec = rankItem.getFishVec();
    _isDailyVec = rankItem.getIsDailyVec();

    _isFashTankUnlockVec = rankItem.getIsFashTankUnlockVec();
    _cy = rankItem.getCy();
    _key = rankItem.getKey();
    if(rank == 1)
    {//自己是第一就不要查看了
        getNode("Button_look_one")->setVisible(false);
    }
    getNode("Button_setName")->setVisible(true);
    _rankPrice = 0;
    auto isReward = DATA_M->getIsRankReward();
    auto oldRank = DATA_M->getOldRank();
    if(isReward&&oldRank <= 100&&oldRank != -1)
    {//到了领奖的时候了
        //1. 600
        //2. 350
        //3. 200
        //前100. 100
        log("_rankPrice1 : %d", _rankPrice);
        vector<int> rewards = {600,350,200};
        if(oldRank <= rewards.size())
        {
            _rankPrice = rewards.at(oldRank-1);
        }
        else
        {
            _rankPrice = 100;
        }
        log("_rankPrice : %d", _rankPrice);
        getNode<Text*>("Text_Bounes")->setString(Lang("100062"));
        getNode<TextBMFont*>("BitmapFontLabel_reward")->setString(StringUtils::toString(_rankPrice));
    }
    getNode("Button_look_0")->setVisible(_rankPrice != 0&&_type != RankView::RankType::WinLayer);
    
    getNode<Text*>("Text_rankName_one")->setString(_name);
    getNode<Text*>("Text_rankScore_one")->setString(StringUtils::toString(_score));
    getNode<Text*>("Text_look_one")->setString(Lang("100326"));
    auto Text_miaoshu = getNode<Text*>("Text_miaoshu");
    Text_miaoshu->setString(StringUtils::format(Lang("100330").c_str(),7));
    UIUtils::textAdaptiveSize(Text_miaoshu, 915);
    
    
    auto Text_hour = getNode<TextBMFont*>("BitmapFontLabel_hour");
    auto Text_min = getNode<TextBMFont*>("BitmapFontLabel_min");
    long startTs = UIUtils::getDailyTS(); // + OneDaySec;
    DATA_M->setRankDailyTS(startTs);

    auto cb = [startTs, Text_hour,Text_min,this](float t){
        std::time_t t_now = std::time(0);  // t is an integer type
        auto diff = startTs - t_now;
        if(diff <= OneDaySec)
        {
            timeParent->setVisible(true);
            //diff = MAX(MIN(diff, 3*OneDaySec), 0);
            diff = MAX(diff, 0);
            int min = diff / 60;
            int hour = min / 60;
            min = min % 60;
            Text_hour->setString(StringUtils::format("%02d",hour));
            Text_min->setString(StringUtils::format("%02d",min));
        }
        else
        {
            timeParent->setVisible(false);
        }
    };
    cb(0);
    this->unschedule("update_ts");
    this->schedule(cb, 0.5f, "update_ts");
    auto cnt = RankManager::getInstance()->getRankList().size();//rankArr.IsNull()||rankArr.Size() == 0?1:rankArr.Size();
    if(cnt > 100) cnt = 100;
    auto scrollViewSize = _scrollView->getInnerContainerSize();
    //计算高度
    auto panel = getPanelView();
    auto height = panel->getContentSize().height;
    height = cnt * height;
    scrollViewSize.height = height;
    _scrollView->setInnerContainerSize(scrollViewSize);
    auto size = _scrollView->getContentSize();
    //isSwallowTouch
    _scrollView->setSwallowTouches(false);
    _loadingNum = 6;
    startIDX = 0;
    this->unschedule("create_tab");
    auto func = [this, size, cnt,height](float t){
        int i = 0;
        
        while(startIDX < cnt)
        {
            auto panel = getPanelView()->clone();
            auto panelSize = panel->getContentSize();
            
            
            auto node = RankItem::createBagNode(startIDX,this);
            if(_myRank == startIDX+1)
            {
                _myRankItem = node;
            }
            node->setCascadeOpacityEnabled(true);
            panel->addChild(node);
            node->setPosition(Vec2(panelSize.width/2,panelSize.height/2));
            // 优化帧率 不该显示时候不显示
            panel->schedule([panel,this, size](float){
//                            CCLOG("PP1 %f_%f", panel->getPositionX(), panel->getPositionY());
                auto worldPos = panel->convertToWorldSpaceAR(Vec2::ZERO);
                auto nodePos = _scrollView->convertToNodeSpace(worldPos);
//                            CCLOG("PP2 %f_%f", nodePos.x, nodePos.y);
                auto flag = nodePos.y < size.height && nodePos.y > -300;
                panel->setVisible(flag);
            }, 1.0f/30, "panel_schedule");
            
            panel->setAnchorPoint(Vec2(0,0));
            panel->setPosition(Vec2(0,height-panelSize.height-(startIDX * panelSize.height)));
            _scrollView->addChild(panel);

            startIDX++;
            i++;
            
            if(i >= _loadingNum)
            {
                _loadingNum = 1;
                return;
            }
        }
        SCENE_M->removeLoading();
        this->unschedule("create_tab");
    };
    schedule(func, 0, "create_tab");
    func(0);
}

void RankView::updateName()
{
    auto myName = DATA_M->getMyName() == ""?"ME":DATA_M->getMyName();
    getNode<Text*>("Text_myName")->setString(myName);
    if(_myRankItem)
    {
        _myRankItem->updateName();
    }
}


Layout* RankView::getPanelView()
{
    Layout* panelView = 0;
    panelView = getNode<Layout*>("Panel_view_bg");
    return panelView;
}

