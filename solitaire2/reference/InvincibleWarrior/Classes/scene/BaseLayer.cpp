#include "BaseLayer.h"
#include "BaseLayer.h"
#include "DataManager.h"

BaseLayer::BaseLayer(const string &csbName):
_csbName(csbName)
{

}

BaseLayer::~BaseLayer()
{
	
}

void BaseLayer::initUI()
{
	return initUIByRemove(false);
}

void BaseLayer::initUIByRemove(bool removeAllChildren)
{
    if (_csbName != "") {
        if (UIUtils::IsPad()) {
            auto padCSBName = "pad/" + _csbName;
            padCSBName.replace(padCSBName.size()-4, 4, "_pad.csb");
            if (FileUtils::getInstance()->isFileExist(padCSBName))
                _csbName = padCSBName;
        }
        CCLOG("NewLayer name:%s", _csbName.c_str());
        _rootNode = CSLoader::createNode(_csbName, [this](Ref *ref){
            auto node = static_cast<Node*>(ref);
            _nodes[node->getName()] = node;
            auto widget = dynamic_cast<Widget*>(ref);
            if (widget && widget->isEnabled())
			{
				widget->addClickEventListener(CC_CALLBACK_1(BaseLayer::dealButtonClick,this));
			}
        });
        _actionManager = ActionTimelineCache::createAction(_csbName);

        setContentSize(_rootNode->getContentSize());
        if (removeAllChildren) {
            auto widget = Widget::create();
            widget->setContentSize(_rootNode->getContentSize());
            auto &children = _rootNode->getChildren();
            Vector<Node*> removedChildren;
            for (auto it = children.rbegin();it!=children.rend();++it) {
                auto child = *it;
                removedChildren.pushBack(child);
                child->removeFromParentAndCleanup(false);
            }
            
            for (auto it = removedChildren.rbegin();it!=removedChildren.rend();++it) {
                auto child = *it;
				this->addChild(child, child->getLocalZOrder(), child->getTag());
            }
            _rootNode = this;
        }
        else {
            addChild(_rootNode);
        }
        _rootNode->runAction(_actionManager);
        _actionManager->setTag(10086);
    }
    
    // 错误的node 不应该被获取到
    _errorNode = Node::create();
    this->addChild(_errorNode);
    _errorNode->setPosition(Vec2(-2000, -2000));
}

void BaseLayer::doLayout()
{
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    _rootNode->setPosition(safeArea.origin);
    _rootNode->setContentSize(safeArea.size);
    setContentSize(_rootNode->getContentSize());
    ui::Helper::doLayout(_rootNode);
}

void BaseLayer::initData()
{

}

bool BaseLayer::init()
{
	if (!Widget::init())
	{
		return false;
	}
    setAnchorPoint(Vec2::ZERO);
	vSize = Director::getInstance()->getVisibleSize();
//    setPosition(vSize/2);
	this->initData();
	this->initUI();


	//设置一些参数
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BaseLayer::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(BaseLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseLayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(BaseLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
	return true;
}

Scene * BaseLayer::createScene()
{
	//auto scene = Scene::create();
	//scene->addChild(BaseLayer::create());
	//return scene;
	return UIUtils::createScene(BaseLayer::create());
}

BaseLayer * BaseLayer::createLayer()
{
	auto baseLayer = new BaseLayer();
	baseLayer->init();
	baseLayer->setName("BaseLayer");
	baseLayer->autorelease();
	return baseLayer;
}

bool BaseLayer::onTouchBegan(Touch * t, Event * e)
{
	return true;
}

void BaseLayer::onTouchMoved(Touch * t,Event * e)
{

}

void BaseLayer::onTouchEnded(Touch * t,Event * e)
{

}

//刷新界面
void BaseLayer::refush()
{

}

//显示黑色的幕
void BaseLayer::showBlackLayer()
{
	auto layer = Layout::create();
	layer->setContentSize(Size(480,800));
	layer->setTouchEnabled(true);

	auto blackLayer = LayerColor::create(Color4B::BLACK);
	layer->addChild(blackLayer);
	this->addChild(layer);
	blackLayer->runAction(Sequence::create(FadeOut::create(0.5), CallFunc::create([layer]{
		layer->removeFromParentAndCleanup(true);
	}), NULL));
}

void BaseLayer::playAni(const std::string &aniName, bool loop, std::function<void()> cb) {
	if (_actionManager) {
        _actionManager->setLastFrameCallFunc(cb);
		_actionManager->play(aniName, loop);
	}
}

void BaseLayer::onEnter() {
	Widget::onEnter();
	for (auto &item:_eventFunc) {
		getEventDispatcher()->addCustomEventListener(item.first, item.second);
	}
    if (!_excludeRecord) {
        onRecordEnter();
    }
}

void BaseLayer::onExit() {
	Widget::onExit();
	for (auto &item:_eventFunc) {
		getEventDispatcher()->removeCustomEventListeners(item.first);
	}
    if (!_excludeRecord) {
        onRecordExit();
    }
}

void BaseLayer::addEvent(const std::string &key, const std::function<void(EventCustom*)> &func, bool add) {
	_eventFunc[key] = func;
    if (add)
        getEventDispatcher()->addCustomEventListener(key, func);
}

void BaseLayer::removeEvent(const std::string &key) {
	auto it = _eventFunc.find(key);
	if (it != _eventFunc.end()) {
		getEventDispatcher()->removeCustomEventListeners(it->first);
		_eventFunc.erase(it);
	}
}

void BaseLayer::onRecordEnter(const std::string v1, const std::string v2, const std::string v3)
{
    if (_name != "" && _name != "BaseLayer" && DATA_M->recordLayerData())
    {
        CCLOG("BaseLayer onEnter:%s", _name.c_str());
        _enterTime = DATA_M->getContentSec();
        ValueMap valueMap{
            {"key", Value("EnterLayer")},
            {"value", Value(getName())},
        };
        if (v1 != "") valueMap["v1"] = Value(v1);
        if (v2 != "") valueMap["v2"] = Value(v2);
        if (v3 != "") valueMap["v3"] = Value(v3);
        UIUtils::FIRFirestoreAdd("operator", valueMap);
        UIUtils::FIRAnalyticsEvent("EnterLayer", valueMap);
    }
}

void BaseLayer::onRecordExit(const std::string v1, const std::string v2, const std::string v3)
{
    if (_name != "" && _name != "BaseLayer" && DATA_M->recordLayerData())
    {
        CCLOG("BaseLayer onExit:%s", _name.c_str());
        ValueMap valueMap{
            {"key", Value("ExitLayer")},
            {"value", Value(getName())},
        };
        if (v1 != "") valueMap["v1"] = Value(v1);
        if (v2 != "") valueMap["v2"] = Value(v2);
        if (v3 != "") valueMap["v3"] = Value(v3);
        _enterTime = DATA_M->getContentSec() -_enterTime;
        valueMap["v4"] = Value(toString(_enterTime)); // 记录停留时间
        UIUtils::FIRFirestoreAdd("operator", valueMap);
        UIUtils::FIRAnalyticsEvent("ExitLayer", valueMap);
    }
}
