#ifndef __CACHE_TEST_H__
#define __CACHE_TEST_H__

#include "Cache.h"

#define HP(n) (100.f/(n))

template<typename T>
class CacheNode // 敌机   子弹
	:public CacheObj
{
public:
	friend class Cache<T>;
	static Cache<T>* getCache();// 不写在模板里是为了用这个类调用
	static void deleteCache();
	
	virtual ~CacheNode();
	virtual void onExit();
	CacheNode();
private:
	
	static Cache<T>* s_cache;
};

// 写个管理类  每种子类都有自己对象池。
// 管理类只需要分辨类型即可
template<typename T>
Cache<T>* CacheNode<T>::s_cache;

template<typename T>
Cache<T>* CacheNode<T>::getCache()
{
	if (!s_cache)s_cache = new Cache<T>();
	return s_cache;
}

template<typename T>
void CacheNode<T>::deleteCache()
{
	if (s_cache)
		delete s_cache;
	s_cache = NULL;
}

template<typename T>
CacheNode<T>::CacheNode()
{
}

template<typename T>
CacheNode<T>::~CacheNode()
{
}

template<typename T>
inline void CacheNode<T>::onExit()
{
	if (!m_bInCache)
	{
		if (s_cache)
		{
			s_cache->deleteOnExit(this);
		}
	}
	CacheObj::onExit();
}

class CacheTest 
	:public CacheNode<CacheTest>
{
public:
	virtual bool init() 
	{// 只调用一次
		CacheNode<CacheTest>::init(); 
		m_bInit = true;
		m_count = 0;
		//cacheInit();  createCacheNode 里面自动调用
		return true;
	}
	virtual void cacheInit()
	{// 可重复调用的。
		if (m_bInit)
		{
			m_bInit = false;
			m_pLabel =
				CCLabelTTF::create("label", "", 32);
			this->addChild(m_pLabel, 1, 1);
		}
		if (m_pLabel)
		{
			++m_count;
			CCString*p = CCString::createWithFormat("%d", m_count);
			m_pLabel->setString(p->getCString());
		}
	}
protected:
	bool m_bInit;
	CCLabelTTF* m_pLabel;
	int m_count;
};

#endif