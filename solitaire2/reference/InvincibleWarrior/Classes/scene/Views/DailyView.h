
#ifndef NewSpaceCatSolitaire_DailyView_H
#define NewSpaceCatSolitaire_DailyView_H

#include "BaseLayer.h"
#include "Factory.hpp"
#include "DailyManager.h"

class DailyNode;
class MainLobby;
class DailyGameView;
class DailyMoreView;
class DailyView : public BaseLayer, public Factory<DailyView> {
public:
    virtual ~DailyView();
    DailyView* showComplete();
    
    DailyView(MainLobby *lobby = nullptr);
    void setCurrentSelectNode(DailyNode* selectNode);
    void updateUI(int days = 0, bool isComplete = false);
    void completeCB();
    void aniEventCB(bool completed = true);
    float getPercent(int current, int days);
    void updataScrollPoi(DailyNode* item);
    void updateDYY();
    void showCompleteAni();
    void scrollEvent(Ref*, ScrollviewEventType);

    Date getSelectedNode();
    void showSelectDialog(bool isCompletedView = false, int tag = 1);
    void hideStart();
    PageView* getPage()
    {
        return pageView;
    }
    void updatePage(PageView* page);
    
    void setToDay();
    void setPageUI(int year, int month, int selectDay_ = 0);
    void setMoreUI(int year, int month, int selectDay_ = 0,bool isPage = false);
    void showStart();
    
    void hideMore();
    void leftMore();
    void rightMore();
    
    void clearFileNodeStart();
    void clearPanelMoret();
    
    //筛选简单的日期
    void filterSimpleDate();
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    void setMonthUI(int year, int month, int selectDay_ = 0);
    bool updateDate(Date date);
    std::string getTrophyShadow(int monthCompleteCNT, int days);
    std::string getTrophy(int monthCompleteCNT, int days);
    
public:
    void onEnter() override;

    void onExit() override;

private:
    
    
    void crownComplete();

    DailyNode *_selectedNode = nullptr;
    Date _current, _today,_current2,_maxday;
    Node  *FileNode_crown, *FileNode_trophy,*FileNode_StarBox,*FileNode_StarBox2;
    DailyGameView*FileNode_start = nullptr;
    DailyMoreView*Panel_more = nullptr;
    int _monthPlayCNT = 0, _monthCompleteCNT = 0, _tag = 1, _effectID = -1;
    //是否来自lobby
    MainLobby* _lobby;

    //翻页容器
    PageView* pageView;
    
    int pageNum;
    bool isLeft;
    Vec2 LRPoi;
    
    int _coinNum, _lastIndex;
    int _diamondNum;
    Node* FileNode_MyBag;
    float percent;
    bool isPageRun = false;
    
    //page触摸事件
    bool isPageTouch = false;//是否触摸page
    bool isPageDistance = false;//是否移动够一定距离

    Vec2 curLayoutStartPoi;//当前显示layout初始坐标
    Vec2 curLayoutTempPoi;//当前显示layout实时坐标
    Size pageSize;
    Rect pageRect;
    bool isJump;
    
    //page按钮
    Button* Button_hardRight,*Button_hardLeft1;
    bool isToDay = false;
    bool isUpdateDay;
    //新增限制后page往左翻页没有走回调
    bool isPageLeft,isPageLeft_2;
    bool isPageRight,isPageRight_2;
    int pageItemNum = 0;
    
    bool isUpdatePage;
    //记录当前页
    int _currentIndex;
};

#endif //NewSpaceCatSolitaire_DailyView_H
