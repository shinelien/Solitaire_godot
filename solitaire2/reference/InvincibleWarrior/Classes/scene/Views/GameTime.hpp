//
//  GameTime.hpp
//  SpacecatSolitaireGame-mobile
//
//  Created by Cyutao on 2018/8/27.
//

#ifndef GameTime_hpp
#define GameTime_hpp

#include <vector>
#include "Factory.hpp"
#include "BaseLayer.h"

enum TimeType {
    Hour1,
    Fen1,
    Fen2,
    Miao1,
    Miao2,
    End
};
class GameTime:public BaseLayer, public Factory<GameTime> {
public:
    GameTime();
    void setTime(time_t time);
    
    void initData() override;
    void initUI() override;
private:
    time_t _time;
    std::vector<int> _timeVec;
    std::vector<Node*> _nodeVec;

    void setTimeAni(int value, TimeType t);
};

#endif /* GameTime_hpp */
