//
// Created by  on 2020/3/20.
//

#include "TeachTalkView.h"
#include "TeachManager.h"
#include "EventObserver.h"
#include "MainLobby.h"
#include "GameViewHD.hpp"
#include "SpriteManager.h"
const float TalkSpd = 20;

//判断字符是否是中文
int is_zh_ch(char p){
    if(~(p >> 8) == 0)
    {
        return 1;
    }
    return -1;
}

void TeachTalkView::initUI() {
    BaseLayer::initUI();
    doLayout();
    _type = (*_teachConfig)["type"].GetString();
    _content = Lang((*_teachConfig)["txt"].GetString());//"呵呵呵像是表达自己的笑容，却给人以莫测高深的感觉。有\n时会让人不明白是喜，是悲，是怒，还是乐，而让人近乎崩溃。\n呵呵呵也有时表示没有话可说，或者对对方的话表示不置\n可否的时候使用呵呵表示自己在应和。";
    dumpString();
    auto text_content = getNode<Text*>("Text_content");
    text_content->setString("");
    unschedule("schedule_update_str");
    schedule([this, text_content](float t){
        _curIdx += t*TalkSpd;
        if (_curIdx >= (_dump.size())) {
            _curIdx = (_dump.size());
            unschedule("schedule_update_str");
            _isEnd = true;
        }
        string showStr;
        showStr = accumulate(_dump.begin(), _dump.begin()+(int)_curIdx, showStr);
        CCLOG("teach talk:%s idx:%d", showStr.c_str(), (int)_curIdx);
        text_content->setString(showStr);
    }, 0, "schedule_update_str");
    playAni("Start0", false, [this](){
        getNode<Widget*>("Panel_root")->setTouchEnabled(false);
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(TeachTalkView::onTouchBegan, this);
        listener->onTouchEnded = CC_CALLBACK_2(TeachTalkView::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    });
    UIUtils::playInnerAction(getNode("FileNode_3"), "KingLoop", true);
    
    
    auto button_auto = getNode("Button_auto");
    if ((*_teachConfig).HasMember("btnTxt")) {
        button_auto->setVisible(true);
        getNode<Text*>("Text_name")->setString(Lang((*_teachConfig)["btnTxt"].GetString()));
    }
    else
        button_auto->setVisible(false);
    auto spriteObj = SPRITE_M;
    if (_type == "poker") {
        _canMoveCard = nullptr;
        getNode("Panel_black")->setVisible(false);
        spriteObj->tipsLayer->setVisible(true);
        auto array = (*_teachConfig)["highlight"].GetArray();
        for (int i = 0; i < array.Size(); ++i) {
            auto item = array[i].GetString();
            vector<string> elems;
            UIUtils::split(item, '_', elems);
            CCASSERT(elems.size()>=2, "config error highlight!!");
            if (elems[0] == "a") {
                int idx = UIUtils::stoii(elems[1]);
                if (!spriteObj->aCardVector[idx].empty()) {
                    auto card = spriteObj->aCardVector[idx].back();
                    card->setTeachLZOrder(100);
                    _hilghtCard.push_back(card);
                }
                else {
//                    auto aSprite = spriteObj->aSprite[idx];
                }
            }
            else if (elems[0] == "k") {
                int idx = UIUtils::stoii(elems[1]);
                int idx1 = UIUtils::stoii(elems[2]);
                if (!spriteObj->kCardVector[idx].empty()) {
                    auto card = spriteObj->kCardVector[idx].at(idx1);
                    card->setTeachLZOrder(100);
//                    card->getShaderS()->setColor(Color3B::RED);
                    if (elems.back() == "t") {
                        _canMoveCard = card;
                    }
                    _hilghtCard.push_back(card);
                }
                else {
//                    auto aSprite = spriteObj->kSprite[idx];
//                    aSprite->setLocalZOrder(100);
//                    aSprite->setColor(Color3B::RED);
                }
            }
            else if (elems[0] == "w") {
                auto card = spriteObj->waitCardVector.back();
                card->setTeachLZOrder(100);
                _canMoveCard = card;
                _hilghtCard.push_back(card);
            }
            else if (elems[0] == "ws") {
                auto card = spriteObj->waitShowCardVector.back();
                card->setTeachLZOrder(100);
                _canMoveCard = card;
                _hilghtCard.push_back(card);
            }
        }
        if (_canMoveCard) { //添加手指头
            auto finger = UIUtils::createCSBNode("Animation/Node_finger.csb", "Start0", true);
            auto worldP = _canMoveCard->convertToWorldSpaceAR(Vec2::ZERO);
            auto localP = this->convertToNodeSpace(worldP);
            this->addChild(finger);
            finger->setPosition(localP+Vec2(0, POKER_SIZE.height/4));
        }
    }
   
}

void TeachTalkView::initData() {
    BaseLayer::initData();
    setName("TeachTalkView");
    
//    addEvent("msg_teach_next", [this](EventCustom *custom) {
//        if (custom->getUserData() == _canMoveCard) {
//            this->removeFromParent();
//            TEACH_M->nextTeachStep();
//        }
//    });
}

void TeachTalkView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();

    if (btnName == "Panel_root") {
        if (_isEnd) {
            if (_type == "talk") { // 对话结束就结束了
                TEACH_M->nextTeachStep();
                this->removeFromParent();
            }
        }
        else {
            _isEnd = true;
            getNode<Text*>("Text_content")->setString(_content);
            unschedule("schedule_update_str");
        }
    }
    else if (btnName == "Button_end") {
        this->removeFromParent();
        TEACH_M->endTeach("");
        auto lobby = SCENE_M->getLobby();
        if (lobby) {
            lobby->setVisible(true);
            lobby->resetHome();
        }
    }
    else if (btnName == "Button_auto") {
        if (_type == "autowin") {
            SCENE_M->getGameView()->dealButtonClick(pSender);
            SPRITE_M->tipsLayer->setVisible(false);
        }
        else {
            TEACH_M->nextTeachStep();
        }
        this->removeFromParent();
    }
}

TeachTalkView::TeachTalkView(std::shared_ptr<rapidjson::Document> teachConfig)
:BaseLayer("teach/TeachTalkView.csb")
,_teachConfig(teachConfig)
,_curIdx(0)
{
}

TeachTalkView::~TeachTalkView() {

}

void TeachTalkView::dumpString()
{
    size_t i=0;
    size_t len = _content.length();
    size_t chLen = string("中").length();
    while(i<len)
    {
        if (is_zh_ch(_content.at(i))==1)
        {
            _dump.push_back(_content.substr(i,chLen));
            i+=chLen;
        }else{
            _dump.push_back(_content.substr(i,1));
            i+=1;
        }
    }
}

bool TeachTalkView::onTouchBegan(Touch *t, Event *e) {
    if (_canMoveCard) {
        Point touchP = t->getLocation();//触摸点
        touchP = _canMoveCard->getParent()->convertToNodeSpace(touchP);
        Rect checkRect = _canMoveCard->getCheckBox();
        if (_canMoveCard->getPosId() == CARD_POS_K) {
            checkRect = _canMoveCard==SPRITE_M->kCardVector[_canMoveCard->getColNum()].back()?checkRect:_canMoveCard->getHeadBox();
        }
        if (checkRect.containsPoint(touchP) && (_canMoveCard->getIsOpen() || _canMoveCard->getPosId() == CARD_POS_WAIT)) // 穿透
        {
            return false;
        }
    }

    return true;
}

void TeachTalkView::onTouchEnded(Touch *t, Event *e) {
    BaseLayer::onTouchEnded(t, e);
    dealButtonClick(getNode<Widget*>("Panel_root"));
}

void TeachTalkView::onEnter() {
    BaseLayer::onEnter();
    EventObserver::getInstance()->addListener("msg_teach_next", [this](ValueMap valueMap, void *obj){
        if (_canMoveCard && valueMap["name"].asString() == _canMoveCard->getName()) {
            this->removeFromParent();
            TEACH_M->nextTeachStep();
        }
    }, this);
}

void TeachTalkView::onExit() {
    BaseLayer::onExit();
    EventObserver::getInstance()->removeListener("msg_teach_next", this);
    for (auto &card:_hilghtCard) {
        card->setTeachLZOrder(0);
    }
}
