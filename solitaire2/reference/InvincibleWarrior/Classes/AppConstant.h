#ifndef _APP_CONSTANT_H_
#define _APP_CONSTANT_H_

#include "cocos2d.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#endif

//stand c++ library
#include <vector>
#include <string>
// Android 才有每日🏆 iOS加入每日
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define HasDaily 1
#else
#define HasDaily 1
#endif

#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
#define TestAutoPlay 0
#else
#define TestAutoPlay 0
#endif

// 订阅
static const std::string NoAdKey = "1249968208";
// 洗牌 func
static size_t ShuffleFunc(int i) { return std::rand()%i; }
//扑克阴影 颜色
static const Vec3 WaitPokerOffset[10]{Vec3(0, 0, 0), Vec3(0.5, 3, 0), Vec3(1, 6, 0), Vec3(2, 9, 0), Vec3(3, 12, 0), Vec3(4, 15, 0), Vec3(5, 18, 0), Vec3(6, 21, 0)
	, Vec3(7, 24, 0), Vec3(8, 27, 0),
};
static const Color3B WaitPokerColor[]{
	Color3B(100, 100, 100), Color3B(128, 128, 128), Color3B(140,140,140), Color3B(153,153,153), Color3B(166,166,166), Color3B(178,178,178),Color3B(191,191,191), Color3B(204,204,204), Color3B(255,255,255)
//    Color3B(255,255,255), Color3B(204,204,204), Color3B(191,191,191),Color3B(178,178,178),Color3B(166,166,166), Color3B(153,153,153), Color3B(140,140,140), Color3B(128, 128, 128),
};
//鱼未解锁颜色
static const Color3B FishUnlockColor = Color3B(30,30,30);
// iap
static const std::string HOT_KEY = "hot_";
// id, {原始价格, 数量, 增加%, 热销价格, 热销数量}
static const std::unordered_map<std::string, std::tuple<float, int, float, float, int>> ProductPrice{
//	{"gold_0", {4.99, 0, 0, 0, 0}},
	{"gold_1", {0.99, 240, 0, 0, 0}},
	{"gold_2", {2.99, 720, 0.5, 0, 0}},
	{"gold_3", {4.99, 1320, 0.5, 3.99, 1440}},
	{"gold_4", {9.99, 2880, 0, 0, 0}},
	{"gold_5", {19.99, 6240, 0, 0, 0}},
	{"gold_6", {39.99, 13440, 0, 0, 0}},
	{"gold_7", {79.99, 28800, 0, 0, 0}},
};
static const std::unordered_map<std::string, std::tuple<float, int, float, float, int>> SubProductPrice{
//    {"gold_0", {4.99, 0, 0, 0, 0}},
    {"sub_noads_week", {1.99, 240, 0, 0, 0}},
    {"sub_noads_month", {5.99, 720, 0.5, 0, 0}},
    {"sub_noads_halfyear", {17.99, 1320, 0.5, 3.99, 1440}},
};
// 卡牌大小缩放
const float CardBoxScale = 1.5;
//全局变量，控制计费信息
static const int MONEY_DIALOG_OPACITY_FLAG = 1;//如果值为0，代表计费界面使用模糊计费界面，如果为1代码使用清晰计费界面
static const int MONEY_DIALOG_EVENT_FLAG = 1;//如果值为0，代表如果用户点了计费弹窗非确认按钮和取消按钮，则相当于点确定，如果为1，则无效.
static const int MONEY_DIALOG_OPACITY = 200;//清晰度
static const int MONEY_DIALOG_IS_IOS = 0 ;//是否是ios平台

static const int FASH_TANK_NUM = 4;
static const std::vector<int> FASH_TANK_UNLOCK{
    0,18,39,60,
};
static const int FISH_NUM = 25;
static const float NPC_NUM = 5.6f;
static const int GOLD_NUM = 10;
static const int FISH_MAX_NUM = 25;
static const int GAME_BG_NUM = 14 + 12;       // 背景总数量 + 动态背景
static const int CARD_FACE_NUM = 6;
static const int CARD_BG_NUM = 35;
// 青龙
static const int QINGLONG_TYPE = 100;

static const auto FREE_COIN_REWARD = 25;
static const auto FREE_VIDEO_COIN_REWARD = 25;         //  免费视频获取金币

static const auto WINLAYER_COIN = 10;//结算金币奖励
static const auto WINLAYER_DIAMOND = 15;//结算钻石奖励

static const auto WINLAYER_COIN2 = 2;//结算金币奖励
static const auto WINLAYER_DIAMOND2 = 1;//结算钻石奖励

//魔法棒购买金额
static const int MAGIC_PRICE = 70;

static const bool IsIPX = Director::getInstance()->getSafeAreaRect().origin.y > 0;
// 提示动画
static const auto TIPS_ACTION_MOVE1 = .4;
static const auto TIPS_ACTION_MOVE2 = .25;
static const auto TIPS_ACTION_DELAY1 = .4;
static const auto TIPS_ACTION_DELAY2 = .25;
static const auto TIPS_ACTION_TOTALTIME = TIPS_ACTION_MOVE1+TIPS_ACTION_MOVE2+TIPS_ACTION_DELAY1+TIPS_ACTION_DELAY2+0.1f;
static const auto TIPS_ACTION_FADEOUT = 0.1;
// 牌大小
static const auto POKER_SIZE = cocos2d::Size(148.f, 220.f);
// 牌移动
static const auto POKER_ACTION_MOVE = 0.15f;
// 动态背景数量
const auto LiveGameBGCNT = 1;
// 最高层级
const static int MaxTopOrder = 200;
// 牌的间距
const static auto OffsetNoOpen = 30;
const static auto OffsetOpen = 66;
const static auto OffsetWait = 57;
// 强制点击CD
const static auto TOUCH_DELAY_CD = 0.07f;
const static auto TOP_TOUCH_DELAY_CD = 0.06f;
// 甩尾动画间隔
const static auto DRIFT_DELAY_TIME = 0.03f;
static const int NBSCORE = 700000;
static const int NBEXP = 210000;
// 任务版时间
const static float LEVEL_SHOW_TIME = 1.0f;
// 统计版数量
const static int CarDataCNT = 15;

// 加时
const static int LevelAddTime = 20;
// 加步数
const static int LevelAddMove = 25;
// 翻牌时间
const static float OpenCardTime = 0.09f;
// 翻牌重置间隔
const static float WaitCardRestTime = 0.012f;
// 三张牌翻牌间隔
const static float ThreeFlopSpaceTime = 0.03f;
// max rank
const static int MAX_RANK = 301;

// 等待卡牌总数
const static int TotalWatiCardNum = 24;
// 自动提示时间
const static float AutoTipsWaitTime = 99999;

const static std::string AutoFinishKey = "AutoFinishKey_XXX";

//------ 音效 ----------
//static char * EFFECT_BTN_CLICK    = EffectMovePoker;    //按钮点击音效
static const int LobbyMusicTotalCNT = 20;
//------道具ID----------
static const int ID_ZS_500=1;
//------发牌动画 下方牌区
const static float fanPaiJianGe = 0.11;//发完牌时 翻牌间隔
const static float faPaiDelayTime = 0.03;//牌与牌之间的延时时间（递增）
const static float faPaiJiaSu = 0.2;//第二排与第四排加速  越大 速度越快
//-------发牌动画  发牌区
const static float MVDT = 0.5f;//第一张牌移动到指定位置的时间
//延时递增数值
const static float DT_0 = 0.04;
//初始角度
const static float ANGLE = 60;

//关卡模式 限时关卡提示次数limitTimeNum
const static int LIMITTIMENUM = 3;

//金币节点飞出速度
const static float FLYSPEED = 1.5;
//星星飞出速度
const static float STARFLYSPEED = 1.0f;

//n局前游戏内不出现广告
const static int GAMENOADSCNT = 3;


const static Vec2 DEFAULTPOS = Vec2(99999,99999);
//挑战局数
const static int challengeMax = 30;

//新鱼排序
const static std::vector<int> newShopIdx{
    0,1,2,3,21,4,5,6,8,19,7,22,9,11,14,17,16,13,18,12,10,15,23,20,24,
};
const static std::vector<int> newShopTipsIdx{
    0,1,2,3,5,6,7,10,8,12,20,13,19,17,14,21,16,15,18,9,23,4,11,22,24
};
//等级上限
const static int playerLvMax = 143;
//--------END-----------------
static void showPayJNI(int payId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/PayTool", "pay", "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, payId);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

static void setIsShowExitDialog(int isShowExit) //isShowExit = 0 不显示 isShowExit = 1 显示
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "setIsShowExitDialog","(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID,isShowExit);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

static void showTipsDialog()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "showTipsDialog", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}




#endif
