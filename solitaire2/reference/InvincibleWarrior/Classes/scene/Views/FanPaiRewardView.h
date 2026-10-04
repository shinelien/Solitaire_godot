//
//  FanPaiRewardView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/29.
//

#ifndef FanPaiRewardView_h
#define FanPaiRewardView_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "TeachInterface.h"

class FanPaiRewardView : public BaseLayer, public Factory<FanPaiRewardView>, public TeachInterface
{
public:
    
    enum class Type
    {
        None,
        Home,
        Daily,
        SevenGold,
        SevenDiamond,
    };
    
    enum class RewardType
    {
        None,
        BigGold,
        SmallGold,
        BigDiamond,
        SmallDiamond,
        GameBg,
        CardBg,
        CardFace,
        Music,
        Magic,
    };
    
    
    enum class ConsumptionType
    {
        Gold,
        Diamond,
        None,
    };
    
    FanPaiRewardView(int rewardNum,FanPaiRewardView::Type type = FanPaiRewardView::Type::None);
    ~FanPaiRewardView();
    
    void setConsumptionType(ConsumptionType type);
    void setType(FanPaiRewardView::Type type);
    void setRewardNum(int num);
    int randGoldNum();
    
    void updateUI();
   
    void updateCoin(bool isDelay = false);
    
    void updateDiamond(bool isDelay = false);
    
    void openGold(int tag);
    void openDiamond(int tag);
    
    void openCardBg(int tag);
    void openCardFace(int tag);
    void openGameBg(int tag, int teachUnlockIdx = -1);
    void openMusic(int tag);
    void openMagic(int tag);
    
    void openCardBgAni(int tag);    // 只是播放动画
    void openCardFaceAni(int tag);  // 只是播放动画
    void openGameBgAni(int tag);    // 只是播放动画
    void openMusicAni(int tag);     // 只是播放动画
    void openMagicAni(int tag);     // 只是播放动画
    
    void randReward(int tag);
    void randDaily(int tag);
    void randHome(int tag);
    void randGold1(int tag);//1阶段
    void randGold2(int tag);//2阶段
    void randGold3(int tag);//3阶段
    void randDiamond1(int tag);//1阶段
    void randDiamond2(int tag);//2阶段
    void randDiamond3(int tag);//3阶段
    void showCompletedBtn();
    void hideOpenBtn();
    
    void updateItemUI(int tag,Node* item,FanPaiRewardView::RewardType type,int index = -1,int randNum = -1);
    
    
    
    void onEnter() override;
    void onExit() override;
    
    Node* getTeachItem(const std::string &name, int idx) override;
    
    void startFanPai();
    void addIdxVec(int idx);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    bool isTouch;
    Node* FileNode_reward;
    int _rewardNum;
    int _openNum;
    int _rewardTempNum;
    
    int _coinNum;
    int _diamondNum;
    
    FanPaiRewardView::Type _type = FanPaiRewardView::Type::None;
    ConsumptionType _consumptionType = ConsumptionType::Gold;
    
    
    vector<int> idxVec;
    int _tag;
    int _goldNum[6];
    int _itemIdx[6];
    FanPaiRewardView::RewardType _rewardType[6];
    //是否抽到了道具
    bool isPorp = false;
    bool isPorp2 = false;
    int prop = 0;
    //
    bool isGold = false;
    bool isDiamond = false;
    //      记录当前星星宝箱上限
    int crownMax;
    int starMax;
    
    
    bool isChongFu;
    vector<int> _randVec;
    vector<int> _randBoxVec;
    
    int fangCuo = 10;
    float tempFangCuo = 0;
    unordered_map<int, std::function<void(int)>> _rewardFuncMap;
    ValueVector _rewardVec;
    
    //记录5连抽次数，不分金币箱与钻石箱
    int fivePumpNum, teachBGGetCNT/*新手*/;
    bool isThreeReward;//第三次之后抽钻石给音乐
    //随机分配卡牌
    int randFiveTagNum;
    //依次打开id容器
    vector<int> _openIdVec;
};

#endif /* FanPaiRewardView_h */
