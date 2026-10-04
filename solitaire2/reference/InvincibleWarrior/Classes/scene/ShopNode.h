/*
	author:codehua
*/
# ifndef __SHOP_NODE__
# define __SHOP_NODE__

# include "cocos2d.h"
# include "UIUtils.h"
# include "DataManager.h"
# include "SoundManager.h"

USING_NS_CC;

class ShopNode : public Widget
{
public:
	CREATE_FUNC(ShopNode);
	ShopNode();
	~ShopNode();
	virtual bool init();
	static ShopNode * createShopNode(int shopType, int index, std::function<void(Ref *)> clickCallback);

	void initUI();
	void setShopNodeState(int shopType, int index, std::function<void(Ref *)> clickCallback);
	void dealButtonClick(Ref * pSender);

	bool setUse(bool isUse, bool isInit = false);
	bool buy();

	void playLightAction();
	void playSelectAction();

	void refush(int coinNum);
    void updateUI();
private:

	Layout * panel_item;
	ImageView * img_light_1, *img_light_2;
	
	ImageView *img_coin, *img_new;
    Sprite *img_card;
	Text * text_item;
	TextBMFont * atlasLabel_num;
    Sprite *Sprite_used;
    Button *Button_use, *Button_buy;

	bool isBuyed;
	bool isUsing;

	int shopType;
	int index;

	int price;
	bool isTouchMove;
    Vec2 img_card_poi;

};


# endif
