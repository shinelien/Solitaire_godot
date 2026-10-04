
#ifndef NewSpaceCatSolitaire_DailyNode_H
#define NewSpaceCatSolitaire_DailyNode_H

#include "BaseLayer.h"
#include "Factory.hpp"
#include "DailyManager.h"

class DailyMoreView;
class DailyNode : public BaseLayer, public Factory<DailyNode> {
public:
    enum class State {
        Open,
        Completed,
        Closed
    };
    
    enum class Type
    {
        day,
        month,
    };

    virtual ~DailyNode();
    DailyNode(DailyMoreView *parentView, Date tm,DailyNode::Type type);
    void setState(State state);
    State getState()
    {
        return _state;
    }
    void updateUI();
    void setSelected(bool flag);
    Date getDate() { return _tm; }
    void setDate(Date date) {_tm = date;}
    void showWin();
    
    void updateDYY();

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    Date _tm;
    DailyMoreView *_parentView;
    ImageView* Image_root;
    State _state = State::Open;
    bool _selected = false;
    DailyNode::Type _type;
};

#endif //NewSpaceCatSolitaire_DailyNode_H
