//
// Created by  on 2019-06-03.
//

#ifndef NewSpaceCatSolitaire_BackView_H
#define NewSpaceCatSolitaire_BackView_H

#include "BaseLayer.h"
#include "Factory.hpp"

using BackCB = std::function<void()>;
class BackView : public BaseLayer, public Factory<BackView> {
public:
    virtual ~BackView();
    BackView(BackCB yesCB, BackCB noCB, const std::string title = "", const std::string yes = "YES", const std::string no = "NO");

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    BackCB _yesCB, _noCB;
    std::string _title, _yes, _no;
};

#endif //NewSpaceCatSolitaire_BackView_H
