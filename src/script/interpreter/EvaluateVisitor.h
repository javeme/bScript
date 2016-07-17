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
		//���������Ϸ���
		;
		//��ȡ����ջ	
		checkNullPtr(contextRef);
		StackFrame* stackFrame=contextRef->getStackFrame();//ջ֡
		checkNullPtr(stackFrame);
		OperandStack* stack=stackFrame->getStack();
		checkNullPtr(stack);
		//��ȡջ�ﴫ�����
		ArrayList<BSVar*> list=node->getIncomingVarList();
		for (unsigned int i=0;i<list.size();i++)
		{
			BSVar* var=list[i];
			*var=*stack->pop();
		}
		//���з�����
		bool success=false; 
		if(node!=nullptr && node->getStatment())
		{
			success=node->getStatment()->accept(this);
		}
		//�����ؽ��ѹջ
		BSVar* rs=detachMethodResult();
		stack->put(rs);
		//��鷵�ؽ���Ϸ���
		;
		return success;
	}
	virtual BSVar* visitMethod(Method* node)
	{
		visit(node);
		//ȡ�������
		checkNullPtr(contextRef);
		StackFrame* stackFrame=contextRef->getStackFrame();//ջ֡
		checkNullPtr(stackFrame);
		OperandStack* stack=stackFrame->getStack();
		checkNullPtr(stack);
		return stack->peek();
	}
};

}//end of namespace bluemei
