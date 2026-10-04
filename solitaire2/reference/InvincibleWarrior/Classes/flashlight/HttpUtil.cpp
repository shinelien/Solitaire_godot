#include "HttpUtil.h"

HttpUtil* HttpUtil::create()
{
    HttpUtil *pRet = new HttpUtil();
    if (pRet)
    {
        return pRet;
    }
    else
    {
        return NULL;
    }
}

HttpUtil::HttpUtil()
{
	this->m_succeedSelector = NULL;
	this->m_failedSelector = NULL;
	this->m_headersSelector = NULL;
#if (CC_LUA_ENGINE_ENABLED > 0)
    this->m_iSucceedListener = 0;
    this->m_iFailedListener = 0;
    this->m_iHeadersListener = 0;
#endif
    this->autorelease();
}

HttpUtil::~HttpUtil()
{
    
}

void HttpUtil::setNotifier(cocos2d::Ref* target, SEL_DATASUCCEED succeedSelector, SEL_DATAFAILED failedSelector, SEL_RESPONSEHEADERS headersSelector)
{
	this->m_pTarget = target;
	this->m_succeedSelector = succeedSelector;
	this->m_failedSelector = failedSelector;
	this->m_headersSelector = headersSelector;
}

#if (CC_LUA_ENGINE_ENABLED > 0)
void HttpUtil::setListener(cocos2d::LUA_FUNCTION succeedListener, cocos2d::LUA_FUNCTION failedListener, cocos2d::LUA_FUNCTION headersListener)
{
    this->m_iSucceedListener = succeedListener;
    this->m_iFailedListener = failedListener;
    this->m_iHeadersListener = headersListener;
}

void HttpUtil::setListener(cocos2d::LUA_FUNCTION succeedListener, cocos2d::LUA_FUNCTION failedListener)
{
    this->m_iSucceedListener = succeedListener;
    this->m_iFailedListener = failedListener;
}
#endif

void HttpUtil::get(const char* url)
{
	cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
	request->setUrl(url);
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(HttpUtil::onHttpRequestCompleted));
	request->setTag("get request");
    cocos2d::network::HttpClient::getInstance()->send(request);
    cocos2d::network::HttpClient::getInstance()->setTimeoutForConnect(10);//设置连接超时时间
    cocos2d::network::HttpClient::getInstance()->setTimeoutForRead(10);//设置发送超时时间
	request->release();
}

void HttpUtil::post(const char* url, const char* data, unsigned int len)
{
	cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
	request->setUrl(url);
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpUtil::onHttpRequestCompleted));

	// write the post data
	request->setRequestData(data, len);

	request->setTag("post request");
	cocos2d::network::HttpClient::getInstance()->send(request);
    cocos2d::network::HttpClient::getInstance()->setTimeoutForConnect(10);//设置连接超时时间
    cocos2d::network::HttpClient::getInstance()->setTimeoutForRead(10);//设置发送超时时间
	request->release();
}

void HttpUtil::post(const char* url, const char* data, unsigned int len, int timeoutForConnect, int timeoutForRead)
{
    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl(url);
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(HttpUtil::onHttpRequestCompleted));
    
    // write the post data
    request->setRequestData(data, len);
    
    request->setTag("post request");
    cocos2d::network::HttpClient::getInstance()->send(request);
    cocos2d::network::HttpClient::getInstance()->setTimeoutForConnect(timeoutForConnect);//设置连接超时时间
    cocos2d::network::HttpClient::getInstance()->setTimeoutForRead(timeoutForRead);//设置发送超时时间
    request->release();
}

void HttpUtil::post(const char* url, const char* data, unsigned int len, int timeoutForConnect, int timeoutForRead, std::vector<std::string> pHeaders)
{
    cocos2d::network::HttpRequest* request = new cocos2d::network::HttpRequest();
    request->setUrl(url);
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    request->setResponseCallback(this, httpresponse_selector(HttpUtil::onHttpRequestCompleted));
    
    request->setHeaders(pHeaders);
    
    // write the post data
    request->setRequestData(data, len);
    
    request->setTag("post request");
    cocos2d::network::HttpClient::getInstance()->send(request);
    cocos2d::network::HttpClient::getInstance()->setTimeoutForConnect(timeoutForConnect);//设置连接超时时间
    cocos2d::network::HttpClient::getInstance()->setTimeoutForRead(timeoutForRead);//设置发送超时时间
    request->release();
}

void HttpUtil::onHttpRequestCompleted(cocos2d::network::HttpClient* client, cocos2d::network::HttpResponse* response)
{
#if (CC_LUA_ENGINE_ENABLED > 0)
    cocos2d::CCLuaStack* stack = cocos2d::CCLuaEngine::defaultEngine()->getLuaStack();
#endif
    
	if (!response)
	{
		if (m_pTarget && m_failedSelector)
		{
			(m_pTarget->*m_failedSelector)(-1, NULL);
		}
#if (CC_LUA_ENGINE_ENABLED > 0)
        if (m_iFailedListener)
        {
            stack->clean();
            stack->pushInt(-1);
            stack->pushCCLuaValue(cocos2d::CCLuaValue::stringValue(response->getErrorBuffer()));
            stack->executeFunctionByHandler(m_iFailedListener, 2);
        }
#endif
		return;
	}

	int statusCode = response->getResponseCode();

	if (!response->isSucceed()) 
	{
		if (m_pTarget && m_failedSelector)
		{
			(m_pTarget->*m_failedSelector)(statusCode, response->getErrorBuffer());
        }
#if (CC_LUA_ENGINE_ENABLED > 0)
        if (m_iFailedListener)
        {
            stack->clean();
            stack->pushInt(statusCode);
            stack->pushCCLuaValue(cocos2d::CCLuaValue::stringValue(response->getErrorBuffer()));
            stack->executeFunctionByHandler(m_iFailedListener, 2);
        }
#endif
		return;
	}

	std::vector<char>* headers = response->getResponseHeader();
	char* headerString = new char[headers->size() + 1]; 
	std::copy(headers->begin(), headers->end(), headerString);
	if (m_pTarget && m_headersSelector)
	{
		(m_pTarget->*m_headersSelector)(headerString);
    }
#if (CC_LUA_ENGINE_ENABLED > 0)
    if (m_iHeadersListener)
    {
        stack->clean();
        stack->pushCCLuaValue(cocos2d::CCLuaValue::stringValue(headerString));
        stack->executeFunctionByHandler(m_iHeadersListener, 1);
    }
#endif

	std::vector<char>* buffer = response->getResponseData();
	char* dataString = new char[buffer->size() + 1]; 
	std::copy(buffer->begin(), buffer->end(), dataString);
	if (m_pTarget && m_succeedSelector)
	{
		(m_pTarget->*m_succeedSelector)(dataString, (unsigned int)buffer->size());
    }
#if (CC_LUA_ENGINE_ENABLED > 0)
    if (m_iSucceedListener)
    {
        stack->clean();
        stack->pushCCLuaValue(cocos2d::CCLuaValue::stringValue(dataString));
        stack->pushInt((int)buffer->size());
        stack->executeFunctionByHandler(m_iSucceedListener, 2);
    }
#endif

	delete []dataString;
	delete []headerString;
}
