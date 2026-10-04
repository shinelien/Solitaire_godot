//
//  RankManager.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by Cyutao on 2021/5/17.
//

#include "RankManager.hpp"
#include "../utils/UIUtils.h"
#include "DataManager.h"

RankManager* RankManager::s_instance = nullptr;

USING_NS_CC;
using namespace std;
using namespace rapidjson;
RankManager* RankManager::getInstance()
{
    if (s_instance == nullptr) {
        s_instance = new RankManager();
    }
    return s_instance;
}

void RankManager::init() {
    for(auto it: ProductPrice) {
        auto product = std::make_shared<Product>(it.first, std::get<0>(it.second), std::get<1>(it.second), std::get<2>(it.second), std::get<3>(it.second), std::get<4>(it.second));
        _productsOrders.push_back(product);
    }
    std::sort(_productsOrders.begin(), _productsOrders.end(), [](std::shared_ptr<Product> a, std::shared_ptr<Product> b)->int{
        return a->getPrice() < b->getPrice();
    });
    for(auto it: SubProductPrice) {
        auto product = std::make_shared<Product>(it.first, std::get<0>(it.second), std::get<1>(it.second), std::get<2>(it.second), std::get<3>(it.second), std::get<4>(it.second));
        _subProductsOrders[product->getID()] = product;
    }
    updateProducts();
}

void RankManager::updateProducts() {
//    if (DATA_M->isVipNoAds()) {
//        auto product = _productsOrders.front();
//        if (product->getID() == "gold_0") {
//            _productsOrders.erase(_productsOrders.begin());
//        }
//    }
}

void RankManager::setRankList(const std::string &str) {
    _rankConfig.Parse<0>(str.c_str());
    CCLOG("DBManager2c++: %s", str.c_str());
    if (_rankConfig.HasParseError())
    {
        CCLOG("rank list json error");
        return;
    }
    _rankList.clear();
    auto array = _rankConfig["list"].GetArray();
    for (int i = array.Size()-1; i >=0 ; i--) {
        _rankList.push_back(RankModel(array[i]));
    }
}

void RankManager::setRankList(const ValueVector valueVec)
{
    _rankList.clear();
    
    for (int i = valueVec.size()-1; i >=0 ; i--) {
        ValueMap valueMap = valueVec[i].asValueMap();
        _rankList.push_back(RankModel(valueMap));
    }
}

const std::vector<RankModel> &RankManager::getRankList() const {
    return _rankList;
}

std::shared_ptr<Product> RankManager::getProduct(const std::string &id)
{
    auto key = id;
    auto pos = id.find(HOT_KEY);
    if (pos != string::npos) { // 热销商品
        key = id.substr(HOT_KEY.length());
    }
    for (auto product: _productsOrders) {
        if (product->getID() == key) {
            return product;
        }
    }
    return nullptr;
}

std::shared_ptr<Product> RankManager::getSubProduct(const std::string &id)
{
    auto it = _subProductsOrders.find(id);
    if (it != _subProductsOrders.end()) {
        return it->second;
    }
    return nullptr;
}

string RankModel::getName() const{
    std::string name = _name;
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    std::string uuid = UIUtils::getAD();
    auto str = DATA_M->getMyName() == ""?"ME":DATA_M->getMyName();
    name = _key == uuid ? str : _name;
#endif
    return name;
}

void RankModel::setName(const string &name) {
    _name = name;
}

int RankModel::getP1() const {
    return _p1;
}

void RankModel::setP1(int p1) {
    _p1 = p1;
}

int RankModel::getP2() const {
    return _p2;
}

void RankModel::setP2(int p2) {
    _p2 = p2;
}

RankModel::RankModel(const string &name, int p1, int p2) : _name(name), _p1(p1), _p2(p2) {
}

RankModel::RankModel(rapidjson::Value &Value) {
    if (Value.IsObject()) {
        try {
            auto obj = Value.GetObject();
            setP1(obj.HasMember("p1")?obj["p1"].GetInt():0);
            setP2(obj.HasMember("p2")?obj["p2"].GetInt():0);

            if (obj.HasMember("fishArray")) {
                const auto &fishArray = obj["fishArray"].GetArray();
                vector<int> tfishVec;
                for (int i = 0; i<fishArray.Size(); ++i) {
                    auto v = fishArray[i].GetInt();
                    tfishVec.push_back(v);
                }
                setFishVec(tfishVec);
            }
            if (obj.HasMember("isDailyArray")) {
                const auto &isDailyVec = obj["isDailyArray"].GetArray();
                vector<bool> tisDailyVec;
                for (int i = 0; i<isDailyVec.Size(); ++i) {
                    auto v = isDailyVec[i].GetInt();
                    tisDailyVec.push_back(v == 1);
                }
                setIsDailyVec(tisDailyVec);
            }
            if (obj.HasMember("isFashTankUnlockArray")) {
                const auto &isFashTankVec = obj["isFashTankUnlockArray"].GetArray();
                vector<bool> tisFashTankVec;
                for (int i = 0; i<isFashTankVec.Size(); ++i) {
                    auto v = isFashTankVec[i].GetInt();
                    tisFashTankVec.push_back(v == 1);
                }
                setIsFashTankUnlockVec(tisFashTankVec);
            }

            setFishTankIdx(obj.HasMember("fashTankIdx")?obj["fashTankIdx"].GetInt():0);
            setCy(obj.HasMember("cy")?obj["cy"].GetString():"US");
            setLv(obj.HasMember("playerLv")?obj["playerLv"].GetInt():1);
            setKey(obj.HasMember("key")?obj["key"].GetString():"key");
            setName(obj.HasMember("name")?obj["name"].GetString():"Player");
        }
        catch (exception e) {
            CCLOGERROR("RankModel exception %s", e.what());
        }
    }
}

RankModel::RankModel(ValueMap &valueMap)
{
    
    _key = valueMap["key"].asString();
    _name = valueMap["name"].asString();
    _p1 = !valueMap["p1"].isNull()?valueMap["p1"].asInt():0;
    _p2 = !valueMap["p2"].isNull()?valueMap["p2"].asInt():0;
    if (!valueMap["fishArray"].isNull()) {
        const auto &fishArray = valueMap["fishArray"].asValueVector();
        for (int i = 0; i<fishArray.size(); ++i) {
            auto v = fishArray[i].asInt();
            _fishVec.push_back(v);
        }
    }
    if (!valueMap["isDailyArray"].isNull()) {
        const auto &isDailyVec = valueMap["isDailyArray"].asValueVector();
        for (int i = 0; i<isDailyVec.size(); ++i) {
            auto v = isDailyVec[i].asInt();
            _isDailyVec.push_back(v == 1);
        }
    }
    if (!valueMap["isFashTankUnlockArray"].isNull()) {
        const auto &isFashTankVec = valueMap["isFashTankUnlockArray"].asValueVector();
        for (int i = 0; i<isFashTankVec.size(); ++i) {
            auto v = isFashTankVec[i].asInt();
            _isFashTankUnlockVec.push_back(v == 1);
        }
    }
    
    
    _fishTankIdx = !valueMap["fashTankIdx"].isNull()?valueMap["fashTankIdx"].asInt():0;
    _cy = !valueMap["cy"].isNull()?valueMap["cy"].asString():"US";
    _lv = !valueMap["playerLv"].isNull()?valueMap["playerLv"].asInt():1;
}

void RankModel::setKey(const string &key) {
    _key = key;
}

void RankModel::setCy(const string &cy) {
    _cy = cy;
}

void RankModel::setFishVec(const vector<int> &fishVec) {
    _fishVec = fishVec;
}

void RankModel::setIsDailyVec(const vector<bool> &isDailyVec) {
    _isDailyVec = isDailyVec;
}

void RankModel::setIsFashTankUnlockVec(const vector<bool> &isFashTankUnlockVec) {
    _isFashTankUnlockVec = isFashTankUnlockVec;
}

void RankModel::setFishTankIdx(int fishTankIdx) {
    _fishTankIdx = fishTankIdx;
}

void RankModel::setLv(int lv) {
    _lv = lv;
}

Product::Product(std::string id, float money, int price, float ex, float hotMoney, float hotPrice):
_id(id),
_money(money),
_price(price),
_ex(ex),
_hotMoney(hotMoney),
_hotPrice(hotPrice)
{
    
}

std::string Product::getHotShowStr() {
    if (_hotShowStr == "") {
        auto jsonStr = UIUtils::getProduct(getHotID());
        rapidjson::Document d;
        d.Parse<0>(jsonStr.c_str());
        if (!d.HasParseError()) {
            if (d.IsObject()) {
                if (d.HasMember("price")) {
                    string price = d["price"].GetString();
                    size_t split = 0, psize = price.size();
                    for (int i=0; i<psize; ++i) {
                        if (isdigit(price.at(i))) {
                            split = i;
                            _price_currency_code = price.substr(0, split);
                            _hotShowStr = price.substr(split, psize-split);
                            break;
                        }
                    }
                }
                if (d.HasMember("description")) {
                    _description = d["description"].GetString();
                }
            }
        }
    }
    return _hotShowStr==""?StringUtils::format("%.2f", _hotMoney):_hotShowStr;
}

// 获取货币价格
std::string Product::getShowStr() {
    if (_showStr == "") {
        auto jsonStr = UIUtils::getProduct(_id);
        rapidjson::Document d;
        d.Parse<0>(jsonStr.c_str());
        if (!d.HasParseError()) {
            if (d.IsObject()) {
                if (d.HasMember("price")) {
                    string price = d["price"].GetString();
                    size_t split = 0, psize = price.size();
                    for (int i=0; i<psize; ++i) {
                        if (isdigit(price.at(i))) {
                            split = i;
                            _price_currency_code = price.substr(0, split);
                            _showStr = price.substr(split, psize-split);
                            break;
                        }
                    }
                }
                if (d.HasMember("description")) {
                    _description = d["description"].GetString();
                }
            }
        }
    }
    return _showStr==""?StringUtils::format("%.2f", _money):_showStr;
}
// 获取货币单位
std::string Product::getCurrencyCode() {
    if (_showStr == "") {
        getShowStr();
    }
    return _price_currency_code;
}

std::shared_ptr<Product> Product::clone()
{
    return std::make_shared<Product>(_id, _money, _price, _ex, _hotMoney, _hotPrice);
}
