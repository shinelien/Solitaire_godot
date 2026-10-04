/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameViewHD.hpp"
#include "TeachManager.h"
#include "MainLobby.h"
#include "BackstagePause.h"
#include "LoadingView.h"

 #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#include "AppUtils.h"
#include "CrashReport.h"
#endif
#include "MainScene.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1080, 1920);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    SETINTEGER("game_load_cnt", GETINTEGER("game_load_cnt", 0)+1);
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("NewSpaceCatSolitaire", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("NewSpaceCatSolitaire");
#endif
        director->setOpenGLView(glview);
    }

#if (COCOS2D_DEBUG>0)
    // turn on display FPS
    director->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
//    auto frameSize = glview->getFrameSize();
//    // if the frame's height is larger than the height of medium size.
//    if (frameSize.height > mediumResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
//    }
//    // if the frame's height is larger than the height of small size.
//    else if (frameSize.height > smallResolutionSize.height)
//    {
//        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
//    }
//    // if the frame's height is smaller than the height of medium size.
//    else
//    {
//        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
//    }

    register_all_packages();
    std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    DataManager::GAME_START_TS = DataManager::getContentSec();

    
    vector<string > searchPaths;
    searchPaths.push_back(FileUtils::getInstance()->getWritablePath());
    searchPaths.push_back(FileUtils::getInstance()->getWritablePath() + "download");
    searchPaths.push_back("music");
    searchPaths.push_back("img");
    searchPaths.push_back("effect");
    searchPaths.push_back("data");
    searchPaths.push_back("ui");
    searchPaths.push_back("game");
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
//    for (int i = 0; i < CARD_FACE_NUM;i++)
//    {
//        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(StringUtils::format("game/car_%d.plist",i));
//    }
    
    //    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/HDcard/card_0.plist");
    //    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/vipbg/vipbg0.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/cardBg.plist");
    //    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/HDcard/cardbg.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/Time/time_0.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui1.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/levelcard.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("challenge.plist");
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("jiangbei.plist");
    //    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("cardBg.plist");
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("skin_invi_deco.plist");
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("skin.plist");

#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    DATA_M->initAds();
#if (COCOS2D_DEBUG==0)
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("5b704947f29d981426000530", "");
#endif
#endif
    
    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();           //HelloWorld::createScene();
    
    scene->getEventDispatcher()->addCustomEventListener("custom_audio_pause", [](EventCustom *){
#if USE_AUDIO_ENGINE
        AudioEngine::pauseAll();
#endif
    });
    scene->getEventDispatcher()->addCustomEventListener("custom_audio_resume", [](EventCustom *){
#if USE_AUDIO_ENGINE
        AudioEngine::resumeAll();
#endif
    });
    // run
    director->runWithScene(scene);

    std::chrono::milliseconds ms1 = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    );
    float useTS = (ms1.count() - ms.count())/1000.f;
    log("startTS use sec:%.2f", useTS);
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    UIUtils::appStartEnd();
#endif
    return true;
}

#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    const int ADSCDTIME = 110;//1分50s//60*3;
    static time_t lastShowTime = 0;
#endif

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    lastShowTime =  std::time(0);
#endif
    
    auto game = SCENE_M->getGameView();
    if(game)
    {
        game->setTipsTime(0);
    }
    auto tm = DATA_M->getContentTime();
    if(tm->tm_hour < 6)
    {//0-6点不触发推送
        
    }
    else
    {//7点开始触发推送
        //UIUtils::registNotify(2*60, "2min", StringUtils::format("notification_back%d",random(1, 2)), true);
    }
    //记录切后台时间
    DATA_M->setDayOfflineTime();
    auto load_cnt = GETINTEGER("game_load_cnt", 0);
    // v1 第一次开始时间
    UIUtils::FIRFirestoreAddOP("EnterBackground", load_cnt <= 1?toString(DataManager::getContentSec() - DataManager::GAME_START_TS):"");
    UIUtils::FIRAnalyticsEventWithPrefix("EnterBackground");
}

static bool FirstOpen = true;
// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
    //UIUtils::unregistNotify("2min");
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("EnterForeground")}
    });
    if (FirstOpen) {
        FirstOpen = false;
        UIUtils::FIRAnalyticsEventWithPrefix("FirstOpen");
    }
    UIUtils::FIRAnalyticsEventWithPrefix("EnterForeground");
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    /*Director::getInstance()->getScheduler()->performFunctionInCocosThread( [=]() {
        auto timeNow = std::time(0);

        bool isPlay = false;
        //是否是第一次切后台 第一次直接放插屏
        isPlay = DATA_M->getIsInitialHouTai();
        //是否允许播放插屏
//        if (timeNow - lastShowTime >= ADSCDTIME || isPlay) {
//            //dispatch_async(dispatch_get_main_queue(), ^{
//            if (DATA_M->showNativeAds(2, "Fore")) {
//                lastShowTime = timeNow;
//                DATA_M->setIsInitialHouTai(false);
//                DATA_M->setInterstitialTime(timeNow);
//            }
//            //});
//        }
        auto loading = SCENE_M->getLoadingView();
        auto gameView = SCENE_M->getGameView();
        if (!loading && gameView) {//启动屏关闭后&&游戏场景已经创建
            //暂停弹窗
            auto gamePause = SCENE_M->getBackstagePause();

            auto isOver = gameView->getGameOver();
            auto isAuto = gameView->getIsAuto();
            auto isPause = gameView->getGamePause();
            auto lobby = SCENE_M->getLobby();
            auto isWinLayerShow = gameView->winLayerIsShow();
            bool isLobby;
            if (!lobby) {//不存在。 为true
                isLobby = true;
            } else if (!lobby->isVisible()) {//存在 但是没有显示 为true
                isLobby = true;
            } else {
                isLobby = false;
            }

            if (!TEACH_M->isTeaching() && isLobby && ((!isOver && !isAuto) ||
                                                      isWinLayerShow)) {// 教学过程中 不需要暂停&&大厅中不暂停&&游戏结束了不暂停||结算窗口显示时可以暂停
                if (!gamePause) {//在进行游戏中 并且 暂停窗口不存在
                    SCENE_M->addDialog(
                            BackstagePause::createLayerN(SCENE_M->getGameView(), isPlay));
                } else if (gamePause) {
                    gamePause->setIsPlay(isPlay);
                }
            }
        }
    });*/
    
#endif
}
