//
// Created by  on 2019-07-13.
//

#ifndef SolitaireClassicGame_RewardRouletteView_H
#define SolitaireClassicGame_RewardRouletteView_H

#include "BaseLayer.h"
#include "Factory.hpp"
class GameViewHD;
class RewardRouletteView : public BaseLayer, public Factory<RewardRouletteView> {
public:
    
    enum class Type
    {
        None,
        Home,
        Daily,
        Game,
    };
    virtual ~RewardRouletteView();
    RewardRouletteView(RewardRouletteView::Type type);
    void startRoulette(bool free = true);
    void showReward(int idx);
    
    void onEnter() override;
    void onExit() override;
    
    void update(float t) override;
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    void setIsAD(bool is);
    bool _freeGet = false;
    bool isAD;//免费与广告按钮切换
    TextBMFont *Text_time;
    Button *Button_adget, *Button_get;
    float _lastOffset = 0, _rotating = false;
    RewardRouletteView::Type _type;
    GameViewHD* _gameView = nullptr;
    int lunPanNum;
    float totalRotetime;
    vector<int> idxVec;
    bool isClickAds;
};

#endif //SolitaireClassicGame_RewardRouletteView_H
