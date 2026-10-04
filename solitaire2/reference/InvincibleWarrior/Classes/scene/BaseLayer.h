/*
	界面基类
	author:codehua
*/

# ifndef __BASELAYER__
# define __BASELAYER__

# include "cocos2d.h"
# include "UIUtils.h"
#include <unordered_map>

USING_NS_CC;
USING_NS_TIMELINE;

class BaseLayer : public Widget
{
public:
	static Scene * createScene();
	static BaseLayer * createLayer();
	BaseLayer(const string &csbName = "");
	~BaseLayer();
	virtual bool init();
	void initUIByRemove(bool removeAllChildren = false);
	virtual void initUI();
	virtual void initData();
	virtual bool onTouchBegan(Touch * t,Event * e);
	virtual void onTouchMoved(Touch * t,Event * e);
	virtual void onTouchEnded(Touch * t,Event * e);
	virtual void refush();//刷新界面
	virtual void dealButtonClick(Ref * pSender) {};
    void doLayout();
    void playAni(const std::string &aniName, bool loop = false, std::function<void()> cb = nullptr);
    void addEvent(const std::string &key, const std::function<void(EventCustom*)> &func, bool add = false);
    void removeEvent(const std::string &key);

	virtual void showBlackLayer();//显示黑色的幕
	cocos2d::Size vSize;
    
    template <typename T>
    inline T getNode(const std::string &name) {
        auto it = _nodes.find(name);
        if (it != _nodes.end())
            return dynamic_cast<T>(it->second);
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        return nullptr;
#else
		return nullptr;
#endif
    }
    
    inline Node* getNode(const std::string &name) {
        auto it = _nodes.find(name);
        if (it != _nodes.end())
            return it->second;
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        return nullptr;
#else
        return _errorNode;
#endif
    }

	void onEnter() override;
    
	void onExit() override;

    void onRecordEnter(const std::string v1="", const std::string v2="", const std::string v3="");
    void onRecordExit(const std::string v1="", const std::string v2="", const std::string v3="");
protected:
	std::string _csbName;
	std::unordered_map<std::string, cocos2d::Node*> _nodes;
	std::unordered_map<std::string, std::function<void(EventCustom*)>> _eventFunc;
	cocos2d::Node *_rootNode, *_errorNode = nullptr;
	ActionTimeline *_actionManager = nullptr;
    long _enterTime = 0;
    bool _excludeRecord = false;
};


# endif
