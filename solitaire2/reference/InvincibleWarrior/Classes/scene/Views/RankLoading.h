//
// Created by Cyutao on 2021/5/18.
//

#ifndef NewSpaceCatSolitaire_2021RankLoading_H
#define NewSpaceCatSolitaire_2021RankLoading_H

#include "BaseLayer.h"
#include "Factory.hpp"

class RankLoading : public BaseLayer, public Factory<RankLoading> {
public:
    virtual ~RankLoading();
    RankLoading();

    void setString(const std::string &str);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    Node* FileNode_loading;
};

#endif //NewSpaceCatSolitaire_2021RankLoading_H
