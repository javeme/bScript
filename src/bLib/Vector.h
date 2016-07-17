#pragma once

#include "bluemeiLib.h"
#include "OutOfBoundException.h"

namespace bluemei{

//模板类无法被dll导出 BLUEMEILIB_API
template <class T>
class BLUEMEILIB_TEMPLATE Vector : public Object// : public vector<T>
{
public:
	Vector(void);
	virtual ~Vector(void);
private:
	vector<T> dataArray;
public:
	int add(T ele);
	bool remove(int pos,T& value);
	bool remove(const T& ele);
	bool get(int pos,T& value);
	T& operator[](int pos);
	int size();
};

}//end of namespace bluemei