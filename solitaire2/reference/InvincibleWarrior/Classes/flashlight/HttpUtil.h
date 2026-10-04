#ifndef __HTTP_UTIL__
#define __HTTP_UTIL__

#include "cocos2d.h"
#include "cocos-ext.h"

#define CC_LUA_ENGINE_ENABLED 0
#if (CC_LUA_ENGINE_ENABLED > 0)
#include "CCLuaEngine.h"
#endif

#include "network/HttpClient.h"

typedef void (cocos2d::Ref::*SEL_RESPONSEHEADERS)(const char*);
typedef void (cocos2d::Ref::*SEL_DATASUCCEED)(const char*, unsigned int);
typedef void (cocos2d::Ref::*SEL_DATAFAILED)(int, const char*);

#define responseheaders_selector(_SELECTOR) (SEL_RESPONSEHEADERS)(&_SELECTOR)
#define datasucceed_selector(_SELECTOR) (SEL_DATASUCCEED)(&_SELECTOR)
#define datafailed_selector(_SELECTOR) (SEL_DATAFAILED)(&_SELECTOR)

class HttpUtil : public cocos2d::Ref
{
public:
    static HttpUtil* create();
    
	HttpUtil();
	virtual ~HttpUtil();

public:
	void setNotifier(cocos2d::Ref* target, SEL_DATASUCCEED succeedSelector, SEL_DATAFAILED failedSelector, SEL_RESPONSEHEADERS headersSelector);
#if (CC_LUA_ENGINE_ENABLED > 0)
    void setListener(cocos2d::LUA_FUNCTION succeedListener, cocos2d::LUA_FUNCTION failedListener);
    void setListener(cocos2d::LUA_FUNCTION succeedListener, cocos2d::LUA_FUNCTION failedListener, cocos2d::LUA_FUNCTION headersListener);
#endif

	void get(const char* url);
    void post(const char* url, const char* data, unsigned int len);
    void post(const char* url, const char* data, unsigned int len, int timeoutForConnect, int timeoutForRead);
    void post(const char* url, const char* data, unsigned int len, int timeoutForConnect, int timeoutForRead, std::vector<std::string> pHeaders);

private:
    void onHttpRequestCompleted(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response);

private:
	cocos2d::Ref*       m_pTarget;
	SEL_DATASUCCEED m_succeedSelector;
	SEL_DATAFAILED m_failedSelector;
	SEL_RESPONSEHEADERS m_headersSelector;
    
#if (CC_LUA_ENGINE_ENABLED > 0)
    int m_iSucceedListener;
    int m_iFailedListener;
    int m_iHeadersListener;
#endif
};

#endif
