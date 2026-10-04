# ifndef __UIUTILS__
# define __UIUTILS__

# include "cocos2d.h"
# include "ui/CocosGUI.h"
# include"cocostudio/CocoStudio.h"
# include "SimpleAudioEngine.h"
# include "xxtea/xxtea.h"
# include "AppConstant.h"
#include "network/HttpClient.h"
#include <unordered_map>

# define PLAYBGMUSIC SimpleAudioEngine::getInstance()->playBackgroundMusic
# define RESUMEBGMUSIC SimpleAudioEngine::getInstance()->resumeBackgroundMusic
# define PLAYEFFECT SimpleAudioEngine::getInstance()->playEffect
# define PAUSEBGMUSIC SimpleAudioEngine::getInstance()->pauseBackgroundMusic
# define STOPBGMUSIC SimpleAudioEngine::getInstance()->stopBackgroundMusic
# define STOPEFFECT SimpleAudioEngine::getInstance()->stopAllEffects
# define PRELOADMUSIC SimpleAudioEngine::getInstance()->preloadBackgroundMusic
# define PRELOADEFFECT SimpleAudioEngine::getInstance()->preloadEffect
# define LoadPictuerByName SpriteFrameCache::getInstance()->getSpriteFrameByName

# define GETFLOAT UserDefault::getInstance()->getFloatForKey
# define SETFLOAT UserDefault::getInstance()->setFloatForKey
# define GETINTEGER UserDefault::getInstance()->getIntegerForKey
# define SETINTEGER UserDefault::getInstance()->setIntegerForKey
# define GETBOOL UserDefault::getInstance()->getBoolForKey
# define SETBOOL UserDefault::getInstance()->setBoolForKey
# define SETSTR UserDefault::getInstance()->setStringForKey
# define GETSTR UserDefault::getInstance()->getStringForKey
# define FLUSH UserDefault::getInstance()->flush
# define DELETEKEY UserDefault::getInstance()->deleteValueForKey

# define FIND_NODE(Type,uiRoot,btnName) dynamic_cast<Type>(UIUtils::seekNodeByName(uiRoot,btnName))
# define INIT_BTN(uiRoot,btnName,func) UIUtils::initButtonClick(uiRoot,btnName,func)
# define INIT_TOUCH_BTN(uiRoot,btnName,func) UIUtils::initButtonTouch(uiRoot,btnName,func)


# define DIRECTOR Director::getInstance()
# define GOTOSCENE(scene) Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)))

#define Lang(key) UIUtils::getStringByName(key)
#define Lang_1(key, value1) StringUtils::format(UIUtils::getStringByName(key).c_str(), value1)
#define Lang_2(key, value1, value2) StringUtils::format(UIUtils::getStringByName(key).c_str(), value1, value2)

//StringUtils::toString
template <typename T> 
std::string toString(const T& value)
{ 
	std::ostringstream oss; 
	oss << value; 
	return oss.str();
}
USING_NS_CC;
using namespace cocostudio;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace cocos2d::network;
using namespace std;


class UIUtils
{
public :
	static Node* seekNodeByTag(Node* root, int tag);
	static Node* seekNodeByName(Node* root, const std::string& name);

	static void showDialog(Node * root, const std::string& childName,float dalayTime = 0.5f);
	static void hideDialog(Node * root, const std::string & childName, float dalayTime = 0.5f);

	static void showDialog(Node * root, const std::string& childName, const string aniName, bool loop);
	static void hideDialog(Node * root, const std::string & childName, const string aniName, bool loop);

    static void showDialogByMove(Node * root, const std::string& childName, cocos2d::Point delayPos, float dalayTime = 0.4f);
	static void hideDialogByMove(Node * root, const std::string & childName, cocos2d::Point delayPos, float dalayTime = 0.4f);//移动移除界面


	static void runShowAction(Node* xx);
	static void runShowCloseAction(Node* xx,Node * root = nullptr);
	static void runEaseBounceAction(Node * xx);
	static Action * getEffectAction(int num, char* fileNames[], float time,bool isLoop = true);

	static int getJsonIntData(const char * jsonName, int id, const char * attName);
	static string getJsonStringData(const char * jsonName, int id, const char * attName);
    static int getJsonIntData(const char * jsonName, const char * attName, int defaultValue = 0);

	static void showShakeAction(Node * target, float scale = 1, bool isRepeat = true);

	static Scene * createScene(Node * layer);

	//对按钮进行初始化
	static Button * initButtonClick(Node * uiRoot, const std::string& name, std::function<void(Ref *)> clickCallback);
	static Button * initButtonTouch(Node * uiRoot, const std::string& name, std::function<void(Ref*, Widget::TouchEventType)> clickCallback);

	//控件播放出现动作
	static void playMoveAction(Node * target,cocos2d::Point delayPos);
	//控件播放移除动作
	static void playReMoveAction(Node * target, cocos2d::Point delayPos);
    inline static int stoii(const std::string &s) { return std::stoi(s.empty()?"0":s); }

	static Armature* getArmature(char * armatureName);
	static vector<int> getGameBgPrices();
	static vector<int> getCardFacePrices();
	static vector<int> getCardBgPrices();

    static void dumpJsonValue(const rapidjson::Value &value);
    static void dumpJson(const rapidjson::Document &doc);
    static void reloadLangFile();
	static string getStringByName(const string &name);
    static void updateString();
	static cocostudio::timeline::ActionTimeline * playInnerAction(Node *child, const string &name, bool loop, std::function<void()> cb = nullptr);
    static cocostudio::timeline::ActionTimeline * playAction(Node *child, const string &name, bool loop, std::function<void()> cb = nullptr);
    static void removeLastFrameFunc(Node* child);
	static Node *createCSBNode(const std::string &csbName, const std::string &aniName = "", bool loop = false, std::function<void()> cb = nullptr);
    static int getNetworkState();
    static void requestReview();
	static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    
    static void httpPost(const std::string &url, const ValueMap &params, const network::ccHttpRequestCallback& callback, const std::string &tag = "httpPost");
    static void FIRAnalyticsEventWithPrefix(const std::string &eventName, const std::string &prefix = "path");
    static void FIRAnalyticsEvent(const std::string &eventName, const ValueMap &params);
    static void FIRAnalyticsUserProperty(const std::string &key, const std::string &property);
    static void FIRAnalyticsTrackScreens(const std::string &name);
    static void appStartEnd(bool loadingEnd = false);
    static void FIRFirestoreAddOP(const std::string &key, const std::string &value = "", const std::string &v1 = "", const std::string &v2 = "", const std::string &v3 = "", const std::string &v4 = "", const std::string &v5 = "", const std::string &v6 = "", const std::string &v7 = "", const std::string &v8 = "", const std::string &v9 = "", const std::string &v10 = "");
    
    static void FIRFirestoreAddLocal(const std::string &method, const ValueMap &params);
    static void FIRFirestoreAddCloud(std::function<void(HttpClient* client, HttpResponse* response)> cb = nullptr);
	static void FIRFirestoreAdd(const std::string &bureau, bool win, int btype, int ptype);
    static void FIRFirestoreAdd(const std::string &method, const ValueMap &params, std::function<void(HttpClient* client, HttpResponse* response)> cb = nullptr);
    static void RequestCK(const std::string &method, const ValueMap &params, std::function<void(HttpClient* client, HttpResponse* response)> cb = nullptr);
    static void calIAP(const std::string &id, bool isSub = false);
	static std::string getProduct(const std::string &id);
    static bool getFirConfig(const std::string &key);
	static std::string sub(const std::string &str,int start,int end);
	static void updateScore(int p1 = 0, int p2 = 0);
    static void updateRank(int p);
    static std::string getName();
    static int getP1();
    static int getP2();
    static long getDailyTS();
    

    static void testCrashlytics();
    static void openMail();
	static void shareApp();
    static void showSetting();
    static void writComment();
    static inline bool IsPad() {
        auto winSize = Director::getInstance()->getWinSize();
        return winSize.height/winSize.width<1.5;
    }
    
    static int clamp(int value, int min_inclusive, int max_inclusive) {
        if (min_inclusive > max_inclusive) {
            std::swap(min_inclusive, max_inclusive);
        }
        return value < min_inclusive ? min_inclusive : value < max_inclusive? value : max_inclusive;
    }
    
    static void registNotify(float time, const std::string& key, const std::string& content, bool isDelay = false);
    static void unregistNotify(const std::string& key);
    static std::string getDeviceModel();
    static std::string getUtcTimeZone();
    static std::string getAD();
    static std::string getVersion();
    static std::string getVersionCode();
    static std::string getPackageName();
    static bool bannerLoaded();
	static float getDensity();
    
    static bool hasInterstitial();
    //文本自适应大小
    static void textAdaptiveSize(Text* text,float maxWidth);
    //根据牌花色返回牌颜色。
    static Color3B getCardColor(int ColType);
    static Vec2 CatmullRomPoint(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, float t);
//private:
//	static std::unordered_map<std::string, rapidjson::Document> sLngMap;
    static int myrandom (int i);
    static  vector<string>  split(const string& src, const string& separator);
    static float getAngle(Vec2 startP,Vec2 endP);
    static Animation* createAni(const char* file,int num,int began,const char* name,int loop,bool flip);
    static Animation* createAni(const char* plist, const char* file, int num, int began, const char* name, int loop,bool flip);
    static Animation* getAnimation(const char* name);
    static std::string getFloatStr(float num,int weiShu);
    static std::string getVersionName();
    static std::string getCountryID();
};
# endif
