
#include "DailyNode.h"
#include "DailyMoreView.h"
#include "SoundManager.h"
#include "EventObserver.h"
void DailyNode::initUI() {
    //BaseLayer::initUI();
    BaseLayer::initUIByRemove(true);

    Image_root = getNode<ImageView*>("Image_root");
    //Image_root->setVisible(false);
    //getNode("Node_cown")->setVisible(false);
    
    updateUI();
}

void DailyNode::initData() {
    BaseLayer::initData();
    setName("DailyNode");
    
    EVENT_M->addListener("msg_daily_node", [this](ValueMap valueMap, void *objP){
        auto obj = static_cast<DailyNode*>(objP);
        //要在这里更新page
        auto data1 = obj->getDate();
        auto data2 = this->getDate();
        auto is = data1 == data2;
        auto tag = obj->getTag();
        setSelected(obj == this||is);
    }, this);
}

void DailyNode::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    if(_tm.Day() == 1)
    {
        btn->getTag();
    }
    auto btnName = btn->getName();
    SOUND_M->playBtnClickAudio();
    if (btnName == "Image_root") {
        auto tag = this->getTag();
        if(tag == 100)
        {//更新page中的node。//事件被拦截
            //auto page = _parentView->getPage();
            //auto itemVec = page->getChildren();
//            for(auto item:itemVec)
//            {
//                auto nodeVec = item->getChildren();
//                for(auto node:nodeVec)
//                {
//                    auto dailyNode = dynamic_cast<DailyNode*>(node);
//                    dailyNode->setSelected(dailyNode == this);
//                }
//            }
        }
        else
        {
            EVENT_M->sendEvent("msg_daily_node", (void*)this);
            //getEventDispatcher()->dispatchCustomEvent("msg_daily_node", (void*)this);
        }

    }
}

DailyNode::DailyNode(DailyMoreView *parentView, Date tm,DailyNode::Type type)
:BaseLayer("2020Daily_Node_0.csb")
,_tm(tm)
,_parentView(parentView)
,_type(type)
{
    _excludeRecord = true; // 不要记录进入
}

DailyNode::~DailyNode() {
    EVENT_M->removeListener("msg_daily_node", this);
}

void DailyNode::setState(DailyNode::State state) {
    _state = state;
    
    updateUI();
}

void DailyNode::updateUI() {
    //刷新的是more 而不是page
    auto text_day = getNode<TextBMFont*>("Text_day");
    auto Text_day_0 = getNode<TextBMFont*>("Text_day_0");
    auto cnt = DailyManager::getInstance()->getCompleteCNT(_tm);
    if(_type == DailyNode::Type::day)
    {
        switch (_state) {
            case State::Completed:
            case State::Open:
                if(_selected)
                {
                    Image_root->loadTexture("daily/Daily_Daily4.png", Widget::TextureResType::PLIST);
                }
                else
                {
                    Image_root->loadTexture(cnt==0?"daily/Daily_Daily3.png":"daily/Daily_Daily5.png", Widget::TextureResType::PLIST);
                }
                if(_selected)
                {//有个先后问题 向后选择日期时先走setSelected()设置字体颜色 在走此函数更改背景 
                    text_day->setColor(Color3B::WHITE);
                }
                else
                {
                    text_day->setColor(Color3B::BLACK);
                }
                //text_day->setColor(Color3B::BLACK);
//              getNode<ImageView*>("Image_root")->loadTexture("daily/Daily_Daily2.png", Widget::TextureResType::PLIST);
                break;
            case State::Closed:
                Image_root->loadTexture("daily/Daily_Daily3.png", Widget::TextureResType::PLIST);
                text_day->setColor(Color3B::GRAY);
                break;
        }
        Image_root->setContentSize(Size(148,163));
        auto flag = cnt>0;  //_state==State::Completed;
        getNode("Node_cown")->setVisible(flag);
        getNode<Sprite*>("Sprite_cown")->setSpriteFrame(StringUtils::format("daily/Challenge_WG%d.png",cnt));//Challenge_WG3.png
        text_day->setVisible(true);
        Text_day_0->setVisible(false);
        text_day->setString(toString(_tm.Day()));
        getNode<Text*>("Text_seven")->setVisible(!flag);
        updateDYY();
        getNode<Text*>("Text_seven")->setColor(Color3B::BLACK);
    }
    else if(_type == DailyNode::Type::month)
    {
        switch (_state) {
            case State::Open:
                Image_root->loadTexture(cnt==0?"daily/Daily_Daily1.png":"daily/Daily_Daily2.png", Widget::TextureResType::PLIST);
                //Text_day_0->setColor(Color3B::BLACK);
                Text_day_0->setColor(Color3B(0,255,126));
//              getNode<ImageView*>("Image_root")->loadTexture("daily/Daily_Daily2.png", Widget::TextureResType::PLIST);
                break;
            case State::Closed:
                Image_root->loadTexture("daily/Daily_Daily3.png", Widget::TextureResType::PLIST);
                Text_day_0->setColor(Color3B::GRAY);
                break;
        }
        Image_root->setContentSize(Size(110,110));
        auto flag = cnt>0;  //_state==State::Completed;
        getNode("Node_cown")->setVisible(flag);
        getNode<Sprite*>("Sprite_cown")->setSpriteFrame(StringUtils::format("daily/Challenge_WG%d.png",cnt));
        text_day->setVisible(false);
        Text_day_0->setVisible(!flag);
        Text_day_0->setPosition(Vec2(110*0.48,110*0.53));
        getNode("Node_cown")->setPosition(Vec2(110*0.50,110*0.50));
        getNode("Node_cown")->setScale(0.91);
        text_day->setString(toString(_tm.Day()));
        Text_day_0->setString(toString(_tm.Day()));
        getNode<Text*>("Text_seven")->setVisible(false);
        
        
        getNode("Daily_Daily4_1")->setPosition(Vec2(110*0.50,110*0.51));
        getNode("Daily_Daily4_1_0")->setPosition(Vec2(110*0.50,110*0.51));
    }
    
    
    Image_root->setTouchEnabled(_state != State::Closed);
    
    if (cnt>0) {
        getNode<Sprite*>("Sprite_cown")->setSpriteFrame(StringUtils::format("daily/Challenge_WG%d.png", MIN(3, cnt)));//无资源
    }
}

void DailyNode::setSelected(bool flag)
{
    
   
    if (_selected != flag)
    {
        _selected = flag;
        if (_state == State::Closed) {
            return;
        }
        
        auto text_day = getNode<TextBMFont*>("Text_day");
        auto Text_day_0 = getNode<TextBMFont*>("Text_day_0");
        auto Text_seven = getNode<Text*>("Text_seven");
        if(_type == DailyNode::Type::day)
        {
            if (flag) {
                Image_root->loadTexture("daily/Daily_Daily4.png", Widget::TextureResType::PLIST);
                
                _parentView->setCurrentSelectNode(this);
                _actionManager->play("loop", true);
                text_day->setColor(Color3B::WHITE);
                Text_seven->setColor(Color3B::WHITE);
            }
            else {
                auto cnt = DailyManager::getInstance()->getCompleteCNT(_tm);
                Image_root->loadTexture(cnt==0?"daily/Daily_Daily3.png":"daily/Daily_Daily5.png", Widget::TextureResType::PLIST);
                _actionManager->gotoFrameAndPause(0);
                text_day->setColor(Color3B::BLACK);
                Text_seven->setColor(Color3B::BLACK);
            }
        }
        else if(_type == DailyNode::Type::month)
        {
            getNode("Daily_Daily4_1")->setVisible(flag);
            getNode("Daily_Daily4_1_0")->setVisible(flag);
            if (flag) {
                
                _parentView->setCurrentSelectNode(this);
                _actionManager->play("loop", true);
                Text_day_0->setColor(Color3B::WHITE);
            }
            else {
                _actionManager->gotoFrameAndPause(0);
//                Text_day_0->setColor(Color3B::BLACK);
                Text_day_0->setColor(Color3B(0,255,126));
            }
        }
        
    }
}

void DailyNode::showWin() {
    _actionManager->play("start", false);
    updateUI();
    _actionManager->setLastFrameCallFunc([this](){
        _actionManager->setLastFrameCallFunc(nullptr);
        _actionManager->play("loop", true);
    });
}

void DailyNode::updateDYY()
{
    auto week = DailyManager::getInstance()->CaculateWeekDay(_tm.Year(), _tm.Month(), _tm.Day());
    string weekday[] = {Lang("100316"),Lang("100310"),Lang("100311"),Lang("100312"),Lang("100313"),Lang("100314"),Lang("100315")};
    getNode<Text*>("Text_seven")->setString(weekday[week]);
}
