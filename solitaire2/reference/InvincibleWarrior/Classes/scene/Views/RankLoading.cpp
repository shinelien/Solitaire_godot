//
// Created by Cyutao on 2021/5/18.
//

#include "RankLoading.h"
#include "DataManager.h"
void RankLoading::initUI() {
    BaseLayer::initUI();
    doLayout();
    FileNode_loading = getNode("FileNode_loading");
    UIUtils::playInnerAction(FileNode_loading,"loop",true);
    
    FileNode_loading->getChildByName<Text*>("Text_1")->setString("L");
    FileNode_loading->getChildByName<Text*>("Text_2")->setString("O");
    FileNode_loading->getChildByName<Text*>("Text_3")->setString("A");
    FileNode_loading->getChildByName<Text*>("Text_4")->setString("D");
    FileNode_loading->getChildByName<Text*>("Text_5")->setString("I");
    FileNode_loading->getChildByName<Text*>("Text_6")->setString("N");
    FileNode_loading->getChildByName<Text*>("Text_7")->setString("G");
    
//    FileNode_loading->getChildByName<Text*>("Text_1")->setFontSize(50);
//    FileNode_loading->getChildByName<Text*>("Text_2")->setFontSize(50);
//    FileNode_loading->getChildByName<Text*>("Text_3")->setFontSize(50);
//    FileNode_loading->getChildByName<Text*>("Text_4")->setFontSize(50);
//    FileNode_loading->getChildByName<Text*>("Text_5")->setFontSize(50);
//    FileNode_loading->getChildByName<Text*>("Text_6")->setFontSize(50);
//    FileNode_loading->getChildByName<Text*>("Text_7")->setFontSize(50);
    auto Text_loading = FileNode_loading->getChildByName<Text*>("Text_8");
    auto fileN = DATA_M->getDyyStr();
    if(fileN == "en")
    {
        Text_loading->setVisible(false);
    }
    else
    {
        Text_loading->setString(Lang("100352"));
    }
    
}

void RankLoading::initData() {
    BaseLayer::initData();
    setName("RankLoading");
    
}

void RankLoading::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
}

RankLoading::RankLoading()
:BaseLayer("2021RankLoading.csb")
{
}

RankLoading::~RankLoading() {

}

void RankLoading::setString(const string &str) {

}
