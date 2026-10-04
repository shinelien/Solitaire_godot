#pragma once


template<typename T>

T* createNode()
{
	T* t = new T;
	if (t&&t->init())
	{
		t->autorelease();
		return t;
	}
	else
	{
		delete t;
		t = NULL;
		return NULL;
	}
	return NULL;
}