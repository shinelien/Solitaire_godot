//
//  RankManager.hpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by Cyutao on 2021/5/17.
//

#ifndef RankManager_hpp
#define RankManager_hpp

#include <stdio.h>
#include <string>
#include <external/json/document.h>
#include <vector>
#include "cocos2d.h"
#include "UIUtils.h"

class RankModel {
public:
    std::string getName() const;

    void setName(const std::string &name);

    int getP1() const;

    void setP1(int p1);

    int getP2() const;

    void setP2(int p2);
    
    int getLv() const { return _lv; }
    
    const std::string &getKey() const { return _key; }
    
    const std::string &getCy() const { return _cy; }
    
    std::vector<int> getFishVec() const { return _fishVec; }
    std::vector<bool> getIsDailyVec() const { return _isDailyVec; }
    std::vector<bool> getIsFashTankUnlockVec() const { return _isFashTankUnlockVec; }
    int getFishTankIdx() const { return _fishTankIdx; };

    RankModel(const std::string &name, int p1, int p2);
    RankModel(rapidjson::Value &Value);
    RankModel(ValueMap &valueMap);
private:
    std::string _name, _key, _cy = "US";
    std::vector<int> _fishVec;
    std::vector<bool> _isDailyVec;
    std::vector<bool> _isFashTankUnlockVec;
    int _p1 = 0, _p2 = 0, _fishTankIdx = 0, _lv = 1;
public:
    void setKey(const string &key);

    void setCy(const string &cy);

    void setFishVec(const vector<int> &fishVec);

    void setIsDailyVec(const vector<bool> &isDailyVec);

    void setIsFashTankUnlockVec(const vector<bool> &isFashTankUnlockVec);

    void setFishTankIdx(int fishTankIdx);

    void setLv(int lv);
};

class Product {
public:
    Product(std::string id, float money, int price, float ex, float hotMoney, float hotPrice);
    
    bool isHot() { return _hot; }
    void setHot(bool flag) { _hot = flag; }
    bool isHotBuy() { return GETINTEGER(getHotID().c_str(), 0) == 1; }
    void setIsHotBuy()  { SETINTEGER(getHotID().c_str(), 1); }
    const std::string getHotID() const { return "hot_" + _id; }
    const std::string getID() const { return _id; }
    const int getHotPrice() const { return _hotPrice; }
    const int getPrice() const { return _price; }
    const float getHotMoney() const { return _hotMoney; }
    const float getMoney() const { return _money; }
    std::string getShowStr(); // 获取货币价格
    std::string getHotShowStr();
    std::string getCurrencyCode(); // 获取货币单位
    std::shared_ptr<Product> clone();
private:
    std::string _id, _showStr = "", _description = "", _price_currency_code = "$", _hotShowStr = "";
    int _price;
    float _money, _ex, _hotMoney, _hotPrice;
    bool _hot = false;
};

class RankManager {
public:
    static RankManager* getInstance();

    const std::vector<RankModel>& getRankList() const;
    void setRankList(const std::string &str);
    void setRankList(const ValueVector valueVec);
    const std::vector<std::shared_ptr<Product>>& getProducts() const { return _productsOrders; };
    std::shared_ptr<Product> getProduct(const std::string &id);
    std::shared_ptr<Product> getSubProduct(const std::string &id);
    void updateProducts();
private:
    static RankManager* s_instance;
    RankManager() { init(); }
    void init();
    std::vector<RankModel> _rankList;
    rapidjson::Document _rankConfig;
    
    // iap 相关
    std::vector<std::shared_ptr<Product>> _productsOrders;
    std::unordered_map<std::string, std::shared_ptr<Product>> _subProductsOrders; // 订阅
};

#endif /* RankManager_hpp */
