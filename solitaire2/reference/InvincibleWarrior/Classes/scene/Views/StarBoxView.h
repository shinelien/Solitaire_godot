//
//  StarBoxView.h
//  NewSpaceCatSolitaire
//
//  Created by lien on 2020/2/25.
//

#ifndef StarBoxView_h
#define StarBoxView_h
#include "BaseLayer.h"
#include "Factory.hpp"
class GameViewHD;
class HomeView;
class DailyView;
class MainLobby;
class StarBoxView : public BaseLayer, public Factory<StarBoxView>
{
public:
    enum class Type
    {
        Home,
        Daily,
        Level,
        None,
    };
    StarBoxView(StarBoxView::Type type = StarBoxView::Type::None);
    ~StarBoxView();
    
    virtual void onExit() override;
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
private:
    GameViewHD* _gameView;
    MainLobby* _mainLobby;
    HomeView* _homeView;
    DailyView* _dailyView;
    StarBoxView::Type _type;
    Node* FileNode_box;
};

#endif /* StarBoxView_h */
