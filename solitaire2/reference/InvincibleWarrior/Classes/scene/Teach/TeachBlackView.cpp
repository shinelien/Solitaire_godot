//
// Created by  on 2020/3/22.
//

#include "TeachBlackView.h"
#include "TeachManager.h"

static int Click_CNT = 0;
void TeachBlackView::initUI() {
    BaseLayer::initUI();
    auto blackLayer = Layout::create();
    _blackLayer = blackLayer;
    auto winSize = Director::getInstance()->getWinSize();
    blackLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    blackLayer->setContentSize(winSize*1.1);
    blackLayer->setPosition(winSize/2);
    blackLayer->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    blackLayer->setBackGroundColor(Color3B::BLACK);
    blackLayer->setBackGroundColorOpacity(0);
    this->addChild(blackLayer);
    
    _toptopLayer = Layout::create();
    _toptopLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _toptopLayer->setContentSize(winSize);
    _toptopLayer->setPosition(winSize/2);
    _toptopLayer->setVisible(false);
    this->addChild(_toptopLayer);

    blackLayer->setTouchEnabled(true);
    
    Click_CNT = 0;
    blackLayer->addClickEventListener([this](Ref*){
        if (++Click_CNT>=1000) {   // 容错
            this->removeFromParent();
            TEACH_M->endTeach("");
        }
    });
}

void TeachBlackView::initData() {
    BaseLayer::initData();
    setName("TeachBlackView");
}

void TeachBlackView::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
}

TeachBlackView::TeachBlackView()
:BaseLayer("")
{
}

TeachBlackView::~TeachBlackView() {

}

void TeachBlackView::onEnter() {
    BaseLayer::onEnter();
}

void highlightNodeAll(Node *node, int order)
{
    node->setGlobalZOrder(order);
    for (auto child : node->getChildren()) {
        highlightNodeAll(child, order);
    }
}

void TeachBlackView::onExit() {
    BaseLayer::onExit();
    if (this->_highlightNode) {
        highlightNodeAll(_highlightNode, 0);
    }
    if (_underNode!=nullptr) {
        _underNode->setVisible(false);
        _underNode->release();
    }
}

void TeachBlackView::highlightNode(Node *node, bool hasFinger, cocos2d::Vec2 offsetFinger, bool lock, bool once, bool underNode) {
    _blackLayer->setTouchEnabled(lock);
    this->_highlightNode = node;
    if (underNode && node) {
        _underNode = node;
        _underNode->retain();
        _underNode->setVisible(true);
    }
    if (lock && node) {
        _blackLayer->setBackGroundColorOpacity(255*0.4);
        highlightNodeAll(_highlightNode, 1);
    }
    if (hasFinger && node) {
        scheduleOnce([this, offsetFinger, once](float t){
            auto finger = UIUtils::createCSBNode("Animation/Node_finger.csb", "Start0", true);
            auto worldP = _highlightNode->convertToWorldSpaceAR(Vec2::ZERO);
            auto localP = this->convertToNodeSpace(worldP);
            this->addChild(finger);
//            auto layerC = LayerColor::create(Color4B::RED, 500, 50);
//            layerC->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//            layerC->setPosition(localP);
//            layerC->setGlobalZOrder(2);
//            this->addChild(layerC);
            
            finger->setName("Teach_finger");
            finger->setPosition(localP+offsetFinger);
            highlightNodeAll(finger, 1);
            if (once) {
                auto listener = EventListenerTouchOneByOne::create();
                listener->setSwallowTouches(true);
                listener->onTouchBegan = [this](Touch *t, Event *e) -> bool {
                    _toptopLayer->removeFromParent();
                    this->removeChildByName("Teach_finger"); // 删除手指头
                    return false;
                };
                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _toptopLayer);
                _toptopLayer->setGlobalZOrder(2);
                _toptopLayer->setVisible(true);
            }
        }, 0.0001f, "schedule_teach_finger_key");
    }
}

void TeachBlackView::fingerOnce(Node *node, cocos2d::Vec2 offsetFinger, bool end) {
    _blackLayer->setTouchEnabled(false);
    this->_highlightNode = node;
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this, end](Touch *t, Event *e) -> bool {
        this->removeFromParent();
        if (end) {
            TEACH_M->endTeach("");
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    scheduleOnce([this, offsetFinger](float t){
        auto finger = UIUtils::createCSBNode("Animation/Node_finger.csb", "Start0", true);
        auto worldP = _highlightNode->convertToWorldSpaceAR(Vec2::ZERO);
        auto localP = this->convertToNodeSpace(worldP);
        this->addChild(finger);
        finger->setPosition(localP+offsetFinger);
        highlightNodeAll(finger, 1);
//        this->runAction(Sequence::create(DelayTime::create(5), RemoveSelf::create(), NULL));
    }, 0.0001f, "schedule_teach_finger_key");
}
