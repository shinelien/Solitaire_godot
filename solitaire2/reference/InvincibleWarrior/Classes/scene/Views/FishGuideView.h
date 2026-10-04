//
//  FishGuideView.h
//  NewSpaceCatSolitaire
//
//  Created by 宋 on 2021/6/30.
//

#ifndef FishGuideView_h
#define FishGuideView_h
#include "BaseLayer.h"
#include "Factory.hpp"
#include <spine/AnimationState.h>
namespace spine {
    class SkeletonAnimation;
}

class FishGuideManager;
class FishGuideView : public BaseLayer, public Factory<FishGuideView>
{
public:
    //No down happy loop think up yes
    enum class FishMoveType
    {
        None,
        No,
        down,
        happy,
        loop,
        think,
        up,
        yes,
        aniNum,
    };
    FishGuideView();
    ~FishGuideView();
    
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    
    void onEnter() override;
    void onExit() override;
    
    void setGuideType(int type);
    
    void startGuide(string tips = "");
    void updateText(float dt);
    
    void setShowPoi(Vec2 poi) { shouPoi = poi; }
    
    void fishPlayAni(string aniName,bool loop,float speed = 1);
    void setTargetNode(Node* node) { targetNode = node; }
    void setBtnScale(float scale) { _btnScale = scale; }
    void jiaohuan(bool isJiaoHuan);
    void hide();
    void setIdx(int idx);
private:
    Node* FileNode_tips,*FileNode_shou,*Panel_1,*FileNode_JianTou,*Node_btn;
    Text* Text_miaoshu,*Text_name;
    int _guideType;
    bool _isPlayText;
    //对话 逐字显示
    vector<char> _duiHuaVec;
    int _duiHuaIndex;
    bool _isTouch,_isTempTouch,_isTipsShow;
    spine::SkeletonAnimation *_fishWinSkeletonNode;
    Vec2 shouPoi;
    
    FishMoveType _fishMoveType;
    ImageView* Image_1,* Image_2;
    Node* clickBtn;
    Node* targetNode;
    
    Node* clickBtnParent;
    Vec2 clickBtnPoi;
    int localZOder;
    ParticleSystemQuad* particle;
    ActionTimeline *_actionManager = nullptr;
    float _btnScale;
    
    int _aniNum;
    bool isHide;
    int _idx;
};

#endif /* FishGuideView_h */
