#pragma once
#include "stdafx.h"
#include "Vector.h"

namespace bluemei{

template <class T>
Vector<T>::Vector(void)
{
	//dataArray.resize(10);
}

template <class T>
Vector<T>::~Vector(void)
{
	;
}

template <class T>
int Vector<T>::add(T ele)
{
	dataArray.push_back(ele);
	return this->size();
}

template <class T>
bool Vector<T>::remove(int pos,T& value)
{
	if(pos<0||pos>=dataArray.size())
		return false;
	vector <T> ::iterator iter = dataArray.begin(); 
	advance(iter,pos);
	value=*iter;
	dataArray.erase(iter);
	return true;	
}

template <class T>
bool Vector<T>::get(int pos,T& value)
{
	if(pos<0||pos>=dataArray.size())
		return false;
	value=dataArray[pos];
	return true;
}

template <class T>
T& Vector<T>::operator[](int pos)
{
	if(pos<0||pos>=dataArray.size())
	{
		char buf[100];
		sprintf(buf,"vector size is %d,can't request %d.",dataArray.size(),pos);
		throw OutOfBoundException(buf);
	}
	return dataArray[pos];
}

template <class T>
bool Vector<T>::remove(const T& ele)
{
	vector<T>::iterator iter = find(dataArray.begin(), dataArray.end(), ele);
	if (iter != dataArray.end()) 
	{
		dataArray.erase(iter);
		return true;
	}
	return false;	
}

template <class T>
int Vector<T>::size()
{
	return dataArray.size();
}

}//end of namespace bluemei