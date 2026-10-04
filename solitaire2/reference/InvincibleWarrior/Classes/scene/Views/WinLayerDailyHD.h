# ifndef __WIN_LAYER_DAILY__
# define __WIN_LAYER_DAILY__

# include "BaseLayer.h"
# include "DataManager.h"
# include "SoundManager.h"

class WinLayerDailyHD : public BaseLayer
{
public:

	CREATE_FUNC(WinLayerDailyHD);

	WinLayerDailyHD();

	static Scene * createScene();
    static WinLayerDailyHD * createLayer();
	static WinLayerDailyHD * createLayer(int score, float time, int moveNum, int extraScore, int totalStar);
	virtual void initUI();
	virtual bool init();
	
	void initData(); //初始化数据

	void dealButtonClick(Ref * pSender);// , ui::TouchEventType teType);

	void showAction(int score, float time, int moveNum, int extraScore, int totalStar);
    void showPokersAction();
    void updateDYY();
    
    
    
    void onEnter() override;
    
    void onExit() override;
private:

	TextBMFont * atlasLabel_you_score, *atlasLabel_best_score;
    TextBMFont * text_you_ExtraScore, *text_best_ExtraScore;
    TextBMFont * text_you_TotalScore, *text_best_TotalScore;
	TextBMFont * atlasLabel_you_time, *atlasLabel_best_time;
	TextBMFont * atlasLabel_you_movetime, *atlasLabel_best_movetime, *atlasLabel_coinnum,*atlasLabel_zuanShiNum,*BitmapFontLabel_doubleCoin;
    Text *Text_modeformat, *Text_percent,*Text_lv,*Text_doubleCoin;
    int _coinNum = 0;
    int _diamondNum = 0;
	Node * panel[7], *FileNode_gold,*FileNode_zuanShi;
    
    int lv = 0,oldLv = 0;
    float percent1 = 0,percent2 = 0;
    bool isBar = false;
    bool isQieHuan = false;
    LoadingBar* loadingBar_percent;
    int multipleNum;
    int tempMultipleNum = 0;
    bool isMultiple;
    float maxPercent;
    float percentDx;
    bool completed;
    int starNum;
    bool isButton;
    bool isShowStar;
    std::function<void()> _InterstitialCB = nullptr;
    
    float  fangCuoTime = 0;
    bool isBtnAni = false;
    bool isAds = false;
};

# endif
