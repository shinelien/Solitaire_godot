//
//  FanPaiAD.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/8.
//

#ifndef FanPaiAD_h
#define FanPaiAD_h
#include "BaseLayer.h"
#include "Factory.hpp"

class FanPaiAD : public BaseLayer, public Factory<FanPaiAD>
{
public:
    
    enum class Type
    {
        None,
        Home,
        Daily,
        Game,
    };
    
    enum class RewardType
    {
        BigGold,
        SmallGold,
        BigDiamond,
        SmallDiamond,
        GameBg,
        CardBg,
        CardFace,
        Music,
        Magic,
        None,
    };
    
    
    enum class ConsumptionType
    {
        Gold,
        Diamond,
        None,
    };
    
    FanPaiAD(FanPaiAD::Type type = FanPaiAD::Type::None);
    ~FanPaiAD();
    
    void setConsumptionType(ConsumptionType type);
    
    int randGoldNum();
    
    void updateUI();
   
    void updateCoin(bool isDelay = false);
    
    void updateDiamond(bool isDelay = false);
    
    void openGold(int tag,bool isAni);
    void openDiamond(int tag,bool isAni);
    
    void openCardBg(int tag,bool isAni);
    void openCardFace(int tag,bool isAni);
    void openGameBg(int tag,bool isAni);
    
    void openMusic(int tag,bool isAni);
    void openMagic(int tag,bool isAni);
    
    void randReward(int tag,bool isAni);
    
    void updateItemUI(int tag,Node* item,FanPaiAD::RewardType type,int index = -1,int randNum = -1);
    
    void randReward();
    int randRewardTag();
    void onEnter() override;
    void onExit() override;
    
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    bool isTouch;
    Node* FileNode_reward;
    int _rewardNum;
    
    int _coinNum;
    int _diamondNum;
    
    FanPaiAD::Type _type = FanPaiAD::Type::None;
    FanPaiAD::ConsumptionType _consumptionType = FanPaiAD::ConsumptionType::Gold;
    FanPaiAD::RewardType _RewardType[6];// = FanPaiAD::RewardType::None;
    bool isOne;
    
    vector<int> idxVec;
    int _tag;
//    int _goldNum = -1;
//    int _idx = -1;
//    int _randNum = -1;
    int _goldNum[6];//如果金币钻石 记录数目
    int _idx[6];//如果牌 背景 音乐，记录id
    int _randNum[6];//如果是牌面，记录num
    int shopType[6];//记录对应奖励类型
    //翻牌次数
    int fanPaiNum;
    int reward1;
    int reward2;
    vector<int> _randVec;
    std::function<void()> _InterstitialCB = nullptr;
    
    int fangCuo = 10;
    float tempFangCuo;
};

#endif /* FanPaiAD_h */
