#include "GameKitHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>
#include <map>

using namespace cocos2d;

//单张牌最高分排行     one_score_rank	Single	默认	上线
//三张牌最高分排行     three_score_rank	Single	设为默认	上线
//挑战关卡星星数排行	level_star_rank	Single	设为默认	上线
//赢局数（翻一张牌）	one_bureau_rank	Single	设为默认	上线
//赢局数（翻三张牌）	three_bureau_rank	Single	设为默认	上线
//最多胜利	maximum_winning_streak
const std::map<std::string, std::string> AppleTransf {
        {"one_score_rank", "CgkI1MabvbUSEAIQAQ"},
        {"three_score_rank", "CgkI1MabvbUSEAIQAg"},
        {"level_star_rank", "CgkI1MabvbUSEAIQAw"},
        {"one_bureau_rank", "CgkI1MabvbUSEAIQBA"},
        {"three_bureau_rank", "CgkI1MabvbUSEAIQBQ"},
        {"maximum_winning_streak", "CgkI1MabvbUSEAIQBg"},
        {"maximum_diamon", "CgkI1MabvbUSEAIQBw"},
};
void GameKitHelper::saveHighScore(const std::string &leaderBoardID, int value) {
    if (AppleTransf.find(leaderBoardID) != AppleTransf.end())
    {
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "submitScore", "(Ljava/lang/String;I)V"))
        {
            jstring ID = t.env->NewStringUTF(AppleTransf.at(leaderBoardID).c_str());
            t.env->CallStaticVoidMethod(t.classID, t.methodID, ID, value);
            t.env->DeleteLocalRef(t.classID);
        }
    }
}

void GameKitHelper::showLeaderBoard() {
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "showLeaderBoard", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

#endif