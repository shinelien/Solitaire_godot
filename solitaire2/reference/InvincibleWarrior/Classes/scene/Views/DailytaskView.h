//
//  DailytaskView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/25.
//

#ifndef DailytaskView_h
#define DailytaskView_h
#include "BaseLayer.h"
#include "Factory.hpp"
class GameViewHD;
class MainLobby;
class DailytaskView : public BaseLayer, public Factory<DailytaskView> {
public:
    
    virtual ~DailytaskView();
    DailytaskView(std::function<void()> cb = nullptr);
    void updateUI();
    
    void openBox(int idx);
    void updateCoin(bool isDelay = false);
    void updateDiamond(bool isDelay = false);
    void onEnter() override;
    void onExit() override;
    
    int getGoldNum(int id);
    int getDiamondNum(int id);
    void jumpLayer(int type);
    
    float getFontSize(int type);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    Node* FileNode_task1,*FileNode_task2,*FileNode_task3,* Panel_7,*Panel_Box1,*Panel_Box2,*Panel_Box3;
    LoadingBar* LoadingBar_task,*LoadingBar_task1,*LoadingBar_task2,*LoadingBar_task3;
    Text* Text_TaskNum1,* Text_TaskNum2,* Text_TaskNum3;
    Text* Text_miaoshu1,* Text_miaoshu2,* Text_miaoshu3;
    
    Text* Text_15_reward1,*Text_15_reward2,*Text_15_reward3;
    Sprite* TaskBox_1,*TaskBox_2,*TaskBox_3;
    std::function<void()> _cb;
    GameViewHD* _gameView;
    MainLobby* _mainLobby;
    //是否打开宝箱
    bool isBox1,isBox2,isBox3;
    //任务是否完成
    bool isTask1,isTask2,isTask3;
    float percentB,percentE;
    bool isBar;
    int taskId = 0;
    int _coinNum = 0;
    int _coinNum2;
    int _diamondNum;
    int _diamondNum2;
    int _boxNum = 0;//开启箱子的个数
    bool isReward = false;//在奖励中按钮失效
    
    int _taskType1;
    int _taskType2;
    int _taskType3;
    int _tempTaskType;
    
    int fangCuoNum;
};

#endif /* DailytaskView_h */
