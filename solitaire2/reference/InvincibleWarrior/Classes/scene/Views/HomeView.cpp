
#include "HomeView.h"
#include "GameViewHD.hpp"
#include "PlayerManager.h"
#include "MainLobby.h"
#include "MainLobby.h"
#include "CardSprite.h"
#include "SpriteManager.h"
#include "UIUtils.h"
//任务
#include "DailytaskView.h"
#include "TaskManager.h"
//星星宝箱
#include "StarBoxView.h"
//分享奖励
#include "ShareRewardView.h"
//领取金币
#include "FreeCoinLayer.h"
//翻牌奖励
#include "FanPaiRewardView.h"
//背包
#include "BagView.h"
//签到
#include "SevenDayView.h"
//翻牌
#include "FanPaiAD.h"
//轮盘
#include "RewardRouletteView.h"
#include "GrowupNode.h"
#include "TeachManager.h"

#include "EventObserver.h"
#include "CardSprite.h"
#include "AtlasManager.h"

void HomeView::initUI() {
    BaseLayer::initUI();
    
    // ani
    auto sprite_flopPoker = getNode("Node_sprite");
    auto card = UIUtils::createCSBNode("card/CardFace.csb");
    auto picType = DATA_M->getCardPicType(2);
    _sprite1 = card->getChildByName<Sprite*>("Sprite_face");
    _sprite2 = _sprite1->getChildByName<Sprite*>("Sprite_num");
    _sprite3 = _sprite1->getChildByName<Sprite*>("Sprite_color");
    _spriteBg = card->getChildByName<Sprite*>("Sprite_bg");
    auto num = 1;
    _sprite1->setSpriteFrame(AtlasManager::getInstance()->getSF(2, num, 0, picType));
    _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, num, 0, picType));
    _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, num, 0, picType));
    _sprite2->setColor(UIUtils::getCardColor(0));
    _spriteBg->setSpriteFrame(SPRITE_M->getCardBgSpriteFrame(DATA_M->getCardPicType(3)));
    sprite_flopPoker->addChild(card);
    card->setPosition(sprite_flopPoker->getContentSize()*0.5f);
    auto pos2 = _sprite2->getPosition();

    _sprite1->setVisible(true);
    _spriteBg->setVisible(false);
    getNode("FileNode_theme")->setVisible(false);
//    getNode("Image_5")->setVisible(false);
//    getNode("Image_5_0")->setVisible(false);
    //sprite_flopPoker->setSpriteFrame(SPRITE_M->getCardSpriteFrameByNumAndColor(1, CARD_BLACK));
    UIUtils::playInnerAction(getNode("FileNode_theme"), "loop", true)->setFrameEventCallFunc([sprite_flopPoker,this,num,pos2](Frame* frame) {
        auto eventName = static_cast<EventFrame*>(frame)->getEvent();
        if (eventName == "event_front") {
            _sprite1->setVisible(true);
            _spriteBg->setVisible(false);
            auto picType = DATA_M->getCardPicType(2);
            _sprite2->setSpriteFrame(AtlasManager::getInstance()->getSF(5, 1, 0, picType));
            _sprite3->setSpriteFrame(AtlasManager::getInstance()->getSF(6, 1, 0, picType));
            auto size2 = _sprite2->getContentSize();
            _sprite2->setPositionX(size2.width*0.5f);
        }
        else if (eventName == "event_back") {
            _sprite1->setVisible(false);
            _spriteBg->setVisible(true);
            _spriteBg->setSpriteFrame(SPRITE_M->getCardBgSpriteFrame(DATA_M->getCardPicType(3)));
        }
    });
//    playAni("In",false);
    
//    auto FileNode_LunPan = getNode("FileNode_LunPan");
//    UIUtils::playInnerAction(FileNode_LunPan, "Start0", true);
    
//    FileNode_StarBox = getNode("FileNode_StarBox");
//    FileNode_StarBox2 = getNode("FileNode_StarBox2");
//    UIUtils::playInnerAction(FileNode_StarBox,"Start0",true);
//    FileNode_MyBag = getNode("FileNode_MyBag");
//    Button_Sign_AD = getNode<Button*>("Button_Sign_AD");
//    Button_LunPan = getNode<Button*>("Button_LunPan");
//    Button_fanPai = getNode<Button*>("Button_fanPai");
    
    
    
//    schedule([this](float dt){
//        refushGift();
//    },10,"lobby_home_refushGift");
    
    
    //多语言
    updateDYY();
    //updataStarBox();
    //UIUtils::playInnerAction(getNode("FileNode_setting"), "loop", true);
    doLayout();
}

void HomeView::initData() {
    BaseLayer::initData();
    setName("HomeView");

    _hardSelectIDX = GETINTEGER("mainlybby_hard_select", 0);
    _modeSelectIDX = GETINTEGER("mainlybby_hard_mode", 0);
    
    EVENT_M->addListener("event_home_updateui", [this](ValueMap valueMap, void *obj){
        this->updateUI();
    },this);
//    addEvent("event_home_updateui", [this](EventCustom *){
//        this->updateUI();
//    });

}

void HomeView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    
    if(dynamic_cast<Button*>(btn))
    {
        SOUND_M->playEffectMusic(EffectButtonStart);
    }
    
    auto btnName = btn->getName();
    if (btnName == "Button_start") {
        if(getIsStart())
        {//防止持续点击进入
            //防止动画没播放结束跳转界面时没有刷新星星数目
            if (TEACH_M->isTeaching())
                UIUtils::FIRAnalyticsEventWithPrefix(string("lobbyStart_") + TEACH_M->getCurrentTeachKey(), "teach");
            else
                UIUtils::FIRAnalyticsEventWithPrefix("gameStartNormal_" + toString(_hardSelectIDX));
            TEACH_M->nextTeachStep(); // 新手
            
            setIsStart(false);
            
            auto type = _hardSelectIDX==0?DataManager::GameType::Huo:DataManager::GameType::Random;
            
            auto isThree = _modeSelectIDX == 1;
            bool is = getIsNewGame();
            DATA_M->setGameType(type);
            DATA_M->setIsThreeModel(isThree);
            _lobby->startGame(is);
        }
    }
    else if (btnName == "Button_hardRight") {
        _hardSelectIDX = MIN(_hardSelectIDX++, 1);
        SETINTEGER("mainlybby_hard_select", _hardSelectIDX);
        updateUI();
    }
    else if (btnName == "Button_hardLeft1") {
        _hardSelectIDX = MAX(_hardSelectIDX--, 0);
        SETINTEGER("mainlybby_hard_select", _hardSelectIDX);
        updateUI();
    }
    else if (btnName == "Button_modeRight") {
        _modeSelectIDX = MIN(1, _modeSelectIDX++);
        SETINTEGER("mainlybby_hard_mode", _modeSelectIDX);
        updateUI();
    }
    else if (btnName == "Button_modeLeft1") {
        _modeSelectIDX = MAX(0, _modeSelectIDX--);
        SETINTEGER("mainlybby_hard_mode", _modeSelectIDX);
        updateUI();
    }
}

//void HomeView::refushGift()
//{
//    if (DATA_M->getNextFreeCoinTime() <= 0&&DATA_M->getHaveVideo())
//    {
//        Button_Sign_AD->setVisible(true);
//    }
//    else
//    {
//        Button_Sign_AD->setVisible(false);
//    }
//
//    if(DATA_M->getNextFreeCoinTime3() <= 0&&DATA_M->getHaveVideo())
//    {
//        Button_LunPan->setVisible(true);
//    }
//    else
//    {
//        Button_LunPan->setVisible(false);
//    }
//
//    if(DATA_M->getNextFreeCoinTime4() <= 0&&DATA_M->getHaveVideo())
//    {
//        Button_fanPai->setVisible(true);
//    }
//    else
//    {
//        Button_fanPai->setVisible(false);
//    }
//}

HomeView::HomeView(MainLobby *lobby)
:BaseLayer("2020HomeView_Classic.csb"),
_lobby(lobby),
isStart(true)
{
}

HomeView::~HomeView() {

}

void HomeView::updateUI() {
    getNode<Button*>("Button_hardLeft1")->setEnabled(_hardSelectIDX != 0);
    getNode<Button*>("Button_hardRight")->setEnabled(_hardSelectIDX != 1);
    getNode<Button*>("Button_modeLeft1")->setEnabled(_modeSelectIDX == 1);
    getNode<Button*>("Button_modeRight")->setEnabled(_modeSelectIDX == 0);
    auto Text_hard = getNode<Text*>("Text_hard");
    auto Text_mode = getNode<Text*>("Text_mode");
    if (_hardSelectIDX == 0) {
        Text_hard->setString(Lang("100116"));
        
    }
    else if (_hardSelectIDX == 1){
        Text_hard->setString(Lang("100117"));
    }
    else if (_hardSelectIDX == 2){
        //getNode<Text*>("Text_hard")->setString(Lang("100188"));
    }
    if (_modeSelectIDX == 0) {
        Text_mode->setString(Lang("100167"));
    }
    else {
        Text_mode->setString(Lang("100168"));
    }
    UIUtils::textAdaptiveSize(Text_hard,450);
    UIUtils::textAdaptiveSize(Text_mode,450);
}

static bool HomeView_NoAni_Once = true;
void HomeView::onEnter() {
    BaseLayer::onEnter();
    updateUI();
    if (!HomeView_NoAni_Once) { // 刚进来么有动画
        playAni("In", false);
    }
    HomeView_NoAni_Once = false;
    UIUtils::FIRAnalyticsEventWithPrefix("HomeView");
}

void HomeView::onExit() {
    BaseLayer::onExit();
    playAni("Out", false);
    EVENT_M->removeListener("event_home_updateui",this);
}

void HomeView::setIsStart(bool is)
{
    isStart = is;
}
bool HomeView::getIsStart()
{
    return isStart;
}

void HomeView::updateDYY()
{
    // 多语言
    //getNode<Text*>("Text_currentLv")->setString(Lang("100200"));
    //getNode<Text*>("Text_setting")->setString(Lang("100071"));
    //getNode<Text*>("Text_hardTitle")->setString(Lang("100201"));
    //getNode<Text*>("Text_modeTitle")->setString(Lang("100202"));
    //getNode<Text*>("Text_themePreview")->setString(Lang("100203"));
    getNode<Text*>("Text_start")->setString(Lang("100150"));
    
    auto Text_hard = getNode<Text*>("Text_hard");
    auto Text_mode = getNode<Text*>("Text_mode");
    if (_hardSelectIDX == 0) {
        Text_hard->setString(Lang("100116"));
        
    }
    else if (_hardSelectIDX == 1){
        Text_hard->setString(Lang("100117"));
    }
    else if (_hardSelectIDX == 2){
        //getNode<Text*>("Text_hard")->setString(Lang("100188"));
    }
    if (_modeSelectIDX == 0) {
        Text_mode->setString(Lang("100167"));
    }
    else {
        Text_mode->setString(Lang("100168"));
    }
    UIUtils::textAdaptiveSize(Text_hard,450);
    UIUtils::textAdaptiveSize(Text_mode,450);
}

void HomeView::setHard(bool isHuo)
{
    if(isHuo)
    {
        _hardSelectIDX = 0;
    }
    else
    {
        _hardSelectIDX = 1;
    }
    SETINTEGER("mainlybby_hard_select", _hardSelectIDX);
    updateUI();
   
}
void HomeView::setMode(bool isOne)
{
    if(isOne)
    {
        _modeSelectIDX = 0;
    }
    else
    {
        _modeSelectIDX = 1;
    }
    updateUI();
}

bool HomeView::getIsNewGame()
{
    bool isGameModel = false;
    bool isThreeModel = false;
    auto type = _hardSelectIDX==0?DataManager::GameType::Huo:DataManager::GameType::Random;
    if(type == DATA_M->getGameType())
    {//模式相同
        isGameModel = false;
    }
    else
    {//模式不同 必定新开
        isGameModel = true;
    }
    auto isThree = _modeSelectIDX == 1;
    int i = -1;
    int j = -1;
    if(isThree)
    {
        i = 1;
    }
    else
    {
        i = 0;
    }
    if (DATA_M->getIsThreeModel())
    {
        j = 1;
    }
    else
    {
        j = 0;
    }
    if(i == j)
    {//翻牌次数相同
        isThreeModel = false;
    }
    else
    {//模式不同 必定新开
        isThreeModel = true;
    }
    return isThreeModel || isGameModel;
}
