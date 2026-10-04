//
// Created by Cyutao on 2018/11/16.
//

#include "ScoreManager.h"
#include "GameKitHelper.h"
#include "UIUtils.h"
#include "DataManager.h"
#include "SpriteManager.h"

ScoreManager* ScoreManager::s_instance = nullptr;
ScoreManager::~ScoreManager() {

}

ScoreManager::ScoreManager() {
}

ScoreManager *ScoreManager::getInstance() {
    if (s_instance == nullptr)
    {
        s_instance = new (std::nothrow)ScoreManager();
        s_instance->init();
    }
    return s_instance;
}

bool ScoreManager::init() {
    for (int i = 0; i < (int) Type::TOTAL; ++i) {
        oneCardScores.push_back(GETINTEGER(StringUtils::format("oneCardData_%d", i).c_str(), 0));
        threeCardScores.push_back(GETINTEGER(StringUtils::format("threeCardData_%d", i).c_str(), 0));
    }
    for (int i = 0; i < (int) ComType::TOTAL; ++i) {
        oneRandomCardScores.push_back(GETINTEGER(StringUtils::format("oneRandomCardData_%d", i).c_str(), 0));
        threeRandomCardScores.push_back(GETINTEGER(StringUtils::format("threeRandomCardData_%d", i).c_str(), 0));
        oneHuoCardScores.push_back(GETINTEGER(StringUtils::format("oneHuoCardData_%d", i).c_str(), 0));
        threeHuoCardScores.push_back(GETINTEGER(StringUtils::format("threeHuoCardData_%d", i).c_str(), 0));
    }
    for(int i = 0;i < (int) OldType::TOTAL;++i)
    {
        oneHuoCardOldScores.push_back(GETINTEGER(StringUtils::format("oneHuoCardOldScores_%d", i).c_str(), 0));
        threeHuoCardOldScores.push_back(GETINTEGER(StringUtils::format("threeHuoCardOldScores_%d", i).c_str(), 0));
    }
    return true;
}

void ScoreManager::setScore(int cardNums, ScoreManager::Type type, score_t score, bool isAdd) {
    auto &scoreVec = cardNums==1?oneCardScores:threeCardScores;
    if (isAdd)
        scoreVec[(int)type] += score;
    else
        scoreVec[(int)type] = score;
}

string getKey(ScoreManager::Type type) {
    switch (type) {
        case ScoreManager::Type::WINCNT:
            return "WIN";
        case ScoreManager::Type::FAILDCNT:
            return "FAILD";
        case ScoreManager::Type::BESTWINTIME:    //最快胜利时间
            return "USE_TIME";
        case ScoreManager::Type::WINMINMOVES:    //胜利最少步数5
            return "USE_MOVES";
        case ScoreManager::Type::BESTSCORE:      //最高分数
            return "SCORE";
        case ScoreManager::Type::TOTALSTAR:      //总星星数
            return "STAR";
    }
    return "";
}


void ScoreManager::setScore(int gameType, ValueVector valueVector) {
    ValueMap paramMap;
    for (auto &value:valueVector) {
        auto valueMap = value.asValueMap();
//        auto gameType = valueMap.at("gameType").asInt();
        auto &scoreVec = gameType == 1 ? oneCardScores : threeCardScores;
        auto type = valueMap.at("type").asInt(), score = valueMap.at("score").asInt();
        auto formatKey = gameType == 1 ? "oneCardData_%d" : "threeCardData_%d";
        auto formatTimeKey = gameType == 1 ? "oneCardData_%d_time" : "threeCardData_%d_time";
        bool needFlush = false;
        bool newHighScore = false; // 产生了新的最高分
        switch (valueMap.at("op").asString().at(0)) {
            case '+':
                scoreVec[type] += score;
                needFlush = true;
                break;
            case '>':
                if (score>scoreVec[type] || (scoreVec[type] == 0&&score > 0)) {//防止负数
                    scoreVec[type] = score;
                    needFlush = true;
                    newHighScore = type == (int)Type::TOTALSCORE;
                }
                break;
            case '<':
                if (score<scoreVec[type] || (scoreVec[type] == 0&&score > 0)) {//防止负数
                    scoreVec[type] = score;
                    needFlush = true;
                }
                break;
            case '=':
                scoreVec[type] = score;
                needFlush = true;
                break;
        }
        if (needFlush) {
//            SETINTEGER(StringUtils::format(formatKey, type).c_str(), scoreVec[type]);
//            UIUtils::FIRAnalyticsUserProperty(StringUtils::format(formatKey, type).c_str(), toString(scoreVec[type]));
        }
        if ((Type) type == Type::WINCNT || (Type) type == Type::FAILDCNT) {
            auto totalCNT = scoreVec[(int) Type::WINCNT] + scoreVec[(int) Type::FAILDCNT];
            if (totalCNT > 0) {
                scoreVec[(int) Type::WINRATE] = int(scoreVec[(int) Type::WINCNT] * 100.0 / totalCNT);
//                SETINTEGER(StringUtils::format(formatKey, (int) Type::WINRATE).c_str(), scoreVec[(int) Type::WINRATE]);
            }
            GameKitHelper::saveHighScore(gameType == 1 ? "one_card_ranks" : "three_card_ranks", scoreVec[(int) Type::WINCNT]);
            GameKitHelper::saveHighScore("total_ranks", oneCardScores[(int) Type::WINCNT]+threeCardScores[(int) Type::WINCNT]);      // 赢的局数
            //分别记录经典困难胜利失败局数
            if (DATA_M->getGameType() == DataManager::GameType::Random) {
                //                auto &scoreRandomVec = gameType == 1 ? oneRandomCardScores : threeRandomCardScores;
                //                if(SPRITE_M->getIsOpenEffective())
                //                {//困难开启辅助胜败局数
                //                    scoreRandomVec[(Type) type == Type::WINCNT?6:7] += 1;
                //                    SETINTEGER(StringUtils::format("oneRandomCardData_%d", (Type) type == Type::WINCNT?6:7).c_str(),scoreRandomVec[(Type) type == Type::WINCNT?6:7]);
                //                }
                //                else
                //                {//困难关闭辅助胜败局数
                //                    scoreRandomVec[(Type) type == Type::WINCNT?0:1] += 1;
                //                    SETINTEGER(StringUtils::format("oneRandomCardData_%d", (Type) type == Type::WINCNT?0:1).c_str(),scoreRandomVec[(Type) type == Type::WINCNT?0:1]);
                //                }
            }
            else if (DATA_M->getGameType() == DataManager::GameType::Huo&&getTotalCNT(gameType) >= 0) {
                //用户评分。
                auto &scoreHuoVec = gameType == 1 ? oneHuoCardScores : threeHuoCardScores;
                auto &scoreHuoOldVec = gameType == 1 ? oneHuoCardOldScores : threeHuoCardOldScores;
                if(SPRITE_M->getIsOpenEffective())
                {//经典开启辅助胜败局数
                    scoreHuoVec[(Type) type == Type::WINCNT?6:7] += 1;
                    SETINTEGER(StringUtils::format("oneHuoCardData_%d", (Type) type == Type::WINCNT?6:7).c_str(),scoreHuoVec[(Type) type == Type::WINCNT?6:7]);
                }
                else
                {//经典关闭辅助胜败局数
                    scoreHuoVec[(Type) type == Type::WINCNT?0:1] += 1;
                    SETINTEGER(StringUtils::format("oneHuoCardData_%d", (Type) type == Type::WINCNT?0:1).c_str(),scoreHuoVec[(Type) type == Type::WINCNT?0:1]);
                    
                    //记录上一局胜负信息
                    auto win = (Type) type == Type::WINCNT;
                    scoreHuoOldVec[(int) OldType::WIN] = win ? 1 : 0;

                    SETINTEGER(StringUtils::format(gameType == 1 ?"oneHuoCardOldScores_%d":"threeHuoCardOldScores_%d", (int) OldType::WIN).c_str(),scoreHuoOldVec[(int) OldType::WIN]);
                }
            }
        } else if ((Type) type == Type::WINNINGSNT) {
            if (scoreVec[(int) Type::WINNINGSNT] > scoreVec[(int) Type::LONGESTWINNINGSCNT]) {
                scoreVec[(int) Type::LONGESTWINNINGSCNT] = scoreVec[(int) Type::WINNINGSNT];
//                SETINTEGER(StringUtils::format(formatKey, (int) Type::LONGESTWINNINGSCNT).c_str(), scoreVec[(int) Type::LONGESTWINNINGSCNT]);
            }
            GameKitHelper::saveHighScore(gameType == 1 ? "top1_combo_socre" : "top3_combo_socre", scoreVec[(int) Type::LONGESTWINNINGSCNT]);      // 赢的局数
        } else if ((Type) type == Type::TOTALSCORE) {
            GameKitHelper::saveHighScore(gameType == 1 ? "top1_socre" : "top3_socre", scoreVec[(int) Type::TOTALSCORE]);
            if (true) {
                UIUtils::updateScore(score, 0);
//                if (gameType == 1) UIUtils::updateScore(score, 0);
//                else UIUtils::updateScore(0, score);
            }
        }
        else if((Type) type == Type::TOTALSTAR&&getTotalCNT(gameType) >= 0)
        {//用户评分。 前两局不记录
            if (DATA_M->getGameType() == DataManager::GameType::Random) {
                //                auto &scoreRandomVec = gameType == 1 ? oneRandomCardScores : threeRandomCardScores;
                //                scoreRandomVec[(int)ComType::TOTALSTAR] += score;
                //                SETINTEGER(StringUtils::format("oneRandomCardData_%d", (int)ComType::TOTALSTAR).c_str(),scoreRandomVec[(int)ComType::TOTALSTAR]);
            }
            else if (DATA_M->getGameType() == DataManager::GameType::Huo) {
                auto &scoreHuoVec = gameType == 1 ? oneHuoCardScores : threeHuoCardScores;
                scoreHuoVec[(int)ComType::TOTALSTAR] += score;
                SETINTEGER(StringUtils::format("oneHuoCardData_%d", (int)ComType::TOTALSTAR).c_str(),scoreHuoVec[(int)ComType::TOTALSTAR]);
            }
        }
        else if((Type) type == Type::BESTSCORE)
        {//记录上一局得分
            auto &scoreHuoOldVec = gameType == 1 ? oneHuoCardOldScores : threeHuoCardOldScores;
            if (DATA_M->getGameType() == DataManager::GameType::Huo)
            {
                scoreHuoOldVec[(int) OldType::SCORE] = score;
                SETINTEGER(StringUtils::format(gameType == 1 ?"oneHuoCardOldScores_%d":"threeHuoCardOldScores_%d", (int) OldType::SCORE).c_str(),scoreHuoOldVec[(int) OldType::SCORE]);
            }
        }
        else if((Type) type == Type::BESTWINTIME)
        {//记录上一局时间
            auto &scoreHuoOldVec = gameType == 1 ? oneHuoCardOldScores : threeHuoCardOldScores;
            if (DATA_M->getGameType() == DataManager::GameType::Huo)
            {
                scoreHuoOldVec[(int) OldType::TIME] = score;
                SETINTEGER(StringUtils::format(gameType == 1 ?"oneHuoCardOldScores_%d":"threeHuoCardOldScores_%d", (int) OldType::TIME).c_str(),scoreHuoOldVec[(int) OldType::TIME]);
            }
        }
        else if((Type) type == Type::HighestWeiJiaSiScore)
        {
            auto num = scoreVec[type];
            if((int)num < score)
            {
                scoreVec[type] = score;
            }
        }
        if (needFlush) {
            auto it = valueMap.find("new");
            if (it != valueMap.end()) {
                SETINTEGER(StringUtils::format(formatTimeKey, type).c_str(), it->second.asInt());
                FLUSH();
            }
        }
        auto key = getKey((Type)type);
        if (!key.empty())
            paramMap[key] = score;
    }
    paramMap["GameType"] = Value(gameType);
    paramMap["BureauType"] = Value((int)DATA_M->getGameType());
    AsyncTaskPool::getInstance()->enqueue(AsyncTaskPool::TaskType::TASK_OTHER, [this, gameType, paramMap](void*){
        auto &scoreVec = gameType == 1 ? oneCardScores : threeCardScores;
        auto formatKey = gameType == 1 ? "oneCardData_%d" : "threeCardData_%d";
        for (int i=0; i<scoreVec.size(); ++i) {
            SETINTEGER(StringUtils::format(formatKey, i).c_str(), scoreVec.at(i));
        }
        FLUSH();
        UIUtils::FIRAnalyticsEvent("event_game_end", paramMap);
        auto totalCNT = oneCardScores[(int) Type::WINCNT] + threeCardScores[(int) Type::WINCNT];
        ValueMap valueMap1;
        if (DataManager::getInstance()->recordLayerData()) {
            if (totalCNT == 10) {
                UIUtils::FIRAnalyticsEvent(StringUtils::format("event_game_wincnt_%d", totalCNT), valueMap1);
            }
        }
        if (totalCNT == 30 || totalCNT == 50 || totalCNT == 70) {
            UIUtils::FIRAnalyticsEvent(StringUtils::format("event_game_wincnt_%d", totalCNT), valueMap1);
        }
    }, nullptr, []{});
}

unsigned int ScoreManager::getScore(int gameType, ScoreManager::Type type) {
    auto &scoreVec = gameType==1?oneCardScores:threeCardScores;
    try {
        return scoreVec[(int)type];
    }
    catch (std::out_of_range e) {
        return 0;
    }
}

bool ScoreManager::isNewRecordAndMinus(int gameType, Type type)
{
    auto formatTimeKey = gameType == 1 ? "oneCardData_%d_time" : "threeCardData_%d_time";
    auto times = GETINTEGER(StringUtils::format(formatTimeKey, type).c_str(), 0);
    SETINTEGER(StringUtils::format(formatTimeKey, type).c_str(), times-1);
    return times>0;
}

float ScoreManager::getRate(int gameType, ScoreManager::Type type) {
    auto &scoreVec = gameType == 1 ? oneCardScores : threeCardScores;
    auto totalCNT = scoreVec[(int) Type::WINCNT] + scoreVec[(int) Type::FAILDCNT];
    if (totalCNT > 0) {
        return scoreVec[(int) type] * 100.0 / totalCNT;
    }
    else
        return 0;
}

int ScoreManager::getWinTotalCNT(bool win)
{
    auto totalCNT = oneCardScores[(int) Type::WINCNT] + threeCardScores[(int) Type::WINCNT];
    if (!win)
        totalCNT += oneCardScores[(int) Type::FAILDCNT] + threeCardScores[(int) Type::FAILDCNT]; // 测试
    return totalCNT;
}

//----------------------------------用户评分用-------------------------------
int ScoreManager::getTotalCNT(int gameType)
{
    auto &scoreVec = gameType == 1 ? oneCardScores : threeCardScores;
    auto totalCNT = scoreVec[(int) Type::WINCNT] + scoreVec[(int) Type::FAILDCNT];
    return totalCNT;
}

float ScoreManager::getComRate(int gameType, int type)
{//经典与困难的胜率
    if (type == 1) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        auto totalCNT = getComTotalCNT(gameType,type);
        if (totalCNT > 0) {
            return scoreRandomVec[(int)ComType::WINCNT] * 100.0 / totalCNT;
        }
        else
            return -1;
    }
    else if (type == 0) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        auto totalCNT = getComTotalCNT(gameType,type);
        if (totalCNT > 0) {
            return scoreHuoVec[(int)ComType::WINCNT] * 100.0 / totalCNT;
        }
        else
            return -1;
    }
    return -1;
}

float ScoreManager::getEffComRate(int gameType, int type)
{//经典与困难的胜率
    if (type == 1) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        auto totalCNT = getEffComTotalCNT(gameType,type);
        if (totalCNT > 0) {
            return scoreRandomVec[(int)ComType::EFFWINCNT] * 100.0 / totalCNT;
        }
        else
            return -1;
    }
    else if (type == 0) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        auto totalCNT = getEffComTotalCNT(gameType,type);
        if (totalCNT > 0) {
            return scoreHuoVec[(int)ComType::EFFWINCNT] * 100.0 / totalCNT;
        }
        else
            return -1;
    }
    return -1;
}

int ScoreManager::getComTotalCNT(int gameType,int type)
{//未开启翻牌有效经典与困难的总局数
    if (type == 1) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        auto totalCNT = scoreRandomVec[(int)ComType::WINCNT] + scoreRandomVec[(int)ComType::FAILDCNT];
        return totalCNT;
    }
    else if (type == 0) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        auto totalCNT = scoreHuoVec[(int)ComType::WINCNT] + scoreHuoVec[(int)ComType::FAILDCNT];
        return totalCNT;
    }
    return 0;
}

int ScoreManager::getEffComTotalCNT(int gameType,int type)
{
    //开启翻牌有效经典与困难的总局数
    if (type == 1) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        auto totalCNT = scoreRandomVec[(int)ComType::EFFWINCNT] + scoreRandomVec[(int)ComType::EFFFAILDCNT];
        return totalCNT;
    }
    else if (type == 0) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        auto totalCNT = scoreHuoVec[(int)ComType::EFFWINCNT] + scoreHuoVec[(int)ComType::EFFFAILDCNT];
        return totalCNT;
    }
    return 0;
}

void ScoreManager::setDataCNT(int gameType, int magicCNT,int tipsCNT,int useBackCNT, int score,int time)
{
//    if(getTotalCNT(gameType) <= 10)
//    {//前10局不记录
//        return;
//    }
    if (DATA_M->getGameType() == DataManager::GameType::Random) {
        //        auto &scoreRandomVec = gameType == 1 ? oneRandomCardScores : threeRandomCardScores;
        //        scoreRandomVec[(int)ComType::SHUFFLECNT] += shuffleCNT;
        //        SETINTEGER(StringUtils::format("oneRandomCardData_%d", (int)ComType::SHUFFLECNT).c_str(),scoreRandomVec[(int)ComType::SHUFFLECNT]);
        //        scoreRandomVec[(int)ComType::TIPSCNT] += tipsCNT;
        //        SETINTEGER(StringUtils::format("oneRandomCardData_%d", (int)ComType::TIPSCNT).c_str(),scoreRandomVec[(int)ComType::TIPSCNT]);
        //        scoreRandomVec[(int)ComType::BACKCNT] += useBackCNT;
        //        SETINTEGER(StringUtils::format("oneRandomCardData_%d", (int)ComType::BACKCNT).c_str(),scoreRandomVec[(int)ComType::BACKCNT]);
        //        if((scoreRandomVec[(int)ComType::MINSCORE] > score||scoreRandomVec[(int)ComType::MINSCORE] == 0)&&!SPRITE_M->getIsOpenEffective())
        //        {//非辅助最低得分
        //            scoreRandomVec[(int)ComType::MINSCORE] = score;
        //            SETINTEGER(StringUtils::format("oneRandomCardData_%d", (int)ComType::MINSCORE).c_str(),scoreRandomVec[(int)ComType::MINSCORE]);
        //        }
    }
    else if (DATA_M->getGameType() == DataManager::GameType::Huo) {
        auto &scoreHuoVec = gameType == 1 ? oneHuoCardScores : threeHuoCardScores;
        scoreHuoVec[(int)ComType::MAGICCNT] += magicCNT;
        SETINTEGER(StringUtils::format("oneHuoCardData_%d", (int)ComType::MAGICCNT).c_str(),scoreHuoVec[(int)ComType::MAGICCNT]);
        scoreHuoVec[(int)ComType::TIPSCNT] += tipsCNT;
        SETINTEGER(StringUtils::format("oneHuoCardData_%d", (int)ComType::TIPSCNT).c_str(),scoreHuoVec[(int)ComType::TIPSCNT]);
        scoreHuoVec[(int)ComType::BACKCNT] += useBackCNT;
        SETINTEGER(StringUtils::format("oneHuoCardData_%d", (int)ComType::BACKCNT).c_str(),scoreHuoVec[(int)ComType::BACKCNT]);
        if(1)//scoreHuoVec[(int)ComType::MINSCORE] > score||scoreHuoVec[(int)ComType::MINSCORE] == 0)
        {
            scoreHuoVec[(int)ComType::MINSCORE] = score;
            SETINTEGER(StringUtils::format("oneHuoCardData_%d", (int)ComType::MINSCORE).c_str(),scoreHuoVec[(int)ComType::MINSCORE]);
        }
        
        auto &scoreHuoOldVec = gameType == 1 ? oneHuoCardOldScores : threeHuoCardOldScores;
        scoreHuoOldVec[(int)OldType::MAGIC] = magicCNT;
        SETINTEGER(StringUtils::format(gameType == 1 ?"oneHuoCardOldScores_%d":"threeHuoCardOldScores_%d", (int) OldType::MAGIC).c_str(),scoreHuoOldVec[(int) OldType::MAGIC]);
    }
}

//胜局平均星星数
float ScoreManager::getStarCNT(int gameType)
{
    if (DATA_M->getGameType() == DataManager::GameType::Random) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        if(scoreRandomVec[(int)ComType::WINCNT] + scoreRandomVec[(int)ComType::EFFWINCNT] == 0)
        {
            return -1;
        }
        auto starCNT = (float)scoreRandomVec[(int)ComType::TOTALSTAR] / (float)(scoreRandomVec[(int)ComType::WINCNT] + scoreRandomVec[(int)ComType::EFFWINCNT]);
        return starCNT;
    }
    else if (DATA_M->getGameType() == DataManager::GameType::Huo) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        if(scoreHuoVec[(int)ComType::WINCNT] + scoreHuoVec[(int)ComType::EFFWINCNT] == 0)
        {
            return -1;
        }
        auto starCNT = (float)scoreHuoVec[(int)ComType::TOTALSTAR] / (float)(scoreHuoVec[(int)ComType::WINCNT] + scoreHuoVec[(int)ComType::EFFWINCNT]);
        return starCNT;
    }
    return -1;
}
//胜局魔法棒数数
float ScoreManager::getMagicCNT(int gameType)
{
    if (DATA_M->getGameType() == DataManager::GameType::Random) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        if(scoreRandomVec[(int)ComType::WINCNT] + scoreRandomVec[(int)ComType::EFFWINCNT] == 0)
        {
            return -1;
        }
        auto MagicCNT = (float)scoreRandomVec[(int)ComType::MAGICCNT] / (float)(scoreRandomVec[(int)ComType::WINCNT] + scoreRandomVec[(int)ComType::EFFWINCNT]);
        return MagicCNT;
    }
    else if (DATA_M->getGameType() == DataManager::GameType::Huo) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        if(scoreHuoVec[(int)ComType::WINCNT] + scoreHuoVec[(int)ComType::EFFWINCNT] == 0)
        {
            return -1;
        }
        auto MagicCNT = (float)scoreHuoVec[(int)ComType::MAGICCNT] / (float)(scoreHuoVec[(int)ComType::WINCNT] + scoreHuoVec[(int)ComType::EFFWINCNT]);
        return MagicCNT;
    }
    return -1;
}
//胜局平均提示数
float ScoreManager::getTipsCNT(int gameType)
{
    if (DATA_M->getGameType() == DataManager::GameType::Random) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        if(scoreRandomVec[(int)ComType::WINCNT] == 0)
        {
            return -1;
        }
        auto tipsCNT = (float)scoreRandomVec[(int)ComType::TIPSCNT] / (float)(scoreRandomVec[(int)ComType::WINCNT] + scoreRandomVec[(int)ComType::EFFWINCNT]);
        return tipsCNT;
    }
    else if (DATA_M->getGameType() == DataManager::GameType::Huo) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        if(scoreHuoVec[(int)ComType::WINCNT] == 0)
        {
            return -1;
        }
        auto tipsCNT = (float)scoreHuoVec[(int)ComType::TIPSCNT] / (float)(scoreHuoVec[(int)ComType::WINCNT] + scoreHuoVec[(int)ComType::EFFWINCNT]);
        return tipsCNT;
    }
    return -1;
}
//胜局平均回退数
float ScoreManager::getBackCNT(int gameType)
{
    if (DATA_M->getGameType() == DataManager::GameType::Random) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        if(scoreRandomVec[(int)ComType::WINCNT] == 0)
        {
            return -1;
        }
        auto backCNT = (float)scoreRandomVec[(int)ComType::BACKCNT] / (float)(scoreRandomVec[(int)ComType::WINCNT] + scoreRandomVec[(int)ComType::EFFWINCNT]);
        return backCNT;
    }
    else if (DATA_M->getGameType() == DataManager::GameType::Huo) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        if(scoreHuoVec[(int)ComType::WINCNT] == 0)
        {
            return -1;
        }
        auto backCNT = (float)scoreHuoVec[(int)ComType::BACKCNT] / (float)(scoreHuoVec[(int)ComType::WINCNT] + scoreHuoVec[(int)ComType::EFFWINCNT]);
        return backCNT;
    }
    return -1;
}
//最低分数
float ScoreManager::getMinScore(int gameType)
{
    if (DATA_M->getGameType() == DataManager::GameType::Random) {
        auto &scoreRandomVec = gameType == 0 ? oneRandomCardScores : threeRandomCardScores;
        auto minScore = scoreRandomVec[(int)ComType::MINSCORE];
        return minScore;
    }
    else if (DATA_M->getGameType() == DataManager::GameType::Huo) {
        auto &scoreHuoVec = gameType == 0 ? oneHuoCardScores : threeHuoCardScores;
        auto minScore = scoreHuoVec[(int)ComType::MINSCORE];
        return minScore;
    }
    return -1;
}
//----------------------------------------

//------获取上一局信息
bool ScoreManager::getOldWin(int gameType)
{
    auto &scoreHuoOldVec = gameType == 0 ? oneHuoCardOldScores : threeHuoCardOldScores;
    auto win = scoreHuoOldVec[(int)OldType::WIN] == 1;
    return win;
}
int ScoreManager::getOldScore(int gameType)
{
    auto &scoreHuoOldVec = gameType == 0 ? oneHuoCardOldScores : threeHuoCardOldScores;
    return scoreHuoOldVec[(int)OldType::SCORE];
}
int ScoreManager::getOldTime(int gameType)
{
    auto &scoreHuoOldVec = gameType == 0 ? oneHuoCardOldScores : threeHuoCardOldScores;
    return scoreHuoOldVec[(int)OldType::TIME];
}

int ScoreManager::getOldMagicNum(int gameType)
{
    auto &scoreHuoOldVec = gameType == 0 ? oneHuoCardOldScores : threeHuoCardOldScores;
    return scoreHuoOldVec[(int)OldType::MAGIC];
}
