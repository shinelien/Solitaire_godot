
#include "FeedBackView.h"
#include "MainLobby.h"
#include "SceneManager.h"
void FeedBackView::initUI() {
    BaseLayer::initUI();
    doLayout();
    //剧中
    //this->setPosition(getContentSize()*0.5f);
    
    /*
     "100317" : "满意度",
     "100318" : "意见反馈",
     "100319" : "提交",
     "100320" : "欢迎给我们提上宝贵的建议"
     */
    getNode<Text*>("Text_10")->setString(Lang("100317"));
    getNode<Text*>("Text_10_0")->setString(Lang("100320"));
    getNode<Text*>("Text_feedback")->setString(Lang("100318"));
    getNode<Text*>("Text_go")->setString(Lang("100319"));
    
}

void FeedBackView::initData() {
    BaseLayer::initData();
    setName("FeedBackView");
}

void FeedBackView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();

    if (btnName == "Button_go") {
        UIUtils::writComment();
        this->removeFromParent();
    }
    else if (btnName == "Button_feedback") {
        UIUtils::openMail();
        this->removeFromParent();
    }
    else if(btnName == "Panel_star")
    {
        auto tag = btn->getTag();
        updataUI(tag);
    }
    else if(btnName == "Panel_1"||btnName == "Button_close")
    {
        this->removeFromParent();
    }

    if (btnName != "Button_close"&&btnName != "Panel_1") {
        UserDefault::getInstance()->getBoolForKey("feedback_flag", true);
        UserDefault::getInstance()->flush();
    }
    
    
}

FeedBackView::FeedBackView()
:BaseLayer("Feedback.csb")
{
}

FeedBackView::~FeedBackView() {

}

void FeedBackView::updataUI(int id)
{
    for(int i = 1;i < 6;++i)
    {
        auto star = getNode(StringUtils::format("win_star0_%d",i));
        if(i<=id)
        {
            star->setOpacity(255);
        }
        else
        {
            star->setOpacity(0);
        }
    }
}

void FeedBackView::onExit()
{
    BaseLayer::onExit();
}
