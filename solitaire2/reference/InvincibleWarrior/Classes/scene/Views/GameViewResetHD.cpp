
#include "GameViewResetHD.h"
#include "SpriteManager.h"
#include "DataManager.h"
#include "GameViewHD.hpp"
#include "LevelViewHD.h"
#include "GameKitHelper.h"
#include "LevelManager.h"
#include "SettingViewHD.h"
#include "ScoreManager.h"
#include "CountLayer.h"
#include "DailyView.h"

void GameViewResetHD::initUI() {
    BaseLayer::initUI();
    doLayout();

    _actionManager->play("Start", false);

    auto isThreeMode = DATA_M->getIsThreeModel();
    auto gameType = isThreeMode?2:1;
    getNode<TextBMFont*>("Text_bestScore1")->setString(StringUtils::toString(ScoreManager::getInstance()->getScore(gameType, ScoreManager::Type::LIVEBESTSCORE)));
    getNode<TextBMFont*>("Text_bestScore2")->setString(StringUtils::toString(ScoreManager::getInstance()->getScore(gameType, ScoreManager::Type::RANDBESTSCORE)));

    Node *pGradeClassicNode = getNode("FileNode_GradeClassic");
    pGradeClassicNode->setVisible(ScoreManager::getInstance()->isNewRecordAndMinus(gameType, ScoreManager::Type::LIVEBESTSCORE));
    Node *pGradeHardNode = getNode("FileNode_GradeHard");
    pGradeHardNode->setVisible(ScoreManager::getInstance()->isNewRecordAndMinus(gameType, ScoreManager::Type::RANDBESTSCORE));
//    UIUtils::playInnerAction(pGradeClassicNode, "Loop", true);
//    UIUtils::playInnerAction(pGradeHardNode, "Loop", true);

    getNode<TextBMFont*>("Text_currentLevelStar")->setString(LevelManager::getInstance()->getCurrentLevelStar());
    getNode("Sprite_tips")->setVisible(DATA_M->hasRedPoint(false));
    
    // 多语言
    getNode<Text*>("Text_cardMode")->setString(Lang(isThreeMode?"100020":"100007"));
    getNode<Text*>("Text_title")->setString(Lang("100115"));
    getNode<Text*>("text_huo_new")->setString(Lang("100116"));
    getNode<Text*>("text_random_new")->setString(Lang("100117"));
    getNode<Text*>("text_levelchallenge")->setString(Lang("100118"));
    getNode<Text*>("Text_share")->setString(Lang("100119"));
    getNode<Text*>("Text_statistics")->setString(Lang("100120"));
    getNode<Text*>("Text_rank")->setString(Lang("100121"));
    getNode<Text*>("Text_setting")->setString(Lang("100122"));
    
    getNode<Text*>("text_highscore1")->setString(Lang("100016"));
    getNode<Text*>("text_highscore2")->setString(Lang("100016"));
    getNode<Text*>("text_totalstarnum")->setString(Lang("100132"));

#if HasDaily
    // 每日
    getNode<Text*>("text_dailyChallenge")->setString(Lang("100155"));
    getNode<Text*>("text_totalcrownnum")->setString(Lang("100160"));
    
    auto currentDate = DailyManager::getInstance()->getCurrentDate();
    auto today = DailyManager::getInstance()->today();
    auto current = currentDate==NoneDate?today:currentDate;
    auto monthCompleteCNT = DailyManager::getInstance()->getMonthCompleteCNT(current);
    int days = DailyManager::getInstance()->getDays(current.Year(), current.Month());
    getNode<TextBMFont*>("Text_currentDailyCrown1")->setString(toString(monthCompleteCNT));
    getNode<TextBMFont*>("Text_currentDailyCrown2")->setString(toString(days));
    getNode("Sprite_dailyTips")->setVisible(DATA_M->hasRedPoint(false, DataManager::GameType::Daily));
#endif
}

void GameViewResetHD::initData() {
    BaseLayer::initData();
    setName("GameViewResetHD");
}

void GameViewResetHD::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Button*>(pSender);
    if (btn == nullptr) {
        return;
    }
    
    SOUND_M->playBtnClickAudio();
    ValueMap valueMap;
    auto btnName = btn->getName();
    if ("btn_reset_replay" == btnName)
    {//分享
//        _gameView->restartGame(true);
//        UIUtils::FIRAnalyticsEvent("event_newGame_replay", valueMap);
        UIUtils::shareApp();
    }
    else if ("btn_random_new" == btnName)
    {
        DATA_M->setIsWeiJiaSi(false);
        _gameView->restartGame(false, DataManager::GameType::Random);
        UIUtils::FIRAnalyticsEvent("event_newGame_random", valueMap);
    }
    else if ("btn_huo_new" == btnName)
    {
//        if (DATA_M->getNetReachable() == 0) {
////            SCENE_M->showTips(UIUtils::getStringByName("100078"));
//            SCENE_M->showDialog(Dialog::Type::Normal, [](){
//                UIUtils::showSetting();
//            }, nullptr)->setText(Lang("100166"), Lang("100169"), Lang("100170"), "");
//        }
//        else {
//            DATA_M->setIsThreeModel(false);     // 活局只支持单张牌
            DATA_M->setIsWeiJiaSi(false);
            _gameView->restartGame(false, DataManager::GameType::Huo);
//        }
        UIUtils::FIRAnalyticsEvent("event_newGame_huo", valueMap);
    }
    else if ("btn_new" == btnName) {
        DATA_M->setIsWeiJiaSi(false);
        _gameView->restartGame(false, DATA_M->getNetReachable() == 0?DataManager::GameType::Random:DataManager::GameType::None);
        UIUtils::FIRAnalyticsEvent("event_newGame", valueMap);
    }
    else if ("btn_level" == btnName) {
        SCENE_M->addDialog(LevelViewHD::createLayerN());
        this->removeFromParent();
    }
    else if ("Button_setting" == btnName) {
        SCENE_M->addDialog(SettingViewHD::createLayerN(SettingViewHD::ViewType::Daily));
        this->removeFromParent();
    }
    else if ("Button_rank" == btnName) {
        GameKitHelper::showLeaderBoard();
        //关闭窗口开始累计计时
        SCENE_M->getGameView()->setIsOpenTipsTime(true);
    }
    else if ("Button_statistic" == btnName) {
        //显示统计界面
        SCENE_M->addDialog(CountLayer::createLayer());
        this->removeFromParent();
    }
    else if ("btn_daily" == btnName) {
        _gameView->gamePause(true);
        SCENE_M->addDialog(DailyView::createLayerN(), true);
        UIUtils::FIRAnalyticsEvent("event_newGame_daily", valueMap);
    }
    
    if (btnName != "Panel_out"&&"btn_reset_replay" != btnName&&"Button_statistic" != btnName&&"btn_level" != btnName&&"Button_setting" != btnName) {
        //关闭窗口开始累计计时
        SCENE_M->getGameView()->setIsOpenTipsTime(true);
        this->removeFromParent();
    }
}

GameViewResetHD::GameViewResetHD(GameViewHD *gameView)
:BaseLayer("UI_reset.csb")
,_gameView(gameView)
{
}

GameViewResetHD::~GameViewResetHD() {

}
