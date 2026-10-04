//
//  LikemeView.cpp
//  NewSpaceCatSolitaire-mobile
//
//  Created by lien on 2020/3/24.
//

#include <stdio.h>
#include "LikemeView.h"
#include "SceneManager.h"

LikemeView::LikemeView()
:BaseLayer("Likeme.csb")
{
    
}
LikemeView::~LikemeView()
{
    
}
    
void LikemeView::initUI()
{
    BaseLayer::initUI();
    doLayout();
    playAni("Start",false,[this](){
        playAni("loop",true);
        UIUtils::removeLastFrameFunc(this);
    });
    
    
    
    getNode<Text*>("Text_title")->setString(Lang("100264"));
    getNode<Text*>("Text_yes")->setString(Lang("100162"));
}
void LikemeView::initData()
{
    BaseLayer::initData();
    
    
    
}
void LikemeView::dealButtonClick(Ref *pSender)
{
    auto btn = dynamic_cast<Widget*>(pSender);
    if(!btn)return;
    
    auto btnName = btn->getName();
    
    if(btnName == "Button_close")
    {//
        SCENE_M->removeLayer(this);
    }
    else if(btnName == "Button_yes")
    {//
        UIUtils::writComment();
        UserDefault::getInstance()->getBoolForKey("feedback_flag", true);
        UserDefault::getInstance()->flush();
        SCENE_M->removeLayer(this);
    }
}
