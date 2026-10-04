
#ifndef SpacecatSolitaireGame_WinLayerLevelHD_H
#define SpacecatSolitaireGame_WinLayerLevelHD_H

#include "BaseLayer.h"
#include "Factory.hpp"

class WinLayerLevelHD : public BaseLayer, public Factory<WinLayerLevelHD> {
public:
    virtual ~WinLayerLevelHD();
    WinLayerLevelHD();
    WinLayerLevelHD(bool isWin, std::shared_ptr<rapidjson::Document> levelData, bool isFirst, int star);
    void showAction(bool isWin, std::shared_ptr<rapidjson::Document> levelData, bool isFirst, int star);
    void updateDYY();
    
    void onEnter() override;
    void onExit() override;
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    bool _isWin, _isFirst;
    int _star;
    TextBMFont *atlasLabel_coinnum,*atlasLabel_zuanShiNum,*BitmapFontLabel_doubleCoin;
    Node *FileNode_gold,*FileNode_zuanShi;
    std::shared_ptr<rapidjson::Document> _levelData;
    int multipleNum;
    int tempMultipleNum;
    bool isMultiple;
    Text*Text_doubleCoin;
    bool isButton;
    bool isShowStar;
    int _coinNum = 0;
    int _diamondNum = 0;
    
    std::function<void()> _InterstitialCB = nullptr;
    
    float  fangCuoTime = 0;
    bool isBtnAni = false;
};

#endif //SpacecatSolitaireGame_WinLayerLevelHD_H
