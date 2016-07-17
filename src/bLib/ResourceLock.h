#pragma once
#include "bluemeiLib.h"
//#include <windows.h>
#include "Exception.h"
#include "Object.h"

namespace bluemei{

#define DEFAULT_MAX_COUNT 1024
#define waitTask() getLock()

class BLUEMEILIB_API ResourceLock : public Object
{
public:
	ResourceLock(unsigned int count=0);
	virtual ~ResourceLock(void);
public:
	ResourceLock(const ResourceLock& other);
	ResourceLock& operator=(const ResourceLock& other);
private:
	HANDLE semaphoreHandle;
	volatile unsigned int waitCount;//等待的线程数
protected:
	virtual void init(unsigned int count);
public:
	virtual void getLock();
	virtual bool wait(unsigned long mSecond=INFINITE) throw(Exception);
	virtual long notify() throw(Exception);
	virtual void notifyAll() throw(Exception);
	virtual long getWaitCount() const;
};
typedef ResourceLock SyncLock;

}//end of namespace bluemei