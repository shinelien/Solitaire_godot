//
//  SettingViewHD.cpp
//  SpacecatSolitaireGame-mobile
//
//  Created by Cyutao on 2018/9/1.
//

#include "SettingViewHD.h"
#include "GameViewHD.hpp"
#include "DataManager.h"
#include "SpriteManager.h"
#include "RuleLayer.h"
#include "CountLayer.h"
#include "PrivacyViewHD.h"
#include "GameKitHelper.h"
#include "MainLobby.h"
#include "ThreeModelTips.h"

USING_NS_CC;
SettingViewHD::SettingViewHD(SettingViewHD::ViewType type)
:BaseLayer("UI_set.csb")
,_type(type)
,_lobby(nullptr)
{
    
}

SettingViewHD::~SettingViewHD()
{
    
}

void SettingViewHD::initData()
{
    setName("SettingViewHD");
}

void SettingViewHD::initUI()
{
    BaseLayer::initUI();
    doLayout();
    
    ListView_dyy = getNode<ListView*>("ListView_dyy");
    auto Node_update = getNode("Node_update");
    auto Node_1 = getNode("Node_1");
    auto isNewVer = DATA_M->isNewVer();
    Node_1->setVisible(!isNewVer);
    Node_update->setVisible(isNewVer);
    _gameView = SCENE_M->getGameView();
    _lobby = SCENE_M->getLobby();
    // 出初始话控件
    btn_three_on = getNode<Button*>("btn_three_on_0");
    btn_left_on = getNode<Button*>("btn_left_on");
    btn_donghua = getNode<Button*>("btn_donghua");
    btn_autoTips = getNode<Button*>("btn_AutoTips");
    btn_music_on = getNode<Button*>("btn_MusicTips");
    btn_effTips = getNode<Button*>("btn_effTips");
    btn_guangGao = getNode<Button*>("btn_guangGao_on");
    getNode<Text*>("Text_version")->setString(string("v")+GETSTR("bu_version", "1.0.0"));
    //更新相关
    btn_three_on_update = getNode<Button*>("btn_three_on_0_update");
    btn_left_on_update = getNode<Button*>("btn_left_on_update");
    btn_donghua_update = getNode<Button*>("btn_donghua_update");
    btn_autoTips_update = getNode<Button*>("btn_AutoTips_update");
    btn_music_on_update = getNode<Button*>("btn_MusicTips_update");
    btn_effTips_update = getNode<Button*>("btn_effTips_update");
    
    initDyy();
    
    setThreeModel(DATA_M->getIsThreeModel());
    setLeftModel(DATA_M->getIsLeftModel());
    setAnimation(DATA_M->isWinHDEnable());
    setAutoTips(DATA_M->getIsAutoTips());
    setEffMusic(DATA_M->getIsEffect());
    setMusic(DATA_M->getIsMusic());
    setDYY(DATA_M->getDyyNum());
    //setGuangGao(DATA_M->getGuangGao());
    // 经典牌局难度控制
//    auto Slider_hard = getNode<Slider*>("Slider_hard");
//#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
//    if (Slider_hard) {
//        Slider_hard->setPercent(DATA_M->getGameHard());
//        Slider_hard->addEventListener([this, Slider_hard](Ref*,Slider::EventType type){
//            if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
//                DATA_M->setGameHard(Slider_hard->getPercent());
//            }
//        });
//    }
//#else
//    Slider_hard->setVisible(false);
//#endif
    _actionManager->play("Start", false);
    _actionManager->setLastFrameCallFunc([this]{
    });
//    this->testBlur();
}

void SettingViewHD::dealButtonClick(Ref *pSender) {
    auto btn = dynamic_cast<Widget*>(pSender);
    if (btn == nullptr) {
        return;
    }
    auto btnName = btn->getName();
    if (btnName == "Button_rule"||btnName == "Button_rule_update") {
        //显示规则界面
        SCENE_M->addDialog(RuleLayer::createLayer(this));
        this->setVisible(false);
    }
    else if (btnName == "panel_statistics") {
        //显示统计界面
//        SCENE_M->addDialog(CountLayer::createLayer());
        UIUtils::writComment();
    }
    else if (btnName == "Button_privacy"||btnName == "Button_privacy_update") {
        //隐私政策
//        SCENE_M->addDialog(PrivacyViewHD::createLayerN());
        Application::getInstance()->openURL("https://sites.google.com/view/space-cat-studio/%E9%A6%96%E9%A1%B5");
    }
    else if (btnName == "panel_dfd") {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        GameKitHelper::openMail();
#endif
    }
    else if ("Button_three" == btnName||"Button_three_update" == btnName)
    {
        //显示三张牌
        setThreeModel(!DATA_M->getIsThreeModel());
        auto gameView = SCENE_M->getGameView();
        if(_type == SettingViewHD::ViewType::Game&&gameView->getIsThreeModel() == !DATA_M->getIsThreeModel())
        {
            SCENE_M->addDialog(ThreeModelTips::createLayerN(this));
            this->setVisible(false);
        }
    }
    else if ("Button_left" == btnName||"Button_left_update" == btnName)
    {
        //显示左手模式
        setLeftModel(!DATA_M->getIsLeftModel());
    }
    else if ("Button_music" == btnName||"Button_music_update" == btnName||btnName == "btn_MusicTips")
    {
        //音乐开关
        setMusic(!DATA_M->getIsMusic());
    }
    else if ("btn_donghua" == btnName)
    {
        //动画开关
        setAnimation(!DATA_M->isWinHDEnable());
    }
    else if ("Button_Auto" == btnName||"Button_Auto_update" == btnName||btnName == "btn_AutoTips")
    {
        //自动提示开关
        setAutoTips(!DATA_M->getIsAutoTips());
    }
    else if ("btn_set_close" == btnName || btnName == "Panel_out") {
        //关闭窗口开始累计计时
        if(_type == SettingViewHD::ViewType::Game)
        {
            _gameView->gamePause(false);//解除暂停
            _gameView->setIsOpenTipsTime(true);
        }
        this->removeFromParent();
    }
    else if("Button_endAni" == btnName)
    {//指定动画
        auto tag = btn->getTag();
        DATA_M->setEndAniIdx(tag);
        DATA_M->setIsEndAniAll(false);
    }
    else if("Button_startAni" == btnName)
    {//指定动画
        auto tag = btn->getTag();
        DATA_M->setStartAni(tag);
        //DATA_M->setIsEndAniAll(false);
    }
    else if("Button_guangGao" == btnName)
    {//指定动画
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
        
#endif
        setGuangGao(!DATA_M->getGuangGao());
    }
    else if(btnName == "Button_setdyy"||btnName == "Button_setdyy_update")
    {
        getNode("Node_dyy")->setVisible(true);
        playAni("Start1",false);
    }
    else if(btnName == "Button_dyy0")
    {
        auto tag = btn->getTag();
        setDYY(tag);
    }
    else if(btnName == "Button_eff"||btnName == "Button_eff_update"||btnName == "btn_effTips")
    {//yinn xiao音效  btn_effTips
        setEffMusic(!DATA_M->getIsEffect());
    }
    else if("Button_endAniAll" == btnName)
    {
        DATA_M->setIsEndAniAll(true);
    }
    else if(btnName == "btn_dyy_close")
    {
        getNode("Node_dyy")->setVisible(false);
    }
    else if(btnName == "Button_update")
    {
        Application::getInstance()->openURL("https://play.google.com/store/apps/details?id=com.cn.spacecate.solitaire2k");
    }
}

void SettingViewHD::initDyy()
{
    
    
    auto Button_dyy0 = getNode<Widget*>("Button_dyy0");
    int i  = 0;
    while (i < 9) {
        auto item = Button_dyy0->clone();
        
        ListView_dyy->pushBackCustomItem(item);
        i++;
        item->setTag(i);
    }
    
}

void SettingViewHD::setDYY(int type)
{//点一下切换一个语言。中文 繁体 英语 日语 韩语 法语 德语
    //重置UIUtils语言文件
    
    auto num = DATA_M->getDyyNum();
    if(num != type)
    {
        SCENE_M->showTips(Lang("100294"));
    }
//    getNode<Text*>("text_dyy_1")->setString(Lang("100266"));
//    getNode<Text*>("text_dyy_2")->setString(Lang("100267"));
//    getNode<Text*>("text_dyy_3")->setString(Lang("100268"));
//    getNode<Text*>("text_dyy_4")->setString(Lang("100269"));
//    getNode<Text*>("text_dyy_5")->setString(Lang("100270"));
//    getNode<Text*>("text_dyy_6")->setString(Lang("100271"));
//    getNode<Text*>("text_dyy_7")->setString(Lang("100272"));
    DATA_M->setDyyNum(type);//替换语言文件
    string str = "";
    if(type == 1)
    {
        str = "100266";
    }
    else if(type == 2)
    {
        str = "100267";
    }
    else if(type == 3)
    {
        str = "100268";
    }
    else if(type == 4)
    {
        str = "100269";
    }
    else if(type == 5)
    {
        str = "100270";
    }
    else if(type == 6)
    {
        str = "100271";
    }
    else if(type == 7)
    {
        str = "100272";
    }
    else if(type == 8)
    {
        str = "100324";
    }
    else if(type == 9)
    {
        str = "100325";
    }
    
    getNode<Text*>("text_Language_0")->setString(Lang(str) + " >");
    getNode<Text*>("text_Language_0_update")->setString(Lang(str) + " >");
    auto vec = ListView_dyy->getItems();
    for(int i = 0;i < (int)vec.size();++i)
    {
        auto item = vec.at(i);
        auto btn = item->getChildByName<Button*>("btn_dyy0");
        
        auto tag = item->getTag();
        if(tag == type)
        {
            btn->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
            btn->loadTexturePressed("ui_switch0.png", Widget::TextureResType::PLIST);
        }
        else
        {
            btn->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
            btn->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        }
        
    }
    
//    for(int i = 1;i<10;++i)
//    {
//        if (i == type)
//            {
//
//                getNode<Button*>(StringUtils::format("btn_dyy_%d",i))->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
//                getNode<Button*>(StringUtils::format("btn_dyy_%d",i))->loadTexturePressed("ui_switch0.png", Widget::TextureResType::PLIST);
//        //        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_three"), "animation0", false);
//            }
//            else
//            {
//                getNode<Button*>(StringUtils::format("btn_dyy_%d",i))->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
//                getNode<Button*>(StringUtils::format("btn_dyy_%d",i))->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
//        //        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_three"), "Start", false);
//            }
//    }
    
    
    updateDYY();
    _gameView->updateDYY();
    if(_lobby)
    {
        _lobby->updateDYY();
    }
}

void SettingViewHD::updateDYY()
{
    FIND_NODE(Text *,this,"Text_settingTitle")->setString(UIUtils::getStringByName("100071"));
    FIND_NODE(Text *,this,"Text_settingTitle_update")->setString(UIUtils::getStringByName("100071"));
    FIND_NODE(Text *,this,"text_three_0")->setString(UIUtils::getStringByName("100045"));
    auto text_three_0_0 = FIND_NODE(Text *,this,"text_three_0_0");
    text_three_0_0->setString(UIUtils::getStringByName("100046"));
    UIUtils::textAdaptiveSize(text_three_0_0,760);
    FIND_NODE(Text *,this,"text_three_0_update")->setString(UIUtils::getStringByName("100045"));
    auto text_three_0_0_update = FIND_NODE(Text *,this,"text_three_0_0_update");
    text_three_0_0_update->setString(UIUtils::getStringByName("100046"));
    UIUtils::textAdaptiveSize(text_three_0_0_update,760);
    
    FIND_NODE(Text *,this,"text_left")->setString(UIUtils::getStringByName("100047"));
    FIND_NODE(Text *,this,"text_left_update")->setString(UIUtils::getStringByName("100047"));
    
    auto text_music = FIND_NODE(Text *,this,"text_music");
    auto text_effTips = FIND_NODE(Text *,this,"text_effTips");
    text_music->setString(UIUtils::getStringByName("100240"));
    text_effTips->setString(UIUtils::getStringByName("100048"));
    UIUtils::textAdaptiveSize(text_music,113);
    UIUtils::textAdaptiveSize(text_effTips,113);
    
    auto text_music_update = FIND_NODE(Text *,this,"text_music_update");
    auto text_effTips_update = FIND_NODE(Text *,this,"text_effTips_update");
    text_music_update->setString(UIUtils::getStringByName("100240"));
    text_effTips_update->setString(UIUtils::getStringByName("100048"));
    UIUtils::textAdaptiveSize(text_music_update,113);
    UIUtils::textAdaptiveSize(text_effTips_update,113);
    FIND_NODE(Text *,this,"text_rule")->setString(UIUtils::getStringByName("100049"));
    FIND_NODE(Text *,this,"text_count")->setString(UIUtils::getStringByName("100050"));
    FIND_NODE(Text *,this,"text_donghua")->setString(UIUtils::getStringByName("100114"));
    FIND_NODE(Text *,this,"text_rule_update")->setString(UIUtils::getStringByName("100049"));
    auto text_privacy = FIND_NODE(Text *,this,"text_privacy");
    text_privacy->setString(UIUtils::getStringByName("100108"));
    UIUtils::textAdaptiveSize(text_privacy,290);
    auto text_privacy_update = FIND_NODE(Text *,this,"text_privacy_update");
    text_privacy_update->setString(UIUtils::getStringByName("100108"));
    UIUtils::textAdaptiveSize(text_privacy_update,290);
    getNode<Text*>("text_AutoTips")->setString(Lang("100183"));
    getNode<Text*>("text_Language")->setString(Lang("100265"));
    getNode<Text*>("Text_settingdyy")->setString(Lang("100265"));
    
    getNode<Text*>("text_AutoTips_update")->setString(Lang("100183"));
    getNode<Text*>("text_Language_update")->setString(Lang("100265"));
    
    getNode<Text*>("text_update")->setString(Lang("100378"));
    auto vec = ListView_dyy->getItems();
    for(int i = 0,j = 0;i < (int)vec.size();++i)
    {
        auto item = vec.at(i);
        auto text = item->getChildByName<Text*>("text_dyy0");
        if(i < 7)
        {
            text->setString(Lang(StringUtils::toString(100266 + i)));
        }
        else
        {
            text->setString(Lang(StringUtils::toString(100324 + j)));
            j++;
        }
        
    }
    
//    getNode<Text*>("text_dyy_1")->setString(Lang("100266"));
//    getNode<Text*>("text_dyy_2")->setString(Lang("100267"));
//    getNode<Text*>("text_dyy_3")->setString(Lang("100268"));
//    getNode<Text*>("text_dyy_4")->setString(Lang("100269"));
//    getNode<Text*>("text_dyy_5")->setString(Lang("100270"));
//    getNode<Text*>("text_dyy_6")->setString(Lang("100271"));
//    getNode<Text*>("text_dyy_7")->setString(Lang("100272"));
}

void SettingViewHD::setThreeModel(bool isThreeModel)
{
    DATA_M->setIsThreeModel(isThreeModel);
    if (isThreeModel)
    {
        btn_three_on->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_three_on->loadTexturePressed("ui_switch0.png", Widget::TextureResType::PLIST);
        
        btn_three_on_update->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_three_on_update->loadTexturePressed("ui_switch0.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_three"), "animation0", false);
    }
    else
    {
        btn_three_on->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_three_on->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        
        btn_three_on_update->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_three_on_update->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_three"), "Start", false);
    }
}

void SettingViewHD::setMusic(bool isMusic)
{
    DATA_M->setIsMusic(isMusic);
    if (isMusic)
    {
        btn_music_on->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_music_on->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
        
        btn_music_on_update->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_music_on_update->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "animation0", false);
    }
    else
    {
        btn_music_on->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_music_on->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        
        btn_music_on_update->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_music_on_update->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "Start", false);
    }
}

void SettingViewHD::setEffMusic(bool isMusic)
{
    DATA_M->setIsEffect(isMusic);
    if (isMusic)
    {
        btn_effTips->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_effTips->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
        
        btn_effTips_update->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_effTips_update->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "animation0", false);
    }
    else
    {
        btn_effTips->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_effTips->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        
        btn_effTips_update->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_effTips_update->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
//        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "Start", false);
    }
}

void SettingViewHD::setAnimation(bool flag)
{
    DATA_M->setWinHDEnable(flag);
    if (flag)
    {
        btn_donghua->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_donghua->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
        //        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "animation0", false);
    }
    else
    {
        btn_donghua->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_donghua->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        //        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "Start", false);
    }
}

void SettingViewHD::setLeftModel(bool isLeftModel)
{
    DATA_M->setIsLeftModel(isLeftModel);

    if (isLeftModel)
    {
        btn_left_on->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_left_on->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
        
        btn_left_on_update->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_left_on_update->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
//		UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_leftmodel"), "animation0", false);
    }
    else
    {
        btn_left_on->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_left_on->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        
        btn_left_on_update->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_left_on_update->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
//		UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_leftmodel"), "Start", false);
    }
    if (_gameView->getLeftModel() != isLeftModel)
    {
        _gameView->setLeftModel(isLeftModel);
        _gameView->changePos();
        SPRITE_M->setLeftModel();
    }
}

void SettingViewHD::setAutoTips(bool flag)
{
    DATA_M->setIsAutoTips(flag);
    
    if (flag)
    {
        btn_autoTips->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_autoTips->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
        
        btn_autoTips_update->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_autoTips_update->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
        //        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "animation0", false);
    }
    else
    {
        btn_autoTips->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_autoTips->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        
        
        btn_autoTips_update->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_autoTips_update->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        //        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "Start", false);
    }
    
}

void SettingViewHD::testBlur()
{
    // TODO 再截一张图就好了额 不过不能实现动态效果😂
    auto sprite = Sprite::create("tmp_capture.png");
    addChild(sprite, -1);
    auto size = Director::getInstance()->getWinSize();
    auto scale = size.width/Director::getInstance()->getOpenGLView()->getFrameSize().width;
    sprite->setPosition(Vec2(size/2));
    sprite->setScale(scale);
    
    std::string fragSource = FileUtils::getInstance()->getStringFromFile(FileUtils::getInstance()->fullPathForFilename("Shaders/Blur.fsh"));
    auto program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.data());
    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
    sprite->setGLProgramState(glProgramState);
    sprite->getGLProgramState()->setUniformVec2("resolution", sprite->getTexture()->getContentSizeInPixels());
    sprite->getGLProgramState()->setUniformFloat("blurRadius", 10);
    sprite->getGLProgramState()->setUniformFloat("sampleNum", 8.f);
    sprite->schedule([sprite](float) {
        sprite->setSpriteFrame(Sprite::create("tmp_capture.png")->getSpriteFrame());
    }, 1/10, "sprite_schedule_capture");
//    utils::captureScreen([sprite](bool, const std::string& fileName){
//        sprite->setSpriteFrame(Sprite::create(fileName)->getSpriteFrame());
//    }, "tmp_capture.png");
}

void SettingViewHD::setGuangGao(bool flag)
{
    DATA_M->setGuangGao(flag);
    
    if (flag)
    {
        btn_guangGao->loadTextureNormal("ui_switch0.png", Widget::TextureResType::PLIST);
        btn_guangGao->loadTextureDisabled("ui_switch0.png", Widget::TextureResType::PLIST);
        //        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "animation0", false);
    }
    else
    {
        btn_guangGao->loadTextureNormal("ui_switch1.png", Widget::TextureResType::PLIST);
        btn_guangGao->loadTextureDisabled("ui_switch1.png", Widget::TextureResType::PLIST);
        //        UIUtils::playInnerAction(FIND_NODE(Node*, this, "FileNode_music"), "Start", false);
    }
}

void SettingViewHD::onExit()
{
    BaseLayer::onExit();
}
