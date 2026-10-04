
#include "LevelItem0.h"
#include "LevelViewHD.h"
#include "LevelManager.h"
#include "EventObserver.h"
#include <unordered_map>

void LevelItem0::initUI() {
    initUIByRemove(true);
    setCascadeOpacityEnabled(true);
    getNode<Text*>("Text_needStar")->setString(toString((*_value)["unlock"].GetInt()));
    getNode<Text*>("Text_mode")->setString(Lang((*_value)["hard"].GetString()));
    getNode<Button*>("Button_go")->loadTextures((*_value)["icon"].GetString(), (*_value)["icon"].GetString(), "", Widget::TextureResType::PLIST);
    setLock(_idx>=6);
    getNode<Text*>("Text_lockTitle")->setString(Lang("100133"));
}

void LevelItem0::initData() {
    BaseLayer::initData();
    setName("LevelItem1");

    _value = LevelManager::getInstance()->getLevelData(_idx);
}

void LevelItem0::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();

    if (btnName == "Button_go") {
        if (!_isLock)
            _parentView->showLevel((int)LevelViewHD::Tab::Level1, _idx);
    }
}

LevelItem0::LevelItem0(LevelViewHD *parentView, int idx)
:BaseLayer("level_icon0.csb")
,_idx(idx)
,_parentView(parentView)
{
}

LevelItem0::~LevelItem0() {

}

void LevelItem0::setLock(bool lock) {
    _isLock = lock;
    getNode("Node_unlock")->setVisible(!lock);
    getNode("Node_lock")->setVisible(lock);
}

void LevelItem0::updateUI() {
//    setLock(!LevelManager::getInstance()->isLevelComplete(_idx));
    getNode<TextBMFont*>("Text_level")->setString(StringUtils::toString(_idx+1));
    auto levelStar = LevelManager::getInstance()->getLevelStar(_idx);
    getNode<Text*>("Text_winStar")->setString(StringUtils::format("%d/%d", levelStar, (*_value)["total"].GetInt()));
}

void LevelItem0::onEnter() {
    Widget::onEnter();
    EVENT_M->addListener("msg_levelite0_update", [this](ValueMap valueMap, void *obj){
        this->updateUI();
    },this);
//    getEventDispatcher()->addCustomEventListener("msg_levelite0_update", [this](EventCustom* eventCustom){
//
//    });
    updateUI();
}

void LevelItem0::onExit() {
    Widget::onExit();
    EVENT_M->removeListener("msg_levelite0_update",this);
    //getEventDispatcher()->removeCustomEventListeners("msg_levelite0_update");
}
