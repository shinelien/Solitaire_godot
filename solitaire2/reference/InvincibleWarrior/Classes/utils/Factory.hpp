//
//  Factory.hpp
//  SpacecatSolitaireGame
//
//  Created by Cyutao on 2018/8/27.
//

#ifndef Factory_hpp
#define Factory_hpp

#include <stdio.h>

template <typename T>
class Factory {
public:
    template <typename...Args>
    static T* createLayerN(Args&&... args) {
        auto *ret = new (std::nothrow) T(std::forward<Args>(args)...);
        if (ret && ret->init())
        {
            ret->autorelease();
            return ret;
        }
        else
        {
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
    }
};

#endif /* Factory_hpp */
