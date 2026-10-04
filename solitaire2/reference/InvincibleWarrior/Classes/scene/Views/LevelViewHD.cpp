
#include "LevelViewHD.h"
#include "LevelManager.h"
#include "LevelItem0.h"
#include "LevelItem1.h"
#include "SceneManager.h"
#include "GameViewHD.hpp"
#include "MainLobby.h"
#include "EventObserver.h"
void LevelViewHD::initUI() {
    BaseLayer::initUI();
    doLayout();
    
    getNode("btn_level_close")->setVisible(!_isLobby);

    _listview_bg0 = getNode<ListView*>("ListView_bg0");
    _listview_bg1 = getNode<ListView*>("ListView_bg1");
    _listview_bg0->setScrollBarEnabled(false);
    _listview_bg1->setScrollBarEnabled(false);
    
    
    //BitmapFontLabel_2
    //多语言
    updateDYY();
    
    initLevel0();
    showLevel(0);
    updateUI();
    playAni("Start0");
}

void LevelViewHD::initData() {
    BaseLayer::initData();
    setName("LevelViewHD");
    
    DATA_M->hasRedPoint(true); // z重置时间
    LevelManager::getInstance();
}

void LevelViewHD::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();

    if ("btn_level_close" == btnName||"panel_shop" == btnName) {
        getNode("btn_level_close")->setVisible(!_currentTab == 1);
        if (_currentTab == 1) {
            showLevel(0);
        } else {
            //关闭窗口开始累计计时
//            SCENE_M->getGameView()->setIsOpenTipsTime(true);
            SCENE_M->removeLayer(this);
        }
    }
}

LevelViewHD::LevelViewHD(bool isLobby)
:BaseLayer("Level0.csb")
,_isLobby(isLobby)
{
}

LevelViewHD::~LevelViewHD() {

}

void LevelViewHD::initLevel0() {
    auto listView = _listview_bg0;
    auto totalCNT = LevelManager::getInstance()->getTotalCNT();
    for (int i=0;i<totalCNT;i++) {
        listView->pushBackCustomItem(LevelItem0::createLayerN(this, i));
    }
    auto group = LevelManager::getInstance()->getCurrentGroup();
    listView->jumpToPercentVertical(group*100.f/totalCNT);
}

const int SPLIT = 4;
void LevelViewHD::initLevel1(int level) {
    _currentLevel = level;
    auto listView = _listview_bg1;
    auto levelData = LevelManager::getInstance()->getLevelData(level);
    const auto &array = (*levelData)["data"].GetArray();
    int totalCNT = array.Size();
    int totalSplitCNT = ceil(totalCNT*1./SPLIT);
    for (int i = 0; i < totalSplitCNT; i++)
    {
        auto panel = getNode<Layout*>("Panel_view")->clone();
        auto panelSize = panel->getContentSize();
        for (int j=0;j<SPLIT;j++)
        {
            auto idx = i*SPLIT+j;
            if (idx>=totalCNT) break;

            auto node = LevelItem1::createLayerN(this, LevelManager::getInstance()->clone(array[idx]), idx);
            auto splitSize = panelSize/SPLIT;
            node->setPosition(Vec2(j*splitSize.width+splitSize.width/2,panelSize.height/2));
            panel->addChild(node);
        }
        listView->pushBackCustomItem(panel);
    }
    
    auto group = LevelManager::getInstance()->getCurrentGroup();
    if (group == _currentLevel) {
        auto sub = LevelManager::getInstance()->getCurrentSub();
        listView->jumpToPercentVertical(floor(sub/4.0f)/totalSplitCNT*100.f);
    }
    else {
        listView->jumpToTop(); 
    }
}

void LevelViewHD::showLevel(int tab, int level) {
    if (_currentTab!=tab) {
        _currentTab = tab;
        getNode("btn_level_close")->setVisible(_currentTab == 1);
        _listview_bg0->setVisible(false);
        _listview_bg1->setVisible(false);
//        listView->jumpToTop();
        if (tab == 0) {
            _listview_bg0->setVisible(true);
        } else {
            _listview_bg1->setVisible(true);
            _listview_bg1->removeAllItems();
            initLevel1(level);
        }
    }
}

void LevelViewHD::startLevel(int sub) {
    if(getIsStart())
    {//防止持续点击进入
        setIsStart(false);
        auto gameView = SCENE_M->getGameView();
        SCENE_M->getRewardNode()->setVisible(false);
        //恢复音效
        //SOUND_M->resumeDTEffect();
        gameView->playMusic();
        gameView->playEffect();
        auto lobby = SCENE_M->getLobby();
        if(lobby)
        {
            lobby->setVisible(false);
            gameView->setVisible(true);
        }
        
        if (gameView) {
            _currentSub = sub;
            auto value = LevelManager::getInstance()->getLevelData(_currentLevel, sub);
            gameView->startLevelRank(value);
//            gameView->menuPlayAni("menuIdel", false);
//            this->setVisible(false);
//            SCENE_M->removeLayerByName(getName(), this);
            SCENE_M->removeLayer(this);
        }
    }
}

void LevelViewHD::complete(bool isWin, std::shared_ptr<rapidjson::Document> levelData) {
    this->setVisible(true);
    updateUI();
    if (isWin) {
//        LevelManager::getInstance()->setLevelComplete(_currentLevel, _currentSub);
        if (levelData != nullptr) {
            showTabWithLevel(_currentTab, (*levelData)["group"].GetInt()-1);
        }
    }
}

void LevelViewHD::updateUI() {
    getNode<Text*>("Text_totalStar")->setString(StringUtils::toString(LevelManager::getInstance()->getTotalStar()));
    EVENT_M->sendEvent("msg_levelite0_update");
    EVENT_M->sendEvent("msg_levelite1_update");
    auto star = LevelManager::getInstance()->getTotalStar();
    getNode<TextBMFont*>("BitmapFontLabel_2")->setString(StringUtils::toString(star));
    //getEventDispatcher()->dispatchCustomEvent("msg_levelite0_update");
    //getEventDispatcher()->dispatchCustomEvent("msg_levelite1_update");
}

void LevelViewHD::showTabWithLevel(int tab, int level)
{
    _currentTab = -1;        // 刷新 子页面
    showLevel(tab, level);
}


void LevelViewHD::setIsStart(bool is)
{
    isStart = is;
}
bool LevelViewHD::getIsStart()
{
    return isStart;
}

void LevelViewHD::resetView()
{
    isStart = true;
}

void LevelViewHD::updateDYY()
{
    auto text_title = getNode<Text*>("text_title");
    text_title->setString(Lang("100126"));
    UIUtils::textAdaptiveSize(text_title,460);
    getNode<Text*>("text_titlesub")->setString(Lang("100127"));
}
