
#ifndef SpacecatSolitaireGame_TipsNode_H
#define SpacecatSolitaireGame_TipsNode_H

#include "BaseLayer.h"
#include "Factory.hpp"

class TipsNode : public BaseLayer, public Factory<TipsNode> {
public:
    virtual ~TipsNode();
    TipsNode();

private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;
    
    
private:
    ParticleSystemQuad* Particle_2;
};

#endif //SpacecatSolitaireGame_TipsNode_H
