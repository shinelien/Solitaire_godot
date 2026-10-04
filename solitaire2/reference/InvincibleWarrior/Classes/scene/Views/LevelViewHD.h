
#ifndef SpacecatSolitaireGame_LevelViewHD_H
#define SpacecatSolitaireGame_LevelViewHD_H

#include "BaseLayer.h"
#include "Factory.hpp"

class LevelViewHD : public BaseLayer, public Factory<LevelViewHD> {
public:
    enum Tab {
        Level0,
        Level1
    };
    virtual ~LevelViewHD();
    LevelViewHD(bool isLobby = false);

    void showLevel(int tab, int level = 0);
    void startLevel(int sub);
    void complete(bool isWin, std::shared_ptr<rapidjson::Document> levelData);
    void updateUI();
    void showTabWithLevel(int tab, int level = 0);
    void setIsStart(bool is);
    bool getIsStart();
    void resetView();
    void updateDYY();
protected:
    void initLevel0();
    void initLevel1(int level);

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    int _currentTab = -1, _currentLevel = -1, _currentSub = -1;
    bool _first = true;
    ListView *_listview_bg0, *_listview_bg1;
    bool _isLobby;
    bool isStart = true;
};

#endif //SpacecatSolitaireGame_LevelViewHD_H
