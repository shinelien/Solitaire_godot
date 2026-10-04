# ifndef __RULE_LAYER__
# define __RULE_LAYER__

# include "BaseLayer.h"
# include "DataManager.h"
# include "SoundManager.h"

class RuleLayer : public BaseLayer
{
public:

    RuleLayer(BaseLayer* layer);
    ~RuleLayer();
	static Scene * createScene();
	static RuleLayer * createLayer(BaseLayer* layer);
	virtual void initUI();
	virtual bool init();
    void initData();
	void dealButtonClick(Ref * pSender);// , ui::TouchEventType teType);

private:
    BaseLayer* _layer;
};

# endif
