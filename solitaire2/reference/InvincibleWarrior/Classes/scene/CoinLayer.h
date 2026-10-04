# ifndef __COIN_LAYER__
# define __COIN_LAYER__

# include "BaseLayer.h"
# include "DataManager.h"
# include "SoundManager.h"
# include "FreeCoinLayer.h"
class CoinLayer : public BaseLayer
{
public:

	CREATE_FUNC(CoinLayer);

	static Scene * createScene();
	static CoinLayer * createLayer();
	virtual void initUI();
	virtual bool init();
	virtual void update(float dt);
	void initData(); //初始化数据

	void dealButtonClick(Ref * pSender);// , ui::TouchEventType teType);


	void setCanSeeAds(bool isCanSeeAds);
	void setIsHaveFree(bool isHaveFree);
private:
	Node * panel_coin;

	Button * btn_ads, *btn_freecoin;
	Text * text_free, *text_ads;
	TextAtlas * atlasLabel_time;

	bool isHaveFree;
	bool isCanSeeAds;
};

# endif