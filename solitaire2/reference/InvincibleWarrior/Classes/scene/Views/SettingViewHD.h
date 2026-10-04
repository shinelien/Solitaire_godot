//
//  SettingViewHD.h
//  SpacecatSolitaireGame-mobile
//
//  Created by Cyutao on 2018/9/1.
//

#ifndef SettingViewHD_hpp
#define SettingViewHD_hpp

#include "BaseLayer.h"
#include "Factory.hpp"

class GameViewHD;
class MainLobby;
class SettingViewHD : public BaseLayer, public Factory<SettingViewHD>
{
public:
    enum class ViewType
    {
        Home,
        Daily,
        Game,
    };
	SettingViewHD(SettingViewHD::ViewType type);
    virtual ~SettingViewHD();
    virtual void onExit() override;
    void initData() override;
    void initUI() override;

	void dealButtonClick(Ref *pSender) override;
    void testBlur();
    
    void initDyy();
    
    void updateDYY();
protected:
    void setDYY(int type);
	void setThreeModel(bool isThreeModel);
	void setMusic(bool isMusic);
    void setEffMusic(bool isMusic);
    void setLeftModel(bool isLeftModel);
    void setAnimation(bool flag);
    void setAutoTips(bool flag);
    //广告模式
    void setGuangGao(bool flag);
private:
	Button *btn_three_on, *btn_left_on, *btn_music_on, *btn_donghua,*btn_autoTips,*btn_effTips,*btn_guangGao;
    Button *btn_three_on_update, *btn_left_on_update, *btn_music_on_update, *btn_donghua_update,*btn_autoTips_update,*btn_effTips_update;
	GameViewHD *_gameView = nullptr;
    MainLobby* _lobby;
    SettingViewHD::ViewType _type;
    
    ListView* ListView_dyy;
};

#endif /* SettingViewHD_hpp */
