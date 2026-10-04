
#include "TipsNode.h"

void TipsNode::initUI() {
    BaseLayer::initUI();
    Particle_2 = getNode<ParticleSystemQuad*>("Particle_2");
    
    _actionManager->setFrameEventCallFunc([this](Frame* frame) {
        auto eventName = static_cast<EventFrame*>(frame)->getEvent();
        if (eventName == "event_quad") {
            Particle_2->resetSystem();
        }
    });
}

void TipsNode::initData() {
    BaseLayer::initData();
    setName("TipsNode");
}

void TipsNode::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
}

TipsNode::TipsNode()
:BaseLayer("card/tips.csb")
{
    _excludeRecord = true; // 不要记录进入
}

TipsNode::~TipsNode() {

}
