#pragma once
#include "stdafx.h"
#include "ExpressionVisitor.h"
#include "Method.h"
#include "EvaluateContext.h"

namespace bluemei{

class EvaluateVisitor : public ExpressionVisitor
{
public:
	EvaluateVisitor(EvaluateContext* ctx):contextRef(ctx){
		methodResult=nullptr;
	}
	virtual ~EvaluateVisitor(){}
public:
	EvaluateContext* getContext() const { return contextRef; }
	void setContext(EvaluateContext* val) { contextRef = val; }

	BSVar* getMethodResult() const { return methodResult; }
	void setMethodResult(BSVar* val) { methodResult = val; }
	BSVar* detachMethodResult() { 
		BSVar* tmp=methodResult;
		methodResult=nullptr;
		return tmp;
	}
protected:
	EvaluateContext* contextRef;
	BSVar* methodResult;;
public:
	virtual bool visit(Method* node)
	{
		//检查各参数合法性
		;
		//获取方法栈	
		checkNullPtr(contextRef);
		StackFrame* stackFrame=contextRef->getStackFrame();//栈帧
		checkNullPtr(stackFrame);
		OperandStack* stack=stackFrame->getStack();
		checkNullPtr(stack);
		//获取栈里传入参数
		ArrayList<BSVar*> list=node->getIncomingVarList();
		for (unsigned int i=0;i<list.size();i++)
		{
			BSVar* var=list[i];
			*var=*stack->pop();
		}
		//运行方法体
		bool success=false; 
		if(node!=nullptr && node->getStatment())
		{
			success=node->getStatment()->accept(this);
		}
		//将返回结果压栈
		BSVar* rs=detachMethodResult();
		stack->put(rs);
		//检查返回结果合法性
		;
		return success;
	}
	virtual BSVar* visitMethod(Method* node)
	{
		visit(node);
		//取结果返回
		checkNullPtr(contextRef);
		StackFrame* stackFrame=contextRef->getStackFrame();//栈帧
		checkNullPtr(stackFrame);
		OperandStack* stack=stackFrame->getStack();
		checkNullPtr(stack);
		return stack->peek();
	}
};

}//end of namespace bluemei
