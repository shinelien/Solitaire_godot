
#ifndef NewSpaceCatSolitaire_Dialog_H
#define NewSpaceCatSolitaire_Dialog_H

#include "BaseLayer.h"
#include "Factory.hpp"

using CBFunc = std::function<void()>;
class Dialog : public BaseLayer, public Factory<Dialog> {
public:
    enum Type {
        Normal
    };

    virtual ~Dialog();
    Dialog(Type type, CBFunc ok, CBFunc no);
    void setText(const std::string &title, const std::string &content, const std::string &yes, const std::string &no);
private:
    void initUI() override;
    void initData() override;
    void dealButtonClick(Ref *pSender) override;

    CBFunc _cbOk, _cbNo;
    Type _type;
};

#endif //NewSpaceCatSolitaire_Dialog_H
