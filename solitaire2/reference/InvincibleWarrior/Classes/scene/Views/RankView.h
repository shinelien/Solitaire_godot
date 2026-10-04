//
//  RankView.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/5/11.
//

#ifndef RankView_h
#define RankView_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "TeachInterface.h"

class BagGameBg;
class MainLobby;
class RankItem;
class RankView : public BaseLayer, public Factory<RankView>
{
public:
   
    enum class RankType
    {
        GameView,
        WinLayer,
        Lobby,
    };
    RankView(RankType type);
    ~RankView();
    void onEnter() override;
    void onExit() override;
    
    //void refush(bool isRefushAll);
    int getTotalCNT();
    void showSelect(int shopType, int shopIndex, const string name);
    void updateUI();
    void updateName();
    Layout* getPanelView();
    RankType getRankType() { return _type; }
    
    
    vector<int> getFishVec() { return _fishVec; }
    vector<bool> getIsDailyVec() { return _isDailyVec; }
    std::vector<bool> getIsFashTankUnlockVec() const { return _isFashTankUnlockVec; }
    int getLevel() { return _lv; }
    int getScore() { return _score; }
    string getUserName() { return _name; }
    string getCy() { return _cy; }
    string getUserKey() { return _key; }
    int getFashTankId() { return _fashTankId; }
    
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    int startIDX,_loadingNum;
    rapidjson::Value rankArr;
    RankType _type;
    ScrollView* _scrollView;
    
    
    int _idx, _fashTankId, _lv, _score,_myRank;
    string _name, _cy, _key;
    vector<int> _fishVec;
    vector<bool> _isDailyVec;
    vector<bool> _isFashTankUnlockVec;
    
    TextField* TextField_name;
    string oldStr;
    
    Node* Panel_setName;
    RankItem* _myRankItem;
    int _rankPrice;
    Node* timeParent;
};

#endif /* RankView_h */
