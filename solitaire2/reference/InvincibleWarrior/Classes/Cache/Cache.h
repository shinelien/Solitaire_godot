#ifndef __CACHE_H__
#define __CACHE_H__

#include "cocos2d.h"
using namespace cocos2d;
#include <list>
//#include "BaseHead.h"
#include"CreateNode.h"
// 会自动回收到缓冲池中
class CacheObj
	:public Node
{
public:
	virtual void cacheInit() = 0;
	virtual ~CacheObj() 
	{
		--s_count;
	}
	CacheObj():m_bInCache(false)
	{ 
		++s_count;
	}
	
	friend class CacheAssert;
	// 这里不容易获取缓冲池， 不适合在这里写
	//virtual void onExit();
	bool m_bInCache;
private:
	static int s_count;
};

class CacheAssert: public CacheObj
{// 析构函数最后调用 父类析构函数最后调用
	// 所以，用1判断 然后父类析构函数会减去1
public:
	CacheAssert() {}
	~CacheAssert() 
	{ 
		CCAssert(1 == s_count, "Cache mast Clean ");
	}
	virtual void cacheInit() {}
};
// static int n = 3; 不要用此方式，会创建多个
template<typename T>
class Cache
{
public:
	Cache();
	virtual ~Cache();
	void myInit(int num);
	T* createCacheNode(Node* pFather);
	void deleteNode(T* &pNode);
	// 仅用于onExit中
	// 已经从父节点移除， 传入的指针不会置空
	// 因为是个常量
	void deleteOnExit(CacheObj* pNode);
private:
	std::list<T*> m_arr;
};

template<typename T>
Cache<T>::Cache()
{
	//m_arr = CCArray::create();
	//m_arr->retain();
}

template<typename T>
Cache<T>::~Cache()
{
	//m_arr->removeAllObjects();
	//m_arr->release();
	typename std::list<T*>::iterator it = m_arr.begin();
	while (it != m_arr.end())
	{
		T* p = (*it);
		it = m_arr.erase(it);
		p->release();
	}
}

template<typename T>
void Cache<T>::myInit(int num)
{
	//m_arr->initWithCapacity(num);
	for (int i = 0; i < num; ++i)
	{
		T* pNode = createNode<T>();
		//m_arr->addObject(pNode);
		pNode->m_bInCache = true;
		m_arr.push_back(pNode);
		pNode->retain();
	}
}



template<typename T>
T* Cache<T>::createCacheNode(Node* pFather)
{
	T* pNode = NULL;
	if (m_arr.size() > 0)
	{
		//m_arr->randomObject();
		pNode = m_arr.front();
		pFather->addChild(pNode);
		pNode->release(); 
		pNode->m_bInCache = false;
		m_arr.pop_front();
	}
	else
	{
		pNode = createNode<T>();
		pFather->addChild(pNode);
	}
	
	pNode->cacheInit();
	return pNode;
}

// 如果是动作删除，因为节点不在缓冲池
// 不会对缓冲池有影响
template<typename T>
void Cache<T>::deleteNode(T* &pNode)// **
{
	pNode->m_bInCache = true;
	m_arr.push_back(pNode);
	pNode->retain();
	pNode->removeFromParent();
	pNode = NULL;
}

template<typename T>
void Cache<T>::deleteOnExit(CacheObj* pNode)
{
	pNode->m_bInCache = true;
	m_arr.push_back((T*)pNode);
	pNode->retain();
}

#endif
