# ifndef __COUNT_LAYER__
# define __COUNT_LAYER__

# include "BaseLayer.h"
# include "DataManager.h"
# include "SoundManager.h"

class CountLayer : public BaseLayer
{
public:

	CREATE_FUNC(CountLayer);

	CountLayer();

	static Scene * createScene();
	static CountLayer * createLayer();
	virtual void initUI();
	virtual bool init();
	
	void initData(); //初始化数据

	void dealButtonClick(Ref * pSender);// , ui::TouchEventType teType);
	void dealButtonTouch(Ref * pSender,Widget::TouchEventType touchType);
    
    void onExit() override;

private:
	Node * panel_count;

	Node * panel_num_1, *panel_num_2;

};

# endif
