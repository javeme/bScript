#pragma once
#include "stdafx.h"
#include "Method.h"
#include "Operand.h"
#include "EvaluateContext.h"
#include "EvaluateVisitor.h"

namespace bluemei{
	
Method::Method( cstring name ) :methodName(name)
{
	stmt=nullptr;
}

Method::~Method()
{
	delete stmt;
}

String Method::getText() const
{
	if (stmt!=nullptr)
	{
		String str=stmt->getText();
		StringBuilder sb(str.length()*1.2);

		sb.append(methodName);
		;
		sb.append(str);
		;

		return sb.toString();
	}
	return STR_NULL;
}

bool Method::accept( InstructionVisitor* visitor )
{
	checkNullPtr(visitor);
	return visitor->visit(this);
}

BSVar* Method::evaluate( EvaluateContext* ctx )
{
	checkNullPtr(ctx);
	EvaluateVisitor* visitor=ctx->getVisitor();
	checkNullPtr(visitor);

	BSVar* rs=visitor->visitMethod(this);
	//·µ»Ø
	return rs;
}

}//end of namespace bluemei

