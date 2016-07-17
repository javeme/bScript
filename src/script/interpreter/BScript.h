#pragma once
#include "Method.h"
#include "EvaluateVisitor.h"
#include "Executeable.h"

namespace bluemei{

class BScript : public Executeable
{
public:
	BScript(Instruction* scr):script(scr){}
	virtual ~BScript(){ delete script; }
public:
	virtual BSVar* evaluate(EvaluateContext* ctx) {
		checkNullPtr(ctx);
		checkNullPtr(script);

		BSVar* result=nullptr;
		Method* mth=dcast<Method>(script);
		if (mth!=nullptr)
		{
			result=mth->evaluate(ctx);
		}
		else{
			bool success=script->accept(ctx->getVisitor());
			result=new OperandNumber(new Boolean(success));
		}
		return result;
	}
	virtual void execute()
	{
		EvaluateContext ctx;
		delete evaluate(&ctx);
	}
protected:
	Instruction* script;
};

}//end of namespace bluemei

