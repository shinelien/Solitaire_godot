//
// Created by  on 2020/3/26.
//

#include "BoxDataManager.h"
#include "FanPaiRewardView.h"
#include "DataManager.h"
#include "SceneManager.h"
#include "DataManager.h"

USING_NS_CC;

BoxDataManager *BoxDataManager::s_instance = nullptr;

BoxDataManager *BoxDataManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new BoxDataManager();
        s_instance->init();
    }
    return s_instance;
}

void BoxDataManager::init() {
    analysisJsonConfig();
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
//    startTest();
#endif
}

bool BoxDataManager::analysisJsonConfig() {
    auto load_str = FileUtils::getInstance()->getStringFromFile("boxData.json");
    _config.Parse(load_str.c_str());
    if (_config.HasParseError()) {
        //解析出错
        CCASSERT(true, "解析出现错误");
        return false;
    }
    return true;
}

BoxDataManager::BoxDataManager() {
}

BoxDataManager::~BoxDataManager() {

}

std::shared_ptr<rapidjson::Document> getLotteryIdx(const rapidjson::Value &doc, const char* key, int &idx) {
    auto randNum1 = random(0, 99);  // 第一层的随机数值
    auto groupList = doc[key].GetArray();
    int sum = 0;
    for (int i=0; i<groupList.Size(); i++) {
        auto data = groupList[i].GetObject();
        string type2 = data["type2"].GetString();
        auto rate = data["rate"].GetInt();
        if (randNum1 >= sum && randNum1 < (rate+sum)) // 中了
        {
            auto value = std::make_shared<rapidjson::Document>();
            value->CopyFrom(groupList[i] , value->GetAllocator());
            idx = i;
            return value;
        }
        sum+=rate;
    }
    // 不应该走到这里😂 容错啥也没抽到 就当抽中了第一个
    auto value = std::make_shared<rapidjson::Document>();
    value->CopyFrom(groupList[0] , value->GetAllocator());
    idx = 0;
    return value;
}

// 道具的映射
std::unordered_map<std::string, int> ItmesType {
//    第二层概率 扑克正面 扑克背面PBack 游戏背景BG 魔法棒Magic Music
    {"BG", 1},
    {"PFore", 2},
    {"PBack", 3},
    {"Music", 5},
    {"Magic", 1000},
};
// type2 的映射
std::unordered_map<std::string, FanPaiRewardView::RewardType> FPRewardType {
//    第二层概率 扑克正面 扑克背面PBack 游戏背景BG 魔法棒Magic Music
    {"BG", FanPaiRewardView::RewardType::GameBg},
    {"PFore", FanPaiRewardView::RewardType::CardFace},
    {"PBack", FanPaiRewardView::RewardType::CardBg},
    {"Music", FanPaiRewardView::RewardType::Music},
    {"Magic", FanPaiRewardView::RewardType::Magic},
    {"BigGold", FanPaiRewardView::RewardType::BigGold},
    {"Gold", FanPaiRewardView::RewardType::SmallGold},
    {"BigGem", FanPaiRewardView::RewardType::BigDiamond},
    {"Gem", FanPaiRewardView::RewardType::SmallDiamond},
};
static vector<int> s_randPForeVec;
ValueMap BoxDataManager::lotteryOnce(const rapidjson::Value &doc, const char* key) {
    if (s_randPForeVec.empty()) {
        for(auto i = 0;i<52;++i) {
            s_randPForeVec.push_back(i);
        }
    }
    int idx = 0;
    ValueMap rewardMap;
    std::shared_ptr<rapidjson::Document> hittedDoc = getLotteryIdx(doc, key, idx);
    string hittedType = (*hittedDoc)["type2"].GetString();
    if (hittedType == "Item") {// 如果说中了道具了 接着z抽
        idx = 0;
        std::shared_ptr<rapidjson::Document> itemHittedDoc = getLotteryIdx((*hittedDoc), "items_rate", idx);
        
        string itemHittedType = (*itemHittedDoc)["type2"].GetString();
        int shopType = ItmesType.at(itemHittedType);
        auto totalCNT = DATA_M->getShopItemTotalCount(shopType); // 获取道具总数
        vector<int> randVec;
        for (int i=0; i<totalCNT; ++i) {
            randVec.push_back(i);
            randVec.insert(randVec.begin()+random(0, (int)randVec.size()-1), i);  // 插入随机
        }
        int hittedIdx = 0, faceHittedIdx = 0;
        auto sec_rate = (*itemHittedDoc)["sec_rate"].GetInt();
        auto randNum1 = random(0, 100);
        std::random_shuffle(s_randPForeVec.begin(), s_randPForeVec.end(), ShuffleFunc);
        _isChongFu = GETBOOL("box_lottery_chongfu", false);
        if (sec_rate>0 && !_isChongFu && randNum1<sec_rate) { // 凉凉了 白玩 抽到了一个重复的 上次重复了 就给次机会吧
            SETBOOL("box_lottery_chongfu", true);
            for (auto idx:randVec) {
                bool isUnlock = DATA_M->getShopItemStatus(shopType,idx);
                if (isUnlock) {
                    hittedIdx = idx;
                    if (itemHittedType == "PFore") { //正面的话 还要随机牌
                        faceHittedIdx = random(0, 51); //反正都有了 随便来一张
                    }
                    break;
                }
            }
            CCLOG("没中奖,恭喜您白玩了!!!!");
        }
        else {
            SETBOOL("box_lottery_chongfu", false);
            for (auto idx:randVec) {
                bool isUnlock = DATA_M->getShopItemStatus(shopType,idx);
                if (!isUnlock) {
                    hittedIdx = idx;
                    if (itemHittedType == "PFore") { //正面的话 还要随机牌
                        for (int i=0;i<52;i++) {
                            auto randNum = s_randPForeVec.at(i);
                            auto isBuy = DATA_M->getCardFaceStatus(2,idx,randNum);
                            if(!isBuy) {
                                faceHittedIdx = randNum;
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            CCLOG("恭喜您获得了奖品道具:%s 索引:%d 索引1:%d", itemHittedType.c_str(), hittedIdx, faceHittedIdx);
        }
        rewardMap["type2"] = Value((int)FPRewardType.at(itemHittedType));     // 配置类型
        rewardMap["shopType"] = Value(shopType);        // 商店类型
        rewardMap["idx"] = Value(hittedIdx);                  // idx 索引
        rewardMap["randNum"] = Value(faceHittedIdx);                  // faceHittedIdx 索引
        rewardMap["count"] = Value(1);                  // 数量
        _simpleResults += StringUtils::format("|%s,%d,%d",itemHittedType.c_str(),hittedIdx,faceHittedIdx);
    }
    else { // 不是道具 乖乖领钱
//        UIUtils::dumpJson(*hittedDoc); // 打印
        auto hittedType = (*hittedDoc)["type2"].GetString();
        auto values = (*hittedDoc)["values"].GetArray();
        int min = values[0].GetInt(), max=values[1].GetInt();
        auto rewardValue = random(min, max);
        CCLOG("恭喜您获得了奖品:%s 数量:%d", (*hittedDoc)["name"].GetString(), rewardValue);
        rewardMap["type2"] = Value((int)FPRewardType.at(hittedType));     // 配置类型
//        rewardMap["shopType"] = Value(shopType);        // 商店类型
        rewardMap["idx"] = Value(idx);                  // idx 索引
        rewardMap["count"] = Value(rewardValue);                  // 数量
        _simpleResults += StringUtils::format("|%s,%d,%d",hittedType,idx,rewardValue);
    }
    return rewardMap;
}

ValueVector BoxDataManager::startLottery(BoxDataManager::LotteryType lotteryType, BoxDataManager::LotteryTimes lotteryTimes, int money) {
    string skey = getKey(lotteryType);
    string slotteryTimesKey = getKey(lotteryTimes);
    CCASSERT(_config.HasMember(skey.c_str()), "config dont contain key!!!!");
    CCASSERT(_config[skey.c_str()].GetObject().HasMember(slotteryTimesKey.c_str()), "config dont contain key!!!!");
    const rapidjson::Value &lotteryConfig = _config[skey.c_str()].GetObject()[slotteryTimesKey.c_str()];
    CCLOG("------=====开始抽奖(%d)(%d)(%d)(%d)=====------", lotteryType, lotteryTimes, money, lotteryConfig.MemberCount());
    _simpleResults.clear();
    ValueVector rewardVec;
    int i = 0;
//    UIUtils::dumpJsonValue(lotteryConfig);
    for (auto it = lotteryConfig.GetObject().begin();it != lotteryConfig.GetObject().end();it++) {
        CCLOG("lotteryConfig idx:%d", i++);
//        UIUtils::dumpJsonValue(it->value);
        auto money_range = it->value["money_range"].GetArray();
        int min = money_range[0].GetInt(), max=money_range[1].GetInt();
        if (money>=min && (max==-1 || money<max)) {
            // 符合区间 开始抽奖啦
            if (lotteryTimes == LotteryTimes::One) {
                rewardVec.push_back(Value(lotteryOnce(it->value, "group")));
            }
            else/* if (lotteryTimes == LotteryTimes::Five)*/ {
                for (auto &item:it->value["group"].GetObject()) {
                    rewardVec.push_back(Value(lotteryOnce(it->value["group"], item.name.GetString())));
                }
            }
//            else if (lotteryTimes == LotteryTimes::Daily || lotteryTimes == LotteryTimes::Star) {
//                for (int i=1; i<=3; ++i) {
//                    rewardVec.push_back(Value(lotteryOnce(it->value["group"], toString(i).c_str())));
//                }
//            }
            break;
        }
    }
    CCLOG("------=====结束抽奖=====------");
//    std::shuffle(rewardVec.begin(), rewardVec.end(), ShuffleFunc);  // 结果随机排序👿
    UIUtils::FIRFirestoreAdd("operator", {
        {"key", Value("lottery")},
        {"value", Value(toString((int)lotteryType))},
        {"v1", Value((int)lotteryTimes)},
        {"v2", Value(money)},
        {"v3", Value(_simpleResults)},
        {"v4", Value(GETSTR("bu_version", "1.0.0"))},
    });
    return rewardVec;
}

std::string BoxDataManager::getKey(BoxDataManager::LotteryType lotteryType) {
    switch (lotteryType) {
        case LotteryType::Gold:
            return "TGold";
        case LotteryType::Gem:
            return "TGem";
        case LotteryType::Daily:
            return "TDaily";
        case LotteryType::Star:
            return "TStar";
    }
    return "";
}

std::string BoxDataManager::getKey(BoxDataManager::LotteryTimes lotteryTimes) {
    switch (lotteryTimes) {
        case LotteryTimes::One:
            return "one";
        case LotteryTimes::Five:
            return "five";
        case LotteryTimes::Daily:
            return "daily";
        case LotteryTimes::Star:
            return "star";
    }
    return "";
}

void BoxDataManager::startTest()
{
//    int money = 0;
//    while (money < 99999) {
//        startLottery(BoxDataManager::LotteryType::Gold, BoxDataManager::LotteryTimes::One, money);
//        startLottery(BoxDataManager::LotteryType::Gold, BoxDataManager::LotteryTimes::Five, money);
//        startLottery(BoxDataManager::LotteryType::Gem, BoxDataManager::LotteryTimes::One, money);
//        startLottery(BoxDataManager::LotteryType::Gem, BoxDataManager::LotteryTimes::Five, money);
//        money += random(1, 100);
//    }
    for (int i=0; i<100; i++) {
        startLottery(BoxDataManager::LotteryType::Gold, BoxDataManager::LotteryTimes::Five, 2000);
    }
}

void BoxDataManager::startTest1()
{
    int money = 0;
    while (money < 99999) {
        startLottery(BoxDataManager::LotteryType::Daily, BoxDataManager::LotteryTimes::Daily, money);
        startLottery(BoxDataManager::LotteryType::Star, BoxDataManager::LotteryTimes::Star, money);
        money += random(1, 100);
    }
}
