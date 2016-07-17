// XcpClient.cpp : Defines the entry point for the console application.
#pragma once
#include "stdafx.h"
#include "MemoryPool.h"
#include "NullPointerException.h"

namespace bluemei{


template<class T>
SimpleMemoryPool<T>::SimpleMemoryPool(unsigned int itemSize/*=128*/,unsigned int maxSize/*=1024*/)
{
	m_bNeedThrow=true;
	init(itemSize,maxSize);
}

template<class T>
SimpleMemoryPool<T>::~SimpleMemoryPool()
{
	destroy();
}

template<class T>
void SimpleMemoryPool<T>::init(unsigned int itemSize,unsigned int maxSize)
{
	if(m_listOriginalObject.size()>0)
		return;
	if(maxSize<itemSize)
		maxSize=itemSize;
	m_nMaxSize=maxSize;
	for(unsigned int i=0;i<itemSize;i++)
	{
		m_listOriginalObject.addToLast(new T());
	}
	this->m_listObject=m_listOriginalObject;
}

template<class T>
void SimpleMemoryPool<T>::destroy()
{
	auto i=m_listOriginalObject.iterator();
	while(i->hasNext())
	{
		delete i->next();
	}
	m_listOriginalObject.releaseIterator(i);
	m_listOriginalObject.clear();
	m_listObject.clear();
}

template<class T>
bool SimpleMemoryPool<T>::changeMaxSize( unsigned int maxSize)
{
	/*int usedSize=m_listOriginalObject.size()-m_listObject.size();
	if (maxSize<=usedSize)
	{
		return false;
	}*/
	unsigned int currentSize=m_listOriginalObject.size();
	if(maxSize<currentSize)
		return false;
	
	m_nMaxSize=maxSize;
	return true;
}

template<class T>
void SimpleMemoryPool<T>::setThrowException( bool needThrow )
{
	m_bNeedThrow=needThrow;
}

template<class T>
bool SimpleMemoryPool<T>::growSize( unsigned int size )
{
	bool succes=true;
	int currentSize=m_listOriginalObject.size();
	if(size+currentSize>m_nMaxSize)//超过最大容量
	{
		size=m_nMaxSize-currentSize;
		succes=false;
	}

	for(unsigned int i=0;i<size;i++)
	{
		T* obj=new T();
		m_listOriginalObject.addToLast(obj);
		m_listObject.addToLast(obj);
	}
	return succes;
}

template<class T>
unsigned int SimpleMemoryPool<T>::available()
{
	return m_listObject.size();
}

template<class T>
void SimpleMemoryPool<T>::release( void* obj )
{
	if(obj!=nullptr)
		m_listObject.addToLast((T*)obj);
}

template<class T>
void* SimpleMemoryPool<T>::get()
{
	if(available()==0)
	{
		double currentSize=(m_listOriginalObject.size())*0.5+2;
		growSize((unsigned int)currentSize);
	}

	T* obj=nullptr;
	if(m_listObject.removeFirstElement(obj))
		return obj;
	else{
		if(m_bNeedThrow)
		{
			throw NullPointerException("out of memory.");
		}
		return nullptr;
	}
}


}//end of namespace bluemei