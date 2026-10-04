//
//  GrowupNode.hpp
//  SpacecatSolitaireGame-mobile
//
//  Created by Cyutao on 2018/11/18.
//

#ifndef GrowupNode_hpp
#define GrowupNode_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GrowupNode : public cocos2d::Node {
public:
    GrowupNode();
    CREATE_FUNC(GrowupNode);
    
    void startGrouwup(cocos2d::ui::TextBMFont *label, int startNum, int endNum, float time,std::string str, std::function<void()> callFunc = nullptr);
    void startGrouwup(cocos2d::ui::Text *label, int startNum, int endNum, float time, std::function<void()> callFunc = nullptr);
    
    
    void unTextSchedule();
private:
    float _currentNum=0;
    std::function<void()> _cb = nullptr;
    cocos2d::ui::TextBMFont *labelBMF = nullptr;
    cocos2d::ui::Text *labelText = nullptr;
};

#endif /* GrowupNode_hpp */
