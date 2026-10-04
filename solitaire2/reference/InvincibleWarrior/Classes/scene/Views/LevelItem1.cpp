
#include "LevelItem1.h"
#include "LevelViewHD.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "LevelManager.h"
#include "EventObserver.h"
void LevelItem1::initUI() {
//    BaseLayer::initUI();
    initUIByRemove(true);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    getNode<Text*>("Text_title")->setString(Lang((*_value)["name"].GetString()));
    getNode<TextBMFont*>("Text_level")->setString(StringUtils::toString((*_value)["subShow"].GetInt()));
//    getNode<Sprite*>("Level_icon0")->setSpriteFrame((*_value)["icon"].GetString());
    getNode<Sprite*>("Level_icon1")->setSpriteFrame((*_value)["icon"].GetString());
}

void LevelItem1::initData() {
    BaseLayer::initData();
    setName("LevelItem1");
}

void LevelItem1::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();

    if (btnName == "Button_go") {
        _parentView->startLevel(_idx);
    }
}

LevelItem1::LevelItem1(LevelViewHD *parentView, std::shared_ptr<rapidjson::Document> value, int idx)
:BaseLayer("level_icon1.csb")
,_parentView(parentView)
,_value(value)
,_idx(idx)
{
}

LevelItem1::~LevelItem1() {

}

void LevelItem1::onEnter() {
    Widget::onEnter();
    EVENT_M->addListener("msg_levelite1_update", [this](ValueMap valueMap, void *obj){
        this->updateUI();
    },this);
    
    updateUI();
}

void LevelItem1::onExit() {
    Widget::onExit();
    EVENT_M->removeListener("msg_levelite1_update",this);
    //getEventDispatcher()->removeCustomEventListeners("msg_levelite1_update");
}

void LevelItem1::updateUI() {
    auto levelManager = LevelManager::getInstance();
    bool completed = levelManager->isLevelComplete(_value);
    getNode("Level_complete")->setVisible(completed);
    auto isUnlock = levelManager->isLevelUnLock(_value);
    getNode<Sprite*>("Level_icon0")->setVisible(!isUnlock);
    getNode<Button*>("Button_go")->setEnabled(isUnlock);
    
    auto star = levelManager->getFullLevelStar(_value);
    getNode("Node_star")->setVisible(star>0);
    for (int i = 1; i <= 3; ++i) {
        getNode(StringUtils::format("Level_starbg%d", i))->setVisible(i<=star);
    }
    
    auto select = star==0 && isUnlock;
    if (select&&0) {
        auto node_elect = getNode("Node_select");
        node_elect->setVisible(select);
        playAni("start", true);
    }
    else {
        getNode("Node_select")->setVisible(false);
    }
}
