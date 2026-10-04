//
// Created by Cyutao on 2018/11/16.
//

#ifndef SPACECATSOLITAIREGAME_SCOREMANAGER_H
#define SPACECATSOLITAIREGAME_SCOREMANAGER_H

#include <vector>
#include <string>
#include "AppConstant.h"

using score_t = unsigned int;
class ScoreManager {
public:
    enum class Type {
        WINCNT,         //胜利局数0
        FAILDCNT,       //失败局数
        WINRATE,        //胜率
        BESTWINTIME,    //最快胜利时间
        LONEGESTTIME,   //最长胜利时间
        WINMINMOVES,    //胜利最少步数5
        WINMAXMOVES,    //胜利最多步数
        WINNOMOVES,     //无返回胜利数
        BESTSCORE,      //最高分数
        WINNINGSNT,     //当前连胜局数9
        LONGESTWINNINGSCNT,//最高连胜局数10
        TOTALTIME,      //总游戏时间
        EXTRASCORE,     //额外得分
        TOTALSCORE,     //总得分
        RANDBESTSCORE,  //随机最高分
        LIVEBESTSCORE,  //活局最高分
        TOTALSTAR,      //总星星数
        HighestWeiJiaSiScore,//最高维加斯累计积分
        FAILDNINGSNT,   //连败局数
        TOTAL
    };
    enum class ComType{
        WINCNT,         //胜利局数0
        FAILDCNT,       //失败局数
        TOTALSTAR,      //总星星数
        MAGICCNT,     //魔法棒总数
        TIPSCNT,        //提示总数
        BACKCNT,        //回退总数
        EFFWINCNT,      //辅助胜利局数0
        EFFFAILDCNT,    //辅助失败局数
        MINSCORE,       //活局最低分
        TOTAL
    };
    
    enum class OldType{
        WIN,        //胜负
        SCORE,      //分数
        TIME,       //时间
        MAGIC,      //魔法棒使用数目
        TOTAL
    };

    virtual ~ScoreManager();
    static ScoreManager* getInstance();

    void setScore(int cardNums, Type type, score_t score, bool isAdd = false);
    void setScore(int gameType, ValueVector valueVector);
    unsigned int getScore(int gameType, Type type);
    float getRate(int gameType, Type type);
    bool isNewRecordAndMinus(int gameType, Type type);
    //经典总胜利局数
    int getWinTotalCNT(bool win = false);
    //----------------------------------用户评分用
    //总局数
    int getTotalCNT(int gameType);
    //未开启辅助胜率
    float getComRate(int gameType, int type);
    //未开启辅助总场次
    int getComTotalCNT(int gameType,int type);
    //开启辅助胜率
    float getEffComRate(int gameType, int type);
    //开启辅助总场次
    int getEffComTotalCNT(int gameType,int type);
    //洗牌数，提示数，回退数，得分，时间
    void setDataCNT(int gameType, int shuffleCNT,int tipsCNT,int useBackCNT,int score,int time);
    //平均星星数
    float getStarCNT(int gameType);
    //平均魔法棒数
    float getMagicCNT(int gameType);
    //平均提示数
    float getTipsCNT(int gameType);
    //平均回退数
    float getBackCNT(int gameType);
    //最低分数
    float getMinScore(int gameType);
    //------------------------------------------------
    //------获取上一局信息
    bool getOldWin(int gameType);
    int getOldScore(int gameType);
    int getOldTime(int gameType);
    int getOldMagicNum(int gameType);
protected:
    bool init();

private:
    ScoreManager();
    static ScoreManager* s_instance;

    std::vector<score_t> oneCardScores;
    std::vector<score_t> threeCardScores;
    
    //用户评分用
    std::vector<score_t> oneRandomCardScores;
    std::vector<score_t> threeRandomCardScores;
    std::vector<score_t> oneHuoCardScores;
    std::vector<score_t> threeHuoCardScores;
    
    //计算牌局难度用
    std::vector<score_t> oneHuoCardOldScores;
    std::vector<score_t> threeHuoCardOldScores;
};


#endif //SPACECATSOLITAIREGAME_SCOREMANAGER_H
