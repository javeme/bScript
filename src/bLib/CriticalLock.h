#ifndef _CriticalLock_h_
#define _CriticalLock_h_

#include "bluemeiLib.h"
//#include <windows.h>
#include "Exception.h"
#include "Object.h"

namespace bluemei{


#define DEFAULT_MAX_COUNT 1024


class BLUEMEILIB_API CriticalLock : public Object
{
public:
	CriticalLock();
	virtual ~CriticalLock(void);
public:
	CriticalLock(const CriticalLock& other){
		waitCount=0;
		::InitializeCriticalSection(&critialSection);
		this->operator=(other);
	};
	CriticalLock& operator=(const CriticalLock& other){
		return *this;
	};
private:
	CRITICAL_SECTION critialSection;
	volatile unsigned int waitCount;//等待的线程数
public:
	virtual void getLock();
	virtual void releaseLock();
	void notify(){ return releaseLock();}
	virtual long getWaitCount() const;
	virtual long getMyThreadEnteredCount()const;
};

class BLUEMEILIB_API ScopedLock : Object
{
public:
	explicit ScopedLock(CriticalLock& m): mutex(m)
	{
		mutex.getLock();
	}
	~ScopedLock()
	{
		mutex.releaseLock();
	}

private:
	CriticalLock& mutex;

private:
	ScopedLock();
	ScopedLock(const ScopedLock&);
	ScopedLock& operator = (const ScopedLock&);
};


}//end of namespace bluemei
#endif