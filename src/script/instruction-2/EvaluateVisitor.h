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
		//检查各参数合法性
		;
		//建立方法栈		
		StackFrame stackFrame;//栈帧
		//获取传入参数
		;
		//运行方法体
		bool success=false; 
		if(node!=nullptr && node->getStatment())
		{
			success=node->getStatment()->accept(this);
		}
		//获取结果
		BSVar* rs;//=stackFrame.pop();
		//返回
		return rs;
	}
};

}//end of namespace bluemei
