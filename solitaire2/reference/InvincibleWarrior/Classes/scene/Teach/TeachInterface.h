//
// Created by  on 2020/3/23.
//

#ifndef NewSpaceCatSolitaire_TeachInterface_H
#define NewSpaceCatSolitaire_TeachInterface_H

#include "cocos2d.h"

class TeachInterface {
public:
    virtual cocos2d::Node* getTeachItem(const std::string &name, int idx) = 0;
};

#endif //NewSpaceCatSolitaire_TeachInterface_H
