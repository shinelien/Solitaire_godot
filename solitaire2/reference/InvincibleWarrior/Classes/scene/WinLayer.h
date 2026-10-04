# ifndef __WIN_LAYER__
# define __WIN_LAYER__

# include "BaseLayer.h"
# include "DataManager.h"
# include "SoundManager.h"

class WinLayer : public BaseLayer
{
public:

	CREATE_FUNC(WinLayer);

	WinLayer();

	static Scene * createScene();
    static WinLayer * createLayer();
	static WinLayer * createLayer(int score, float time, int moveNum, int extraScore, int totalStar);
	virtual void initUI();
	virtual bool init();
	
	void initData(); //初始化数据

	void dealButtonClick(Ref * pSender);// , ui::TouchEventType teType);

	void showAction(int score, float time, int moveNum, int extraScore, int totalStar);
    void showPokersAction();
    
    void updateDYY();
    void getVideoReward(EventCustom *eventCustom);
    
    void onEnter() override;
    void onExit() override;
    void updateRank();
private:

	TextBMFont * atlasLabel_you_score, *atlasLabel_best_score;
    TextBMFont * text_you_ExtraScore, *text_best_ExtraScore;
    TextBMFont * text_you_TotalScore, *text_best_TotalScore;
	TextBMFont * atlasLabel_you_time, *atlasLabel_best_time;
	TextBMFont * atlasLabel_you_movetime, *atlasLabel_best_movetime, *atlasLabel_coinnum,*atlasLabel_coinnum_0,*atlasLabel_coinnum_0_0,*atlasLabel_zuanShiNum,*BitmapFontLabel_doubleCoin,
    *atlasLabel_rank;
    Text *Text_modeformat, *Text_percent,*Text_lv,*Text_look,*Text_rank;
    int _coinNum = 0,_extraCoinNum = 0;
	Node * panel[7], *FileNode_gold,*FileNode_zuanShi;
    LoadingBar* loadingBar_percent;
    
    int lv = 0,oldLv = 0;
    float percent1 = 0,percent2 = 0;
    bool isBar = false;
    bool isQieHuan = false;
    int multipleNum;
    int tempMultipleNum = 0;
    bool isMultiple;
    float maxPercent;
    
    float percentDx;
    int starNum;
    
    bool isButton;
    bool isShowStar;
    
    std::function<void()> _InterstitialCB = nullptr;
    
    //第一次引导提前出现按钮
    bool isOneTeach;
    //防错
    float fangCuoTime;
    bool isBtnAni;
    bool isAds = false;
    bool isGuide = false;
    bool isTouch;
};

# endif
