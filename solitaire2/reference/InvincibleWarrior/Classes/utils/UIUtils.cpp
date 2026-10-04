#include <string>
#include "UIUtils.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "DataManager.h"
#include "SceneManager.h"
#include "PlayerManager.h"
#endif
#include "FeedBackView.h"
#include "extensions/cocos-ext.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "xxtea/xxtea.h"
#include <zlib.h>
#include "DBManager.h"
#include "PlayerManager.h"
#include "DailyManager.h"
#define TEST_SERVER 0
#if TEST_SERVER
#define SERVER_ADDR "localhost"
#else
#define SERVER_ADDR "api.spacecat.top"
#endif

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::network;

//处理
Node* UIUtils::seekNodeByTag(Node* root, int tag){ 
    if (!root) 
    { 
        return nullptr; 
    } 
    if (root->getTag() == tag) 
    { 
        return root; 
    } 
    const auto& arrayRootChildren = root->getChildren(); 
    ssize_t length = arrayRootChildren.size(); 
    for (ssize_t i=0;i<length;i++) 
    { 
        Node* child = dynamic_cast<Node*>(arrayRootChildren.at(i)); 
        if (child) 
        { 
			Node* res = seekNodeByTag(child,tag); 
            if (res != nullptr) 
            { 
                return res; 
            } 
		}
    } 
    return nullptr; 
} 
Node* UIUtils::seekNodeByName(Node* root, const std::string& name) 
{ 
    if (!root) 
    { 
        return nullptr; 
    } 
    if (root->getName() == name) 
    { 
        return root; 
    } 
    const auto& arrayRootChildren = root->getChildren(); 
    for (auto& subWidget : arrayRootChildren) 
    { 
        Node* child = dynamic_cast<Node*>(subWidget); 
        if (child) 
        { 
			Node* res = seekNodeByName(child,name); 
            if (res != nullptr) 
            { 
                return res; 
            } 
        } 
    } 
    return nullptr; 
}

void UIUtils::showShakeAction(Node * target,float scale,bool isRepeat)
{
	target->stopAllActions();
	Sequence* seq = CCSequence::create(
		ScaleTo::create(0.2f, scale - 0.03f, scale + 0.03f),
		ScaleTo::create(0.2f, scale),
		ScaleTo::create(0.2f, scale + 0.03f, scale - 0.03f),
		ScaleTo::create(0.2f, scale),
		ScaleTo::create(0.2f, scale - 0.03f, scale + 0.03f),
		ScaleTo::create(0.2f, scale),
		ScaleTo::create(0.2f, scale + 0.03f, scale - 0.03f),
		ScaleTo::create(0.2f, scale),
		//CCScaleTo::create(0.1f,1.0f, 1.0f),
		CallFunc::create([target,scale]{
		target->setScale(scale);
	}),
		NULL);
	RepeatForever* forever = RepeatForever::create(seq);
	if (isRepeat)
	{
		target->runAction(forever);
	}
	else
	{
		target->runAction(seq);
	}
}

Scene * UIUtils::createScene(Node * layer)
{
	auto scene = Scene::create();
	layer->setName("MyLayer");
	scene->addChild(layer);
	return scene;
}

//弹窗显示动画 --- 
void UIUtils::runShowAction(Node* xx)
{
	xx->getParent()->setVisible(true);
	xx->setScale(0);
	xx->setVisible(true);
	xx->runAction(Sequence::create(EaseBounceOut::create(ScaleTo::create(0.8, 1)), NULL));

}

void UIUtils::runEaseBounceAction(Node * xx)
{
	xx->setScaleX(0);
	//添加动画
	xx->runAction(Sequence::create(DelayTime::create(0.4), EaseBounceOut::create(ScaleTo::create(1, 1, 1)), NULL));
}

void UIUtils::showDialog(Node * root, const std::string& childName, float dalayTime)
{
	auto child = root->getChildByName(childName);
	if (child == NULL)
	{
		return;
	}
	if (child->isVisible() == false)
	{
		child->setVisible(true);
	}
	child->setScale(1.2);
	child->setOpacity(120);
	root->setOpacity(0);
	child->runAction(Spawn::create(EaseBackOut::create(ScaleTo::create(dalayTime, 1)), FadeIn::create(dalayTime), NULL));
	root->setVisible(true);
	root->runAction(Sequence::create(FadeIn::create(dalayTime), NULL));
}



void UIUtils::hideDialog(Node * root, const std::string & childName,float dalayTime)
{
	auto child = root->getChildByName(childName);
	if (child == NULL)
	{
		return;
	}
	child->setScale(1);
	child->runAction(Sequence::create(Spawn::create(ScaleTo::create(dalayTime, 1.2), FadeOut::create(dalayTime), NULL),  NULL));
	root->runAction(Sequence::create(FadeOut::create(dalayTime), CallFunc::create([root]{
		root->setVisible(false);
	}), NULL));
}

void UIUtils::hideDialogByMove(Node * root, const std::string & childName, Point delayPos, float dalayTime)
{
	auto child = root->getChildByName(childName);
	if (child == NULL)
	{
		return;
	}
	child->runAction(Sequence::create(MoveTo::create(dalayTime, Point(delayPos.x, delayPos.y)), CallFunc::create([root]{
		root->setVisible(false);
	}), NULL));
}

void UIUtils::showDialogByMove(Node * root, const std::string& childName, Point delayPos, float dalayTime)
{
	auto child = root->getChildByName(childName);
	if (child == NULL)
	{
		return;
	}
	child->runAction(Sequence::create(MoveTo::create(dalayTime, Point(delayPos.x, delayPos.y)), CallFunc::create([root]{
		//root->setVisible(false);
	}), NULL));
}

//弹窗动画 --- 
void UIUtils::runShowCloseAction(Node* xx, Node * root)
{
	xx->runAction(Sequence::create(ScaleTo::create(0.1, 0), DelayTime::create(0.2), CallFunc::create([xx, root]{
		xx->getParent()->setVisible(false);
		xx->setVisible(false);
		//xx->getParent()->removeFromParent();
		xx->getParent()->removeFromParentAndCleanup(true);
		if (nullptr != root)
		{
			//这样能强力销毁界面
			root->removeFromParentAndCleanup(true);
		}
	}), NULL));
}

void UIUtils::playMoveAction(Node * target, Point delayPos)
{
	target->setPosition(target->getPosition()+delayPos);
	target->runAction(EaseElasticOut::create(MoveBy::create(1, Point(-delayPos.x, -delayPos.y))));
}

void UIUtils::playReMoveAction(Node * target, Point delayPos)
{
	target->runAction(MoveBy::create(0.3, Point(delayPos.x, delayPos.y)));
}

Action * UIUtils::getEffectAction(int num, char* fileNames[], float time,bool isLoop)
{
	Vector<SpriteFrame *> spriteFrameVector;
	for (int i = 0; i < num; i++)
	{
		spriteFrameVector.pushBack(LoadPictuerByName(fileNames[i]));
	}
	auto pAnimation = Animation::createWithSpriteFrames(spriteFrameVector, time);
	auto pAnimate = Animate::create(pAnimation);
	if (isLoop)
	{
		return RepeatForever::create(pAnimate);
	}
	else
	{
		return pAnimate;
	}
}

//对按钮进行初始化
Button * UIUtils::initButtonClick(Node * uiRoot, const std::string& name, std::function<void(Ref *)> clickCallback)
{
	auto btn = FIND_NODE(Button *,uiRoot,name);
	btn->addClickEventListener(clickCallback);
	return btn;
}

Button * UIUtils::initButtonTouch(Node * uiRoot, const std::string& name, std::function<void(Ref *, Widget::TouchEventType)> clickCallback)
{
	auto btn = FIND_NODE(Button *, uiRoot, name);
	btn->addTouchEventListener(clickCallback);
	return btn;
}

int UIUtils::getJsonIntData(const char * jsonName, int id, const char * attName)
{
    auto load_str = FileUtils::getInstance()->getStringFromFile(jsonName);
    
    rapidjson::Document d;
//    std::string load_str((const char *)data.getBytes(), data.getSize());
	d.Parse<0>(load_str.c_str());
	if (d.HasParseError())
	{
		return 0;
	}
	if (d.IsArray() && d.Size() >= id)
	{
		const rapidjson::Value &dd = d[id - 1];
		if (dd.IsObject())
		{
			if (dd.HasMember(attName))
			{
				const rapidjson::Value &ddd = dd[attName];
				return ddd.GetInt();
			}
		}
	}
	return 0;
}

int UIUtils::getJsonIntData(const char * jsonName, const char * attName, int defaultValue)
{
    auto load_str = FileUtils::getInstance()->getStringFromFile(jsonName);
        
        rapidjson::Document d;
    //    std::string load_str((const char *)data.getBytes(), data.getSize());
        d.Parse<0>(load_str.c_str());
        if (d.HasParseError())
        {
            return defaultValue;
        }
        if (d.IsObject())
        {
            if (d.HasMember(attName))
            {
                const rapidjson::Value &ddd = d[attName];
                return ddd.GetInt();
            }
        }
        return defaultValue;
}

string UIUtils::getJsonStringData(const char * jsonName, int id, const char * attName)
{
    auto load_str = FileUtils::getInstance()->getStringFromFile(jsonName);
    
    rapidjson::Document d;
//    std::string load_str((const char *)data.getBytes(), data.getSize());
	d.Parse<0>(load_str.c_str());
	if (d.HasParseError())
	{
		return "???";
	}
	if (d.IsArray() && d.Size() >= id)
	{
		const rapidjson::Value &dd = d[id - 1];
		if (dd.IsObject())
		{
			if (dd.HasMember(attName))
			{
				const rapidjson::Value &ddd = dd[attName];
				return ddd.GetString();
			}
		}
	}
    return "default";
}	

Armature * UIUtils::getArmature(char * armatureName)
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo(StringUtils::format("%s.ExportJson", armatureName));
	Armature* armature = Armature::create(armatureName);
	return armature;
}

vector<int> UIUtils::getGameBgPrices()
{
	vector<int> gameBgPrices;
	//读取json
    auto load_str = FileUtils::getInstance()->getStringFromFile("ShopData.json");
    
    rapidjson::Document d;
//    std::string load_str((const char *)data.getBytes(), data.getSize());
	d.Parse<0>(load_str.c_str());
	if (d.HasParseError())
	{
		//解析出错
		CCLOG("解析出现错误");
		return gameBgPrices;
	}
	// 通过[]取成员值,再根据需要转为array,int,double,string  
	const rapidjson::Value &pArray = d["gamebgprice"];

	//是否是数组  
	if (!pArray.IsArray())
		return gameBgPrices;

	for (rapidjson::SizeType i = 0; i < pArray.Size(); i++)
	{
		const rapidjson::Value &p = pArray[i];
		gameBgPrices.push_back(p.GetInt());
	}

	return gameBgPrices;
}

vector<int> UIUtils::getCardFacePrices()
{
	vector<int> cardFacePrices;
	//读取json
    auto load_str = FileUtils::getInstance()->getStringFromFile("ShopData.json");

	rapidjson::Document d;
//    std::string load_str((const char *)data.getBytes(), data.getSize());
	d.Parse<0>(load_str.c_str());
	if (d.HasParseError())
	{
		//解析出错
		CCLOG("解析出现错误");
		return cardFacePrices;
	}
	// 通过[]取成员值,再根据需要转为array,int,double,string  
	const rapidjson::Value &pArray = d["cardfaceprice"];

	//是否是数组  
	if (!pArray.IsArray())
		return cardFacePrices;

	for (rapidjson::SizeType i = 0; i < pArray.Size(); i++)
	{
		const rapidjson::Value &p = pArray[i];
		cardFacePrices.push_back(p.GetInt());
	}

	return cardFacePrices;
}

vector<int> UIUtils::getCardBgPrices()
{
	vector<int> cardBgPricesPrices;
	//读取json
	ssize_t size = 0;
    auto load_str = FileUtils::getInstance()->getStringFromFile("ShopData.json");
    
    rapidjson::Document d;
//    std::string load_str((const char *)data.getBytes(), data.getSize());
	d.Parse<0>(load_str.c_str());
	if (d.HasParseError())
	{
		//解析出错
		CCLOG("解析出现错误");
		return cardBgPricesPrices;
	}
	// 通过[]取成员值,再根据需要转为array,int,double,string  
	const rapidjson::Value &pArray = d["cardbgprice"];

	//是否是数组  
	if (!pArray.IsArray())
		return cardBgPricesPrices;

	for (rapidjson::SizeType i = 0; i < pArray.Size(); i++)
	{
		const rapidjson::Value &p = pArray[i];
		cardBgPricesPrices.push_back(p.GetInt());
	}

	return cardBgPricesPrices;
}

static shared_ptr<rapidjson::Document> s_langDoc = nullptr;
void UIUtils::reloadLangFile()
{
    //读取json
    const char* languageCode;
    auto fileN = DATA_M->getDyyStr();//
    if(fileN == "1")
    {//第一次登陆 读取设备语言
        languageCode = Application::getInstance()->getCurrentLanguageCode();
        DATA_M->setDyyNum(languageCode);//设置当前语言 如果是没有配置语言则改为英语,仅在第一次登陆设置
    }
    else
    {//随后登陆读取设置语言
        languageCode = fileN.c_str();
    }
    //
    //auto languageCode = Application::getInstance()->getCurrentLanguageCode();
    auto languageFileName = StringUtils::format("strings_%s.json", languageCode);
    if (!FileUtils::getInstance()->isFileExist(languageFileName))
    {
        languageFileName = "strings.json";
    }
    auto load_str = FileUtils::getInstance()->getStringFromFile(languageFileName);
    s_langDoc = std::make_shared<rapidjson::Document>();
    s_langDoc->Parse<0>(load_str.c_str());
#if (COCOS2D_DEBUG>0)
    for (auto it = s_langDoc->GetObject().begin(); it!=s_langDoc->GetObject().end();it++) {
        CCLOG("lang:%s k:%s_v:%s", languageCode, it->name.GetString(), it->value.GetString());
    }
#endif
}

string UIUtils::getStringByName(const string &name)
{
    if (s_langDoc == nullptr) {
        reloadLangFile();
    }
	
    if (s_langDoc->HasParseError())
    {
        //解析出错
        CCLOG("解析出现错误");
        return "error";
    }
	// 通过[]取成员值,再根据需要转为array,int,double,string
	if (s_langDoc->HasMember(name.c_str()))
		return (*s_langDoc)[name.c_str()].GetString();
    else {
#if (COCOS2D_DEBUG>0)
		return name;
#else
		return "default";
#endif
    }
}

void dumpJsonArray(const rapidjson::Value &doc)
{
    auto array = doc.GetArray();
    for (int i=0; i<array.Size(); i++) {
        CCLOG("[DumpJson]i k:%d", i);
        UIUtils::dumpJsonValue(array[i]);
    }
}

void UIUtils::dumpJsonValue(const rapidjson::Value &value)
{
    switch (value.GetType()) {
        case rapidjson::kStringType:
            CCLOG("[DumpJson]str k:%s_v:-1-", value.GetString());
            break;
        case rapidjson::kNumberType:
            CCLOG("[DumpJson]num k:%d_v:-1-", value.GetInt());
            break;
        case rapidjson::kArrayType:
//            CCLOG("[DumpJson] k:%s", value.GetString());
            dumpJsonArray(value);
            break;
        case rapidjson::kObjectType:
//            CCLOG("[DumpJson] k:%s", value.GetString());
            for (auto it = value.GetObject().begin(); it!=value.GetObject().end();it++) {
                CCLOG("[DumpJson]key k:%s", it->name.GetString());
                dumpJsonValue(it->value);
            }
            break;
        default:
            break;
    }
}

void UIUtils::dumpJson(const rapidjson::Document &doc)
{
#if (COCOS2D_DEBUG>0)
    dumpJsonValue(doc);
#endif
}

void UIUtils::updateString()
{
    string languageCode = DATA_M->getDyyStr();
//        languageCode="ar"; //
    auto languageFileName = StringUtils::format("strings_%s.json", languageCode.c_str());
    if (!FileUtils::getInstance()->isFileExist(languageFileName))
    {
        languageFileName = "strings.json";
    }
    auto load_str = FileUtils::getInstance()->getStringFromFile(languageFileName);
    s_langDoc = std::make_shared<rapidjson::Document>();
    s_langDoc->Parse<0>(load_str.c_str());
            
}

void UIUtils::showDialog(Node *root, const std::string &childName, const string aniName, bool loop) {
	auto child = FIND_NODE(Node*,root,childName);
	if (child == NULL)
	{
		return;
	}
	if (child->isVisible() == false)
	{
		child->setVisible(true);
	}

	auto actionManager = reinterpret_cast<cocostudio::timeline::ActionTimeline *>(child->getActionByTag(child->getTag()));
	if (actionManager)
    {
        actionManager->setLastFrameCallFunc([child](){
//            child->setVisible(false);
        });
		actionManager->play(aniName, loop);
    }
}

void UIUtils::hideDialog(Node *root, const std::string &childName, const string aniName, bool loop) {
	auto child = FIND_NODE(Node*,root,childName);
	if (child == NULL)
	{
		return;
	}

	auto actionManager = dynamic_cast<cocostudio::timeline::ActionTimeline *>(child->getActionByTag(child->getTag()));
	if (actionManager) {
		actionManager->setLastFrameCallFunc([child](){
			child->setVisible(false);
		});
		actionManager->play(aniName, loop);
	}
}

cocostudio::timeline::ActionTimeline* UIUtils::playInnerAction(Node *child, const string &name, bool loop, std::function<void()> cb) {
	auto actionManager = dynamic_cast<cocostudio::timeline::ActionTimeline *>(child->getActionByTag(child->getTag()));
    CCLOG("[WTF]innerPlay:%s loop:%d cb:%ld", name.c_str(), loop, &cb);
	if (actionManager) {
        if (cb) {
            actionManager->clearFrameEndCallFuncs();
			actionManager->setLastFrameCallFunc(cb);
        }
		actionManager->play(name, loop);
	}
    return actionManager;
}

cocostudio::timeline::ActionTimeline* UIUtils::playAction(Node *child, const string &name, bool loop, std::function<void()> cb) {
    auto actionManager = dynamic_cast<cocostudio::timeline::ActionTimeline *>(child->getActionByTag(child->getTag()));
    if (actionManager) {
        actionManager->play(name, loop);
        if (cb) {
            auto startFrame = actionManager->getStartFrame();
            auto endFrame = actionManager->getEndFrame();
            //所需时间
            float actionTime = 1.0f/60.0f * (endFrame-startFrame);
            auto delay = DelayTime::create(actionTime);
            auto func = CallFunc::create([cb](){
                cb();
            });
            auto seq = Sequence::createWithTwoActions(delay,func);
            child->runAction(seq);
        }
    }
    return actionManager;
}

void UIUtils::removeLastFrameFunc(Node* child) {
    auto actionManager = dynamic_cast<cocostudio::timeline::ActionTimeline *>(child->getActionByTag(child->getTag()));
    if (actionManager) {
        actionManager->setLastFrameCallFunc(nullptr);
    }
}

Node *UIUtils::createCSBNode(const std::string &csbName, const std::string &aniName, bool loop, std::function<void()> cb)
{
	auto node = CSLoader::createNode(csbName);
	auto actionManager = cocostudio::timeline::ActionTimelineCache::createAction(csbName);
	node->runAction(actionManager);
	actionManager->setTag(10086);
    node->setTag(10086);

	if (aniName != "")
	{
        if (cb)
            actionManager->setLastFrameCallFunc(cb);
		actionManager->play(aniName, loop);
	}
	return node;
}

std::vector<std::string> &UIUtils::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

void UIUtils::updateScore(int p1, int p2) {
    auto fashTankIdx = DATA_M->getCurrentFashTankIdx();
    auto lv = PlayerManager::getInstance()->getLevel();
    auto name = DATA_M->getMyName();
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    
    log("updateScore: %d",lv);
	JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "setUserScore", p1, p2, lv,fashTankIdx,name);
#else
    DB_M->setUser(p1,p2,lv,fashTankIdx,name);
#endif
    
}

void UIUtils::updateRank(int p) {
    //p == 1 是单张
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "updateRank", p);
#else
//    auto contents = FileUtils::getInstance()->getStringFromFile("data/rank_test.json");
//    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("jni_event_custom_callcppwithstring", (void*)__String::create(contents.c_str()));
    DB_M->getRank(p == 1?"p1":"p2");
#endif
}

std::string UIUtils::getName() {
    std::string name{"Player"};
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    name = JniHelper::callStaticStringMethod("org/cocos2dx/cpp/AppActivity", "getName");
#else
    DB_M->getMe();
#endif
    return name;
}

int UIUtils::getP1() {
    int p1 = 0;
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    p1 = JniHelper::callStaticIntMethod("org/cocos2dx/cpp/AppActivity", "getP1");
#else
    p1 = DB_M->getP1();
#endif
    return p1;
}

int UIUtils::getP2() {
    int p2 = 0;
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    p2 = JniHelper::callStaticIntMethod("org/cocos2dx/cpp/AppActivity", "getP2");
#else
    DB_M->getP2();
#endif
    return p2;
}

long UIUtils::getDailyTS() {
    long ts = 0;
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    ts = JniHelper::callStaticIntMethod("org/cocos2dx/cpp/AppActivity", "getDailyTS");
#else
    DB_M->getDailyKeyTs();
#endif
    return ts;
}

void UIUtils::FIRAnalyticsEventWithPrefix(const std::string &eventName, const std::string &prefix)
{
    ValueMap valueMap;
    string newName{prefix + "_" + eventName};
    CCLOG("FIRAnalyticsEventWithPrefix:%s", newName.c_str());
    UIUtils::FIRAnalyticsEvent(newName, valueMap);
}

void startWrite(rapidjson::Writer<rapidjson::StringBuffer> &writer, const ValueMap &params)
{
    for (auto &it:params)
    {
//        string key = it.first;
        writer.Key(it.first.c_str());
        if (it.second.getType() == Value::Type::STRING)
        {
            writer.String(it.second.asString().c_str());
        }
        else if (it.second.getType() == Value::Type::INTEGER)
        {
            writer.Int(it.second.asInt());
        }
        else if (it.second.getType() == Value::Type::BOOLEAN)
        {
            writer.Bool(it.second.asBool());
        }
        else if (it.second.getType() == Value::Type::DOUBLE)
        {
            writer.Double(it.second.asDouble());
        }
        else if (it.second.getType() == Value::Type::VECTOR)
        {
            writer.StartArray();
            for (auto xx: it.second.asValueVector()) {
                writer.StartObject();
                startWrite(writer, xx.asValueMap());
                writer.EndObject();
            }
            writer.EndArray();
        }
        else
        {
            writer.String(it.second.asString().c_str());
        }
    }
}

string convertValueMapToJson(const ValueMap &params)
{
    // 转成字符串https://blog.csdn.net/qq849635649/article/details/52678822
    rapidjson::StringBuffer strBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
    
    writer.StartObject();
    startWrite(writer, params);
    writer.Key("ad");
    writer.String(UIUtils::getAD().c_str());
    writer.Key("ver");
	writer.String(UIUtils::getVersion().c_str());
    writer.Key("ver_code");
    writer.String(UIUtils::getVersionCode().c_str());
    writer.Key("pn");
    writer.String(UIUtils::getPackageName().c_str());
    writer.EndObject();
    
    return strBuffer.GetString();
}

string convertValueMapToJsonSimple(const ValueMap &params)
{
    // 转成字符串https://blog.csdn.net/qq849635649/article/details/52678822
    rapidjson::StringBuffer strBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
    
    writer.StartObject();
    startWrite(writer, params);
    writer.EndObject();
    
    return strBuffer.GetString();
}

string convertValueMapToJsonCloud(int &ll)
{
    // 转成字符串https://blog.csdn.net/qq849635649/article/details/52678822
    rapidjson::StringBuffer strBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
    
    writer.StartObject();
    ll = DailyManager::getInstance()->getLogs(writer);
    writer.Key("ad");
    writer.String(UIUtils::getAD().c_str());
    writer.Key("ver");
    writer.String(UIUtils::getVersion().c_str());
    writer.Key("ver_code");
    writer.String(UIUtils::getVersionCode().c_str());
    writer.Key("pn");
    writer.String(UIUtils::getPackageName().c_str());
    writer.EndObject();
    
    return strBuffer.GetString();
}

std::string compress(const std::string &data)
{
    unsigned char* buf = nullptr;
    uLong tlen = data.length();
    
    /* 计算缓冲区大小，并为其分配内存 */
    auto blen = compressBound(tlen); /* 压缩后的长度是不会超过blen的 */
    
    if((buf = (unsigned char*)malloc(sizeof(unsigned char) * blen)) == NULL)
    {
        printf("no enough memory!\n");
        return "Error";
    }
    
    /* 压缩 */
    if(::compress(buf, &blen, (const unsigned char *)data.data(), tlen) != Z_OK)
    {
        printf("compress failed!\n");
        CC_SAFE_FREE(buf);
        return "Error";
    }
    
    std::string res = std::string((char*)buf, blen);
    CC_SAFE_FREE(buf);
    return res;
}
const auto DestBufferSize = 1024*200;
const std::string CompressHead = "~{AA|BB}";
std::string uncompress(const std::string &data)
{
    unsigned char *buffer = (unsigned char *)data.data();
    unsigned long length = data.length();
    
    /* 计算缓冲区大小，并为其分配内存 */
    unsigned char buf[DestBufferSize];
    
    unsigned long realLength = DestBufferSize;
    auto ok = ::uncompress(buf, &realLength, buffer, length);
    if(ok != Z_OK)
    {
        printf("uncompress failed!\n");
        return "";
    }
    
    std::string res((char*)buf, realLength);
    return res;
}

void UIUtils::httpPost(const std::string &url, const ValueMap &params, const ccHttpRequestCallback& callback, const std::string &tag)
{
    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl(url);
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback(callback);
    std::string postData = convertValueMapToJson(params).c_str();
    static const char* key = "123456";
    static const ssize_t keyLen = strlen(key);
    xxtea_long retLen = 0;
    
    std::string compressedData = CompressHead+compress(postData);
    unsigned char* dataBytes = (unsigned char*)compressedData.c_str();
    unsigned char* retData = xxtea_encrypt(dataBytes, xxtea_long(postData.length()), (unsigned char*)key, xxtea_long(keyLen), &retLen);
    request->setRequestData((char*)retData, retLen);
    request->setTag("httpPost");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    free(retData);
}

void UIUtils::FIRFirestoreAddOP(const std::string &key, const std::string &value, const std::string &v1, const std::string &v2, const std::string &v3, const std::string &v4, const std::string &v5, const std::string &v6, const std::string &v7, const std::string &v8, const std::string &v9, const std::string &v10)
{
    ValueMap valueMap{
        {"key",Value(key)},
    };
    if (value != "") valueMap["value"] = Value(value);
    if (v1 != "") valueMap["v1"] = Value(v1);
    if (v2 != "") valueMap["v2"] = Value(v2);
    if (v3 != "") valueMap["v3"] = Value(v3);
    if (v4 != "") valueMap["v4"] = Value(v4);
    if (v5 != "") valueMap["v5"] = Value(v5);
    if (v6 != "") valueMap["v6"] = Value(v6);
    if (v7 != "") valueMap["v7"] = Value(v7);
    if (v8 != "") valueMap["v8"] = Value(v8);
    if (v9 != "") valueMap["v9"] = Value(v9);
    if (v10 != "") valueMap["v10"] = Value(toString(DATA_M->getCoinNum()));
    UIUtils::FIRFirestoreAdd("operator", valueMap);
}

void UIUtils::FIRFirestoreAddLocal(const std::string &method, const ValueMap &params) {
    DailyManager::getInstance()->insertLog(method, convertValueMapToJsonSimple(params));
}

void UIUtils::FIRFirestoreAddCloud(std::function<void(HttpClient* client, HttpResponse* response)> cb) {
    // write the post data
    int ll = 0;
    std::string postData = convertValueMapToJsonCloud(ll).c_str();
    if (ll == 0) return; // 没有数据 暂时不需要上报
    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl("http://" + string(SERVER_ADDR) + ":8090/al");
//    request->setUrl("http://api.spacecat.top:8090/" + method);
//    request->setUrl("http://192.168.2.245:8090/" + method);
    request->setRequestType(HttpRequest::Type::POST);
    std::vector<std::string> headers;
//    headers.push_back("Content-Type: application/json; charset=utf-8");
//    headers.push_back("Tea: BABA");
    request->setHeaders(headers);
    request->setResponseCallback(cb?cb:[](HttpClient* client, HttpResponse* response){
        CCLOG("log cloud res code:%ld", response->getResponseCode());
    });
    CCLOG("log cloud compress before: %ld", postData.size());
    std::string compressedData = CompressHead+compress(postData);
    CCLOG("log cloud compress after: %ld", compressedData.size());
    static const char* key = "123456";
    static const ssize_t keyLen = strlen(key);
    xxtea_long retLen = 0;
    unsigned char* dataBytes = (unsigned char*)compressedData.c_str();
    unsigned char* retData = xxtea_encrypt(dataBytes, xxtea_long(compressedData.length()), (unsigned char*)key, xxtea_long(keyLen), &retLen);
    CCLOG("log cloud compress encrypt after: %ld", retLen);
    request->setRequestData((char*)retData, retLen);
    request->setTag("POSTFireData");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    free(retData);
}

void UIUtils::FIRFirestoreAdd(const std::string &method, const ValueMap &params, std::function<void(HttpClient* client, HttpResponse* response)> cb)
{
    if (method != "update") {
        return FIRFirestoreAddLocal(method, params);
    }
    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl("http://" + string(SERVER_ADDR) + ":8090/" + method);
//    request->setUrl("http://api.spacecat.top:8090/" + method);
//    request->setUrl("http://192.168.2.245:8090/" + method);
    request->setRequestType(HttpRequest::Type::POST);
    std::vector<std::string> headers;
//    headers.push_back("Content-Type: application/json; charset=utf-8");
//    headers.push_back("Tea: BABA");
    request->setHeaders(headers);
    request->setResponseCallback(cb?cb:[](HttpClient* client, HttpResponse* response){
        CCLOG("res code:%ld", response->getResponseCode());
    });
    
    // write the post data
    std::string postData = convertValueMapToJson(params).c_str();
    std::string compressedData = CompressHead+compress(postData);
    static const char* key = "123456";
    static const ssize_t keyLen = strlen(key);
    xxtea_long retLen = 0;
    unsigned char* dataBytes = (unsigned char*)compressedData.c_str();
    unsigned char* retData = xxtea_encrypt(dataBytes, xxtea_long(compressedData.length()), (unsigned char*)key, xxtea_long(keyLen), &retLen);
    request->setRequestData((char*)retData, retLen);
    request->setTag("POSTFireData");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    free(retData);
}

void UIUtils::RequestCK(const std::string &method, const ValueMap &params, std::function<void(HttpClient* client, HttpResponse* response)> cb)
{
    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl("http://" + string(SERVER_ADDR) + ":8095/" + method);
    request->setRequestType(HttpRequest::Type::POST);
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
//    headers.push_back("Tea: BABA");
    request->setHeaders(headers);
    request->setResponseCallback(cb?cb:[](HttpClient* client, HttpResponse* response){
        CCLOG("ck res code:%ld", response->getResponseCode());
    });
    
    std::string postData = convertValueMapToJsonSimple(params).c_str();
    request->setRequestData(postData.c_str(), postData.length());
    request->setTag("RequestCK");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
}

bool UIUtils::bannerLoaded()
{
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    JniMethodInfo t;
    bool ret = false;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "isBannerLoaded", "()Z")) {
        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
    }
    return ret;
#endif
    return false;
}

float UIUtils::getDensity() {
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
	JniMethodInfo t;
	float ret = 1;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "getDensity", "()F")) {
		ret = t.env->CallStaticFloatMethod(t.classID, t.methodID);
	}
	return ret;
#endif
	return 1;
}

#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
bool UIUtils::getFirConfig(const std::string &key)
{
    return JniHelper::callStaticBooleanMethod("org/cocos2dx/cpp/AppActivity", "getRemoteConfigValue", key);
}

void UIUtils::requestReview() {
    auto cnt = DATA_M->getAppStartCNT();
    if (cnt >= 5 && cnt % 5 ==0)
    {
//        auto flag = UserDefault::getInstance()->getBoolForKey("feedback_flag", false);
//        if (!flag) {
//            SCENE_M->addDialog(FeedBackView::createLayerN());
//        }
		JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "showRate");
    }
}

int UIUtils::getNetworkState() {
    JniMethodInfo t;
    bool ret = false;
//    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/NetWorkUtils", "isMobileConnected", "()Z")) {
//        ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
//
//    }
    return ret?0:1;
}

void UIUtils::FIRAnalyticsEvent(const std::string &eventName, const ValueMap &params)
{
    Value value(params);
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "FIRAnalyticsEvent1", "(Ljava/lang/String;Landroid/os/Bundle;)V"))
	{
		JNIEnv *env = t.env;
		jclass targetClass = env->FindClass("android/os/Bundle");
		if (targetClass) {
			jmethodID mid = env->GetMethodID(targetClass, "<init>", "()V");
			jobject newObject = env->NewObject(targetClass, mid);
			if (newObject) {
				for (auto item:params) {
					jstring key = env->NewStringUTF(item.first.c_str());
					switch (item.second.getType()) {
						case Value::Type::INTEGER:
							mid = env->GetMethodID(targetClass, "putInt", "(Ljava/lang/String;I)V");  //找到方法
							env->CallVoidMethod(newObject, mid, key, item.second.asInt());
							break;
						case Value::Type::FLOAT:
							mid = env->GetMethodID(targetClass, "putFloat", "(Ljava/lang/String;F)V");  //找到方法
							env->CallVoidMethod(newObject, mid, key, item.second.asFloat());
							break;
						default:
						{
							mid = env->GetMethodID(targetClass, "putString", "(Ljava/lang/String;Ljava/lang/String;)V");  //找到方法
							jstring value = env->NewStringUTF(item.second.asString().c_str());
							env->CallVoidMethod(newObject, mid, key, value);
						}
							break;
					}
				}
			}
//			JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "FIRAnalyticsEvent1", eventName, newObject);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, env->NewStringUTF(eventName.c_str()), newObject);
			t.env->DeleteLocalRef(t.classID);
		}
	}
}

void UIUtils::FIRAnalyticsUserProperty(const std::string &key, const std::string &property)
{
	JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "FIRAnalyticsUserProperty", key, property);
}

void UIUtils::FIRFirestoreAdd(const std::string &bureau, bool win, int btype, int ptype)
{
    auto idx = UserDefault::getInstance()->getIntegerForKey("xxkey_cnt", 0);
    JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "FIRFirestoreAdd", idx, bureau, win, btype, ptype);
    UserDefault::getInstance()->setIntegerForKey("xxkey_cnt", ++idx);
}

void UIUtils::openMail() {

}

void UIUtils::shareApp() {
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "shareApp", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void UIUtils::writComment() {
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "jumpToComment", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void UIUtils::showSetting()
{
    
}

void UIUtils::registNotify(float time, const std::string& key, const std::string& content, bool isDelay) {

}

void UIUtils::unregistNotify(const std::string& key) {

}

std::string UIUtils::getDeviceModel(){
    return JniHelper::callStaticStringMethod("org/cocos2dx/cpp/AppActivity", "getDeviceModel");
}

std::string UIUtils::getUtcTimeZone()
{
    return JniHelper::callStaticStringMethod("org/cocos2dx/cpp/AppActivity", "getUtcTimeZone");
}

std::string UIUtils::getAD()
{
//    getAndroidID
    return JniHelper::callStaticStringMethod("org/cocos2dx/cpp/AppActivity", "getAndroidID");
}

std::string UIUtils::getVersion()
{
    return JniHelper::callStaticStringMethod("org/cocos2dx/cpp/AppActivity", "getVersionCode");
}

std::string UIUtils::getVersionCode()
{
	return "";
}

std::string UIUtils::getPackageName()
{
	return getPackageNameJNI();
}

bool UIUtils::hasInterstitial()
{
    return JniHelper::callStaticBooleanMethod("org/cocos2dx/cpp/AppActivity", "hasInterstitial");
}

void UIUtils::FIRAnalyticsTrackScreens(const std::string &name) {

}

void UIUtils::appStartEnd(bool loadingEnd) {
	JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", loadingEnd?"appStartEnd1":"appStartEnd");
}

#define TEST_IAP 0
void UIUtils::calIAP(const std::string &id, bool isSub) {
#if (TEST_IAP==1 && COCOS2D_DEBUG>0)
	auto date = StringUtils::format("{\"orderId\":\"GPA.3363-0565-2774-55761\",\"packageName\":\"com.cn.spacecate.solitaire2k\",\"productId\":\"%s\",\"purchaseTime\":1622189494132,\"purchaseState\":0,\"purchaseToken\":\"gmlppegnelimbgghilbjnglj.AO-J1OyhKExzbkE2DkcHZBlJS-3i5AB8DLMjun4zPxOvMkeA7Z98UHF2g2VdUxUqPdZa3oEWAWbEv8uGGJ1DQDuz2BDcA2Qx36u1GP6XOD63Sd3j9KXzUIY\",\"acknowledged\":false,\"msg\":\"game_purchase\"}", id.c_str());
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("jni_event_custom_callcppwithstring", (void*)__String::create(date.c_str()));
#else
	JniHelper::callStaticVoidMethod("org/cocos2dx/cpp/AppActivity", "calIAP", id, isSub);
#endif
}

std::string UIUtils::getProduct(const std::string &id) {
	return JniHelper::callStaticStringMethod("org/cocos2dx/cpp/AppActivity", "getProduct", id);
}
#endif


void UIUtils::textAdaptiveSize(Text* text,float maxWidth)
{
    return;
    text->setScale(1);
    auto size = text->getBoundingBox().size;
    if(size.width > maxWidth)
    {
        auto scale = maxWidth/size.width;
        text->setScale(scale);
    }
}

Color3B UIUtils::getCardColor(int ColType)
{
    if(ColType == 0||ColType == 2)
    {
        return Color3B::BLACK;
    }
    else if(ColType == 1||ColType == 3)
    {
        return Color3B::RED;
    }
    return Color3B::BLACK;
}

/// <summary>
/// Catmull-Rom 曲线插值
/// </summary>
/// <param name="p0"></param>
/// <param name="p1"></param>
/// <param name="p2"></param>
/// <param name="p3"></param>
/// <param name="t">0-1</param>
/// <returns></returns>
Vec2 UIUtils::CatmullRomPoint(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, float t)
{
    return p1 + (0.5f * (p2 - p0) * t) + 0.5f * (2.f * p0 - 5.f * p1 + 4.f * p2 - p3) * t * t +
            0.5f * (-p0 + 3.f * p1 - 3.f * p2 + p3) * t * t * t;
}

int UIUtils::myrandom (int i)
{
    return std::rand()%i;
}

vector<string> UIUtils::split(const string& src, const string& separator)
{
    vector<string> dest;
    string str = src;
    string substring;
    string::size_type start = 0, index;

    do
    {
        index = str.find_first_of(separator,start);

        if (index != string::npos)
        {
            substring = str.substr(start,index-start);
            dest.push_back(substring);
            start = str.find_first_not_of(separator,index);
            if (start == string::npos) return dest;
        }
    }while(index != string::npos);

    //the last token
    substring = str.substr(start);
    dest.push_back(substring);
    return dest;
}

float UIUtils::getAngle(Vec2 startP,Vec2 endP)
{
    //计算出朝向
    auto dx = endP.x - startP.x;
    auto dy = endP.y - startP.y;
    auto dir = Vec2(dx,dy);

    
    auto dis = endP - startP;
    float t = Vec2(dis.y, dis.x).getAngle() / 3.14f * 180;//一定注意x和y参数是倒过来的

    return t;
}

Animation* UIUtils::createAni(const char* file,int num,int began,const char* name,int loop,bool flip)
{
    auto ani = AnimationCache::getInstance()->getAnimation(name);
    if(ani)return ani;
    
    ani = Animation::create();
    for(int i = 0; i<num; ++i)
    {
        auto str = StringUtils::format("%s%d",file, i);
        auto texture = Director::getInstance()->getTextureCache()->addImage(str.c_str());
        
        Rect rect;
        rect.size = texture->getContentSize();
        SpriteFrame* frame;
        if(flip)
        {
            auto sprite = Sprite::createWithSpriteFrameName(str.c_str());
            sprite->setFlippedX(flip);
            frame = sprite->getSpriteFrame();
        }
        else
        {
            frame = SpriteFrame::createWithTexture(texture,rect);
        }
        ani->addSpriteFrame(frame);
    }
    ani->setDelayPerUnit(0.1f);
    ani->setLoops(loop);
    ani->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(ani, name);
    return ani;
}
Animation* UIUtils::createAni(const char* plist, const char* file, int num, int began, const char* name, int loop,bool flip)
{
    auto ani = AnimationCache::getInstance()->getAnimation(name);
    if(ani)return ani;
    ani = Animation::create();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
    AnimationCache::getInstance()->addAnimationsWithFile(plist);
    for(int i = 0; i<num; ++i)
    {
        auto str = StringUtils::format("%s%d.png",file,i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str.c_str());
        
        ani->addSpriteFrame(frame);
    }
    ani->setDelayPerUnit(0.1f);
    ani->setLoops(loop);
    ani->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(ani, name);
    return ani;
}
Animation* UIUtils::getAnimation(const char* name)
{
    auto ani = AnimationCache::getInstance()->getAnimation(name);
    return ani;
}

std::string UIUtils::getFloatStr(float num,int weiShu)
{
    auto str = StringUtils::toString(num);
    auto strVec = UIUtils::split(str, ".");
    std::string str2 = "";
    if(strVec.size() == 2)
    {
        std::string str0 = strVec[0];
        std::string str1 = strVec[1];
        if(weiShu > 0)
        {
            str1 = str1.substr(0,weiShu);
            if(str1 == "0")
            {
                str2 = str0;
            }
            else
            {
                str2 = str0 + "." + str1;
            }
        }
        else
        {
            str2 = str0;
        }
    }
    else
    {
        str2 = strVec[0];
    }
    
    return str2;
}

std::string UIUtils::getVersionName() {
    std::string name{"0"};
#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
    name = JniHelper::callStaticStringMethod("org/cocos2dx/cpp/AppActivity", "getVersionName");
#endif
    return name;
}
