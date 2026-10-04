//
//  GameRewardsView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/3/4.
//

#ifndef GameRewardsView_h
#define GameRewardsView_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include "ScoreManager.h"
#include <spine/AnimationState.h>
namespace spine {
    class SkeletonAnimation;
}
class GameRewardsView : public BaseLayer, public Factory<GameRewardsView>
{
public:
    enum class Type
    {
        First,//首胜
        Win,//连胜
        MaxScore,//历史最高分
        DayScore,//今日最高分
    };
    
    GameRewardsView();
    ~GameRewardsView();
    void updateUI(int score,int exp,std::function<void()> cb);
    void setScore(int gameType,bool isWin,int score);
    void hideUI();
    void updateData();
    void initDayData();
    void initDayWin();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    std::vector<score_t> oneCardScores;
    std::vector<score_t> threeCardScores;
    bool isThree;
    TextBMFont* BitmapFontLabel_1;
    //上一场分数
    int oneOldScore;
    int threeOldScore;
    Node* Panel_zh,*Panel_tw,*Panel_en,*Panel_ja,*Panel_ko,*Panel_level;
    int _yday;
    spine::SkeletonAnimation *_fishWinSkeletonNode;
};

#endif /* GameRewardsView_h */
