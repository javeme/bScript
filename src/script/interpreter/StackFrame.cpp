#include "stdafx.h"
#include "StackFrame.h"

namespace bluemei{

StackFrame::StackFrame( int size )/* :localVarMap(size)*/
{
	m_pOperandStack=new OperandStack();
	m_pMethodRef=nullptr;
}

StackFrame::~StackFrame()
{
	delete m_pOperandStack;
	m_pMethodRef=nullptr;
}

void StackFrame::setMethod( Method *pMethod )
{
	m_pMethodRef=pMethod;
}

}//end of namespace bluemei