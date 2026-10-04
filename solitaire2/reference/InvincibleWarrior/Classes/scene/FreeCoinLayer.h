# ifndef __FREECOIN_LAYER__
# define __FREECOIN_LAYER__

# include "BaseLayer.h"
# include "DataManager.h"
# include "SoundManager.h"
#include "Factory.hpp"
class FreeCoinLayer : public BaseLayer , public Factory<FreeCoinLayer>
{
public:
    enum class Type
    {
        Gold,
        Diamond,
    };
	//CREATE_FUNC(FreeCoinLayer);
    FreeCoinLayer(FreeCoinLayer::Type type,BaseLayer* layer = NULL);

	static Scene * createScene();
	static FreeCoinLayer * createLayer();
	virtual void initUI() override;
	virtual bool init() override;
	
	void initData() override; //初始化数据

	void dealButtonClick(Ref * pSender) override;// , ui::TouchEventType teType);
	void dealButtonTouch(Ref * pSender,Widget::TouchEventType touchType);
	virtual bool onTouchBegan(Touch * t, Event * e) override;
	virtual void onTouchMoved(Touch * t, Event * e) override;
	virtual void onTouchEnded(Touch * t, Event * e) override;

    
    void onEnter() override;
    void onExit() override;
private:
	Node * panel_freecoin,*FileNode_1;

	Button * btn_guankan;
	Text * text_guankan;

	bool isCanSeeAds;
    FreeCoinLayer::Type _type;
    //领取次数
    int freeCoinNum;
    
    BaseLayer* _layer;
};

# endif
