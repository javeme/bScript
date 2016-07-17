#pragma once
#include "stdafx.h"
#include "ExpressionVisitor.h"
#include "Method.h"
#include "EvaluateContext.h"

namespace bluemei{

class EvaluateVisitor : public ExpressionVisitor
{
public:
	EvaluateVisitor(EvaluateContext* ctx):contextRef(ctx){}
	virtual ~EvaluateVisitor(){}
public:
	EvaluateContext* getContext() const { return contextRef; }
	void setContext(EvaluateContext* val) { contextRef = val; }
protected:
	EvaluateContext* contextRef;
public:
	virtual BSVar* visitMethod(Method* node)
	{
		//���������Ϸ���
		;
		//��������ջ		
		StackFrame stackFrame;//ջ֡
		//��ȡ�������
		;
		//���з�����
		bool success=false; 
		if(node!=nullptr && node->getStatment())
		{
			success=node->getStatment()->accept(this);
		}
		//��ȡ���
		BSVar* rs;//=stackFrame.pop();
		//����
		return rs;
	}
};

}//end of namespace bluemei
