/*
	唯一的层
	author:codehua
*/
# ifndef __MAIN_SCENE__
# define __MAIN_SCENE__

# include "UIUtils.h"
# include "SceneManager.h"
# include "DataManager.h"
# include "SoundManager.h"

class MainScene : public Scene
{
public:

	MainScene();
	~MainScene();

	static Scene * createScene();
	virtual void initUI();
	virtual bool init();
	
	void initData(); //初始化数据

	void dealButtonClick(Ref * pSender);// , ui::TouchEventType teType);

	virtual bool onTouchBegan(Touch * t, Event * e);
	virtual void onTouchMoved(Touch * t, Event * e);
	virtual void onTouchEnded(Touch * t, Event * e);

	void update(float dt);

	void addLayer(Node * layer);		//添加界面
	void removeLayer(Node * layer);	//移除界面
	void removeLayerByName(const char * name);
	void removeLayerByTag(int tag);
    bool hasLayerByName(const string &name);

	void removeAllLayer();//移除所有的界面
    void removeLayer();//移除大厅与游戏c窗口除外的弹窗

	void showTips(string tipStr,bool isNoTips = false,std::function<void()> cb = nullptr);
    
    Node* getRewardNode();
    Node* getWinLayerNode();
    Node* getStarNode();
    void clickEff(Vec2 poi);
public:
	static MainScene * g_mainScene; 
private:
	vector<string> layerNames;
    
    //add奖励的节点呢
    Node* rewardNode = nullptr;
    //星星节点
    Node* starNode = nullptr;
    //结算btn防错节点
    Node* winLayerFCNode = nullptr;
};

# endif
