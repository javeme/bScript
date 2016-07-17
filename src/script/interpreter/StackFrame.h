#pragma once
#include "ByteBuffer.h"
#include "Field.h"
#include "Method.h"

namespace bluemei{

class Method;

class OperandStack : public DataBuffer<BSVar*>
{
public:
	OperandStack(){}
	virtual ~OperandStack(){}
public:
	BSVar* peek(){
		int index=m_nOffset-1;
		if(index<0)
			throwpe(OutOfBoundException(index,m_nOffset));
		return m_buffer[index];
	}
};

class StackFrame : public Object
{
public:
	StackFrame(int size=-1);
	virtual ~StackFrame();
public:
	OperandStack* getStack() const { return m_pOperandStack; }
	void setStack(OperandStack* val) { m_pOperandStack = val; }

	void setMethod(Method *pMethod);
	Method* getMethod() const { return m_pMethodRef; }
protected:
	OperandStack* m_pOperandStack;
	Method *m_pMethodRef;
	//HashMap<String,Field> localVarMap;//局部变量存储区
	//HashMap<String,Field>* m_pGlobalVarMap;
};

}//end of namespace bluemei